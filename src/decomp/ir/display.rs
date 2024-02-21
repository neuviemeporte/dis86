use crate::instr;
use crate::decomp::ir::*;
use std::fmt;
use std::collections::HashMap;

impl fmt::Display for Opcode {
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    write!(f, "{}", self.as_str())
  }
}

fn reg_name(r: instr::Reg) -> &'static str {
  match r {
    instr::Reg::AX => "ax",
    instr::Reg::CX => "cx",
    instr::Reg::DX => "dx",
    instr::Reg::BX => "bx",
    instr::Reg::SP => "sp",
    instr::Reg::BP => "bp",
    instr::Reg::SI => "si",
    instr::Reg::DI => "di",
    instr::Reg::AL => "al",
    instr::Reg::CL => "cl",
    instr::Reg::DL => "dl",
    instr::Reg::BL => "bl",
    instr::Reg::AH => "ah",
    instr::Reg::CH => "ch",
    instr::Reg::DH => "dh",
    instr::Reg::BH => "bh",
    instr::Reg::ES => "es",
    instr::Reg::CS => "cs",
    instr::Reg::SS => "ss",
    instr::Reg::DS => "ds",
    instr::Reg::IP => "ip",
    instr::Reg::FLAGS => "flags",
  }
}

struct RefMapper {
  map: HashMap<Ref, usize>,
  ref_to_symbol: HashMap<Ref, (Symbol, usize)>,
  next: usize,
}

impl RefMapper {
  fn new(ir: &IR) -> Self {
    // Build some helper tables from the "defs"
    let mut symbol_num: HashMap<Symbol, usize> = HashMap::new();
    let mut ref_to_symbol: HashMap<Ref, (Symbol, usize)> = HashMap::new();
    for blk in &ir.blocks {
      for (sym, r) in blk.defs.iter() {
        if !matches!(r, Ref::Instr(_, _)) { continue; }
        assert!(ref_to_symbol.get(r).is_none());
        let num_ptr = symbol_num.entry(*sym).or_insert(1);
        let num = *num_ptr;
        *num_ptr = num+1;
        ref_to_symbol.insert(*r, (*sym, num));
      }
    }

    Self {
      map: HashMap::new(),
      ref_to_symbol,
      next: 0,
    }
  }

  fn map(&mut self, r: Ref) -> usize {
    match self.map.get(&r) {
      Some(val) => *val,
      None => {
        let val = self.next;
        self.map.insert(r, val);
        self.next += 1;
        val
      }
    }
  }

  fn fmt(&mut self, ir: &IR, r: Ref) -> String {
    if let Some((sym, num)) = self.ref_to_symbol.get(&r) {
      return format!("{}.{}", reg_name(sym.0), num);
    }

    match r {
      Ref::Const(ConstRef(num)) => {
        let k = ir.consts[num] as i16;
        if -1024 <= k && k <= 16 {
          format!("#{}", k)
        } else {
          format!("#0x{:x}", k)
        }
      }
      Ref::Init(sym) => format!("{}.0", sym),
      Ref::Block(blk) => format!("b{}", blk.0),
      _ => format!("t{}", self.map(r)),
    }
  }

  fn write_instr(&mut self, f: &mut fmt::Formatter<'_>, ir: &IR, instr: &Instr, iref: Ref) -> fmt::Result {
    if instr.opcode == Opcode::Nop {
      return Ok(());
    }
    let s = self.fmt(ir, iref);
    write!(f, "  {:<8} = ", s)?;
    write!(f, "{:<10}", instr.opcode.to_string())?;
    for oper in &instr.operands {
      let s = self.fmt(ir, *oper);
      write!(f, " {:<12}", s)?;
    }
    writeln!(f, "")?;
    Ok(())
  }
}

impl fmt::Display for IR {
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    let mut r = RefMapper::new(self);

    // writeln!(f, "Consts:")?;
    // for (i, val) in self.consts.iter().enumerate() {
    //   writeln!(f, "  c{:<2} = {}", i, val)?;
    // }

    for (i, blk) in self.blocks.iter().enumerate() {
      // if self.is_block_dead(BlockRef(i)) {
      //   continue;
      // }
      writeln!(f, "")?;
      write!(f, "b{i}: (")?;
      for (k, p) in blk.preds.iter().enumerate() {
        if k != 0 {
          write!(f, " ")?;
        }
        write!(f, "b{}", p.0)?;
      }
      writeln!(f, ") {}", blk.name)?;

      for (j, phi) in blk.phis.iter().enumerate() {
        r.write_instr(f, self, phi, Ref::Phi(BlockRef(i), PhiRef(j)))?;
      }

      for (j, instr) in blk.instrs.iter().enumerate() {
        r.write_instr(f, self, instr, Ref::Instr(BlockRef(i), InstrRef(j)))?;
      }
    }
    Ok(())
  }
}
