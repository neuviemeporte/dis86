#pragma once

typedef struct value     value_t;
typedef struct value_sym value_sym_t;
typedef struct value_mem value_mem_t;
typedef struct value_imm value_imm_t;

enum {
  VALUE_TYPE_SYM = 0,
  VALUE_TYPE_MEM,
  VALUE_TYPE_IMM,
};

struct value_sym
{
  symref_t ref;
};

struct value_mem
{
  // TODO: Remove 8086-isms and dis86-isms
  int        sz; // SIZE_*
  symref_t   sreg;
  symref_t   reg1;
  symref_t   reg2;
  u16        off;
};

struct value_imm
{
  // TODO: Remove 8086-isms and dis86-isms
  int sz; // SIZE_*
  u16 value;
};

struct value
{
  int type;
  union {
    value_sym_t sym[1];
    value_mem_t mem[1];
    value_imm_t imm[1];
  } u;
};

value_t value_from_operand(operand_t *o, symbols_t *symbols);
