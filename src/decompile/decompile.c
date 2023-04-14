#include "decompile_private.h"

#define DEBUG_REPORT_SYMBOLS 0

typedef struct decompiler decompiler_t;
struct decompiler
{
  dis86_t *                  dis;
  dis86_decompile_config_t * cfg;
  dis86_decompile_config_t * default_cfg;
  const char *               func_name;
  dis86_instr_t *            ins;
  size_t                     n_ins;

  symbols_t * symbols;
  labels_t    labels[1];

  meh_t *meh;
};

static decompiler_t * decompiler_new( dis86_t *                  dis,
                                      dis86_decompile_config_t * opt_cfg,
                                      const char *               func_name,
                                      dis86_instr_t *            ins_arr,
                                      size_t                     n_ins )

{
  decompiler_t *d = calloc(1, sizeof(decompiler_t));
  d->dis = dis;
  d->cfg = opt_cfg;
  if (!d->cfg) {
    d->default_cfg = config_default_new();
    d->cfg = d->default_cfg;
  }
  d->func_name = func_name;
  d->ins       = ins_arr;
  d->n_ins     = n_ins;

  d->symbols = symbols_new();
  d->meh = NULL;
  return d;
}

static void decompiler_delete(decompiler_t *d)
{
  if (d->meh) meh_delete(d->meh);
  if (d->default_cfg) config_delete(d->default_cfg);
  symbols_delete(d->symbols);
  free(d);
}

static const char *n_bytes_as_type(u16 n_bytes)
{
  switch (n_bytes) {
    case 1: return "u8";
    case 2: return "u16";
    case 4: return "u32";
    default: FAIL("Unknown size type | n_bytes: %u", n_bytes);
  }
}

static void dump_symtab(symtab_t *symtab)
{
  symtab_iter_t it[1];
  symtab_iter_begin(it, symtab);
  while (1) {
    sym_t *var = symtab_iter_next(it);
    if (!var) break;

    static char buf[128];
    const char *size;
    if (var->len <= 4) {
      size = n_bytes_as_type(var->len);
    } else {
      size = "UNKNOWN";
    }
    LOG_INFO("  %-30s | %04x | %6u | %s", sym_name(var, buf, ARRAY_SIZE(buf)), (u16)var->off, var->len, size);
  }
}

static void decompiler_initial_analysis(decompiler_t *d)
{
  // Pass to find all labels
  find_labels(d->labels, d->ins, d->n_ins);

  // Populate registers
  for (int reg_id = 1; reg_id < _REG_LAST; reg_id++) {
    sym_t deduced_sym[1];
    sym_deduce_reg(deduced_sym, reg_id);
    if (deduced_sym->len != 2) continue; // skip the small overlap regs
    symbols_insert_deduced(d->symbols, deduced_sym);
  }

  // Load all global symbols from config into the symtab
  for (size_t i = 0; i < d->cfg->global_len; i++) {
    config_global_t *g = &d->cfg->global_arr[i];

    type_t type[1];
    if (!type_parse(type, g->type)) {
      LOG_WARN("For global '%s', failed to parse type '%s' ... skipping", g->name, g->type);
      continue;
    }

    symbols_add_global(d->symbols, g->name, g->offset, type_size(type));
  }

  // Pass to locate all symbols
  for (size_t i = 0; i < d->n_ins; i++) {
    dis86_instr_t *ins = &d->ins[i];

    /* const char *as = dis86_print_intel_syntax(d->dis, ins, false); */
    /* LOG_INFO("INS: '%s'", as); */
    /* free((void*)as); */

    for (size_t j = 0; j < ARRAY_SIZE(ins->operand); j++) {
      operand_t *o = &ins->operand[j];
      if (o->type != OPERAND_TYPE_MEM) continue;

      sym_t deduced_sym[1];
      if (!sym_deduce(deduced_sym, &o->u.mem)) continue;

      if (!symbols_insert_deduced(d->symbols, deduced_sym)) {
        static char buf[128];
        const char *name = sym_name(deduced_sym, buf, ARRAY_SIZE(buf));
        LOG_WARN("Unknown global | name: %s  off: 0x%04x  size: %u", name, (u16)deduced_sym->off, deduced_sym->len);
      }
    }
  }

  // Pass to convert to expression structures
  d->meh = meh_new(d->cfg, d->symbols, d->ins, d->n_ins);

  // Report the symbols
  if (DEBUG_REPORT_SYMBOLS) {
    LOG_INFO("Registers:");
    dump_symtab(d->symbols->registers);
    LOG_INFO("Globals:");
    dump_symtab(d->symbols->globals);
    LOG_INFO("Params:");
    dump_symtab(d->symbols->params);
    LOG_INFO("Locals:");
    dump_symtab(d->symbols->locals);
  }
}

static void decompiler_emit_preamble(decompiler_t *d, str_t *s)
{
  static char buf[128];
  symtab_iter_t it[1];

  // Emit params
  symtab_iter_begin(it, d->symbols->params);
  while (1) {
    sym_t *var = symtab_iter_next(it);
    if (!var) break;

    const char *name = sym_name(var, buf, ARRAY_SIZE(buf));
    str_fmt(s, "#define %s ARG_%zu(0x%x)\n", name, 8*sym_size_bytes(var), var->off);
  }

  // Emit locals
  symtab_iter_begin(it, d->symbols->locals);
  while (1) {
    sym_t *var = symtab_iter_next(it);
    if (!var) break;

    const char *name = sym_name(var, buf, ARRAY_SIZE(buf));
    str_fmt(s, "#define %s LOCAL_%zu(0x%x)\n", name, 8*sym_size_bytes(var), -var->off);
  }

  str_fmt(s, "void %s(void)\n", d->func_name);
  str_fmt(s, "{\n");
}

static void decompiler_emit_postamble(decompiler_t *d, str_t *s)
{
  static char buf[128];
  symtab_iter_t it[1];

  str_fmt(s, "}\n");

  // Cleanup params
  symtab_iter_begin(it, d->symbols->params);
  while (1) {
    sym_t *var = symtab_iter_next(it);
    if (!var) break;
    str_fmt(s, "#undef %s\n", sym_name(var, buf, ARRAY_SIZE(buf)));
  }

  // Cleanup locals
  symtab_iter_begin(it, d->symbols->locals);
  while (1) {
    sym_t *var = symtab_iter_next(it);
    if (!var) break;
    str_fmt(s, "#undef %s\n", sym_name(var, buf, ARRAY_SIZE(buf)));
  }
}

static u16 size_in_bytes(int sz)
{
  switch (sz) {
    case SIZE_8:  return 1;
    case SIZE_16: return 2;
    case SIZE_32: return 4;
    default: FAIL("Unknown size type");
  }
}

static const char * size_as_type(int sz)
{
  return n_bytes_as_type(size_in_bytes(sz));
}

static void sym_lvalue(str_t *s, sym_t *var, operand_mem_t *mem)
{
  static char buf[128];
  const char *name = sym_name(var, buf, ARRAY_SIZE(buf));

  u16 mem_len = size_in_bytes(mem->sz);
  if (var->off == (i16)mem->off &&
      var->len == mem_len) {
    str_fmt(s, "%s", name);
  }

  else {
    u16 bytes = (i16)mem->off - var->off;
    str_fmt(s, "*(%s*)((u8*)&%s + %u)", size_as_type(mem->sz), name, bytes);
  }
}

static void sym_rvalue(str_t *s, sym_t *var, operand_mem_t *mem)
{
  static char buf[128];
  const char *name = sym_name(var, buf, ARRAY_SIZE(buf));

  u16 mem_len = size_in_bytes(mem->sz);
  if (var->off == (i16)mem->off) {
    if (var->len == mem_len) {
      str_fmt(s, "%s", name);
    } else {
      // Offset is the same, so just truncate it down
      str_fmt(s, "(%s)%s", size_as_type(mem->sz), name);
    }
  }

  else {
    u16 bits = 8 * ((i16)mem->off - var->off);
    str_fmt(s, "(%s)(%s>>%u)", size_as_type(mem->sz), name, bits);
  }
}

static void operand_str(decompiler_t *d, str_t *s, dis86_instr_t *ins, operand_t *o, bool lvalue)
{
  static char buf[128];

  switch (o->type) {
    case OPERAND_TYPE_REG: str_fmt(s, "%s", as_upper(reg_name(o->u.reg.id))); break;
    case OPERAND_TYPE_MEM: {
      operand_mem_t *m = &o->u.mem;
      symref_t symref = symbols_find_mem(d->symbols, m);
      if (symref.symbol) {
        if (lvalue) sym_lvalue(s, symref.symbol, m);
        else sym_rvalue(s, symref.symbol, m);
        break; // all done
      }
      switch (m->sz) {
        case SIZE_8:  str_fmt(s, "*PTR_8("); break;
        case SIZE_16: str_fmt(s, "*PTR_16("); break;
        case SIZE_32: str_fmt(s, "*PTR_32("); break;
      }
      str_fmt(s, "%s, ", as_upper(reg_name(m->sreg)));
      if (!m->reg1 && !m->reg2) {
        if (m->off) str_fmt(s, "0x%x", m->off);
      } else {
        if (m->reg1) str_fmt(s, "%s", as_upper(reg_name(m->reg1)));
        if (m->reg2) str_fmt(s, "+%s", as_upper(reg_name(m->reg2)));
        if (m->off) {
          i16 disp = (i16)m->off;
          if (disp >= 0) str_fmt(s, "+0x%x", (u16)disp);
          else           str_fmt(s, "-0x%x", (u16)-disp);
        }
      }
      str_fmt(s, ")");
    } break;
    case OPERAND_TYPE_IMM: str_fmt(s, "0x%x", o->u.imm.val); break;
    case OPERAND_TYPE_REL: {
      /* u16 effective = ins->addr + ins->n_bytes + o->u.rel.val; */
      /* str_fmt(s, "0x%x", effective); */
      str_fmt(s, "REL_ADDR_BROKEN");
    } break;
      //case OPERAND_TYPE_FAR: break;
    default: FAIL("INVALID OPERAND TYPE: %d", o->type);
  }
}

static void value_str(value_t *v, str_t *s, bool as_lvalue)
{
  static char buf[128];

  switch (v->type) {
    case VALUE_TYPE_SYM: {
      const char *name = sym_name(v->u.sym->ref.symbol, buf, ARRAY_SIZE(buf));
      str_fmt(s, "%s", name);
    } break;
    case VALUE_TYPE_MEM: {
      value_mem_t *m = v->u.mem;
      switch (m->sz) {
        case SIZE_8:  str_fmt(s, "*PTR_8("); break;
        case SIZE_16: str_fmt(s, "*PTR_16("); break;
        case SIZE_32: str_fmt(s, "*PTR_32("); break;
      }
      str_fmt(s, "%s, ", sym_name(m->sreg.symbol, buf, ARRAY_SIZE(buf)));
      // FIXME: THIS IS ALL BROKEN BECAUSE IT ASSUMES THE SYMREF ARE NEVER PARTIAL REFS
      if (!m->reg1.symbol && !m->reg2.symbol) {
        if (m->off) str_fmt(s, "0x%x", m->off);
      } else {
        if (m->reg1.symbol) str_fmt(s, "%s", sym_name(m->reg1.symbol, buf, ARRAY_SIZE(buf)));
        if (m->reg2.symbol) str_fmt(s, "+%s", sym_name(m->reg2.symbol, buf, ARRAY_SIZE(buf)));
        if (m->off) {
          i16 disp = (i16)m->off;
          if (disp >= 0) str_fmt(s, "+0x%x", (u16)disp);
          else           str_fmt(s, "-0x%x", (u16)-disp);
        }
      }
      str_fmt(s, ")");
    } break;
    case VALUE_TYPE_IMM: {
      str_fmt(s, "0x%x", v->u.imm->value);
    } break;
    default: FAIL("Unknown value type: %d\n", v->type);
  }
}

static void decompiler_emit_expr(decompiler_t *d, expr_t *expr, str_t *ret_s)
{
  str_t s[1];
  str_init(s);

  switch (expr->kind) {
    case EXPR_KIND_UNKNOWN: {
      str_fmt(s, "UNKNOWN();");
    } break;
    case EXPR_KIND_OPERATOR: {
      expr_operator_t *k = expr->k.operator;
      operand_str(d, s, NULL, &k->oper1, true);
      str_fmt(s, " %s ", k->operator);
      if (k->oper2.type != OPERAND_TYPE_NONE) {
        operand_str(d, s, NULL, &k->oper2, false);
      }
      str_fmt(s, ";");
    } break;
    case EXPR_KIND_OPERATOR3: {
      expr_operator3_t *k = expr->k.operator3;
      value_str(&k->dest, s, true);
      str_fmt(s, " = ");
      if (k->sign) str_fmt(s, "(i16)");
      value_str(&k->left, s, false);
      str_fmt(s, " %s ", k->operator);
      if (k->sign) str_fmt(s, "(i16)");
      value_str(&k->right, s, false);
      str_fmt(s, ";");
    } break;
    case EXPR_KIND_FUNCTION: {
      expr_function_t *k = expr->k.function;
      if (k->ret.type != OPERAND_TYPE_NONE) {
        operand_str(d, s, NULL, &k->ret, true);
        str_fmt(s, " = ");
      }
      str_fmt(s, "%s(", k->func_name);
      for (size_t i = 0; i < ARRAY_SIZE(k->args); i++) {
        operand_t *o = &k->args[i];
        if (o->type == OPERAND_TYPE_NONE) break;
        if (i != 0) str_fmt(s, ", ");
        operand_str(d, s, NULL, o, false);
      }
      str_fmt(s, ");");
    } break;
    case EXPR_KIND_LITERAL: {
      expr_literal_t *k = expr->k.literal;
      str_fmt(s, "%s", k->text);
    } break;
    case EXPR_KIND_BRANCH_COND: {
      expr_branch_cond_t *k = expr->k.branch_cond;
      str_fmt(s, "if (");
      if (k->signed_cmp) str_fmt(s, "(i16)");
      value_str(&k->left, s, false);
      str_fmt(s, " %s ", k->operator);
      if (k->signed_cmp) str_fmt(s, "(i16)");
      value_str(&k->right, s, false);
      str_fmt(s, ") goto label_%08x;", k->target);
    } break;
    case EXPR_KIND_BRANCH: {
      expr_branch_t *k = expr->k.branch;
      str_fmt(s, "goto label_%08x;", k->target);
    } break;
    case EXPR_KIND_CALL: {
      expr_call_t *k = expr->k.call;
      if (k->name) {
        str_fmt(s, "CALL_FUNC(%s);", k->name);
      } else {
        switch (k->addr.type) {
          case ADDR_TYPE_FAR: {
            str_fmt(s, "CALL_FAR(0x%04x, 0x%04x);", k->addr.u.far.seg, k->addr.u.far.off);
          } break;
          case ADDR_TYPE_NEAR: {
            str_fmt(s, "CALL_NEAR(0x%04x);", k->addr.u.near);
          } break;
          default: {
            FAIL("Unknonw address type: %d", k->addr.type);
          } break;
        }
      }
      if (k->remapped) str_fmt(s, " /* remapped */");
    } break;
    case EXPR_KIND_LEA: {
      expr_lea_t *k = expr->k.lea;
      operand_str(d, s, NULL, &k->dest, false);
      str_fmt(s, " = %s - 0x%x;", as_upper(reg_name(k->addr_base_reg)), -(i16)k->addr_offset);
    } break;
    default: {
      str_fmt(s, "UNIMPL();");
    } break;
  }

  const char *code_str = str_to_cstr(s);
  for (size_t i = 0; i < expr->n_ins; i++) {
    const char *as = dis86_print_intel_syntax(d->dis, &expr->ins[i], false);
    const char *cs = i+1 == expr->n_ins ? code_str : "";
    str_fmt(ret_s, "  %-50s // %s\n", cs, as);
    free((void*)as);
  }
  free((void*)code_str);
}

char *dis86_decompile( dis86_t *                  dis,
                       dis86_decompile_config_t * opt_cfg,
                       const char *               func_name,
                       dis86_instr_t *            ins_arr,
                       size_t                     n_ins )
{
  str_t ret_s[1];
  str_init(ret_s);

  decompiler_t *d = decompiler_new(dis, opt_cfg, func_name, ins_arr, n_ins);
  decompiler_initial_analysis(d);
  decompiler_emit_preamble(d, ret_s);

  for (size_t i = 0; i < d->meh->expr_len; i++) {
    expr_t *expr = &d->meh->expr_arr[i];
    if (is_label(d->labels, (u32)expr->ins->addr)) {
      str_fmt(ret_s, "\n label_%08x:\n", (u32)expr->ins->addr);
    }
    decompiler_emit_expr(d, expr, ret_s);
  }

  decompiler_emit_postamble(d, ret_s);
  return str_to_cstr(ret_s);
}
