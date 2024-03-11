use crate::decomp::ast::*;
use std::fmt;

struct Gen<'a> {
  f: &'a mut dyn fmt::Write,
  indent_level: usize,
  newline: bool,
}

impl<'a> Gen<'a> {
  fn new(f: &'a mut dyn fmt::Write) -> Self {
    Self { f, indent_level: 0, newline: true }
  }

  fn endline(&mut self) -> fmt::Result {
    self.f.write_str("\n")?;
    self.newline = true;
    Ok(())
  }

  fn text(&mut self, txt: &str) -> fmt::Result {
    if self.newline {
      write!(self.f, "{:indent$}", "", indent=2*self.indent_level)?;
      self.newline = false;
    }
    self.f.write_str(txt)
  }

  fn suppress_indent(&mut self) {
    self.newline = false;
  }

  fn enter_block(&mut self) -> fmt::Result {
    self.text("{")?;
    self.indent_level += 1;
    Ok(())
  }

  fn leave_block(&mut self) -> fmt::Result {
    self.indent_level -= 1;
    self.text("}")?;
    Ok(())
  }

  fn unary_oper(&mut self, oper: &UnaryOperator) -> fmt::Result {
    let s = match oper {
      UnaryOperator::Addr => "(u8*)&",
    };
    self.text(s)
  }

  fn binary_oper(&mut self, oper: &BinaryOperator) -> fmt::Result {
    let s = match oper {
      BinaryOperator::Add => "+",
      BinaryOperator::Sub => "-",
      BinaryOperator::And => "&",
      BinaryOperator::Or  => "|",
      BinaryOperator::Xor => "^",
      BinaryOperator::Shl => "<<",
      BinaryOperator::Shr => ">>",
      BinaryOperator::Eq  => "==",
      BinaryOperator::Neq => "!=",
      BinaryOperator::Gt  => ">",
      BinaryOperator::Geq => ">=",
      BinaryOperator::Lt  => "<",
      BinaryOperator::Leq => "<=",
    };
    self.text(s)
  }

  fn expr(&mut self, expr: &Expr) -> fmt::Result {
    match expr {
      Expr::Unary(u) => {
        self.unary_oper(&u.op)?;
        self.expr(&u.rhs)?;
      }
      Expr::Binary(b) => {
        self.text("(")?;
        self.expr(&b.lhs)?;
        self.binary_oper(&b.op)?;
        self.expr(&b.rhs)?;
        self.text(")")?;
      }
      Expr::Const(k) => {
        let s = if *k > 128 {
          format!("0x{:x}", k)
        } else {
          format!("{}", k)
        };
        self.text(&s)?;
      }
      Expr::Name(n) => {
        self.text(n)?;
      }
      Expr::Ptr16(seg, off) => {
        self.text("PTR_16(")?;
        self.expr(seg)?;
        self.text(", ")?;
        self.expr(off)?;
        self.text(")")?;
      }
      Expr::Ptr32(seg, off) => {
        self.text("PTR_32(")?;
        self.expr(seg)?;
        self.text(", ")?;
        self.expr(off)?;
        self.text(")")?;
      }
      Expr::Cast(typ, expr) => {
        self.text(&format!("({})", typ))?;
        self.expr(expr)?;
      }
      Expr::Deref(expr) => {
        self.text("*")?;
        self.expr(expr)?;
      }
      Expr::Call(name, args) => {
        self.expr(name)?;
        self.text("(")?;
        for (i, arg) in args.iter().enumerate() {
          if i != 0 { self.text(", ")?; }
          self.expr(arg)?;
        }
        self.text(")")?;
      }
      _ => self.text(&format!("UNIMPL_EXPR /* {:?} */", expr))?,
    }
    Ok(())
  }

  fn goto(&mut self, label: &Label) -> fmt::Result {
    self.text("goto ")?;
    self.text(&label.0)?;
    self.text(";")?;
    self.endline()
  }

  fn stmt(&mut self, stmt: &Stmt) -> fmt::Result {
    match stmt {
      Stmt::None => (),
      Stmt::Label(l) => {
        self.suppress_indent();
        self.text(&format!("{}:;", l.0))?;
        self.endline()?;
      }
      Stmt::Assign(s) => {
        self.expr(&s.lhs)?;
        self.text(" = ")?;
        self.expr(&s.rhs)?;
        self.text(";")?;
        self.endline()?;
      }
      Stmt::Goto(g) => {
        self.goto(&g.tgt)?;
        self.endline()?;
      }
      Stmt::CondGoto(g) => {
        self.text("if (")?;
        self.expr(&g.cond)?;
        self.text(") ")?;
        self.goto(&g.tgt_true)?;
        self.text("else ")?;
        self.goto(&g.tgt_false)?;
        self.endline()?;
      }
      Stmt::Return => {
        self.text("return;")?;
        self.endline()?;
        self.endline()?;
      }
      _ => {
        self.text(&format!("UNIMPL_STMT; /* {:?} */", stmt))?;
        self.endline()?;
      }
    }
    Ok(())
  }

  fn gen(&mut self, func: &Function) -> fmt::Result {
    self.text(&format!("void {}()", func.name))?;
    self.endline()?;
    self.enter_block()?;
    self.endline()?;
    for stmt in &func.body {
      self.stmt(stmt)?;
    }
    self.leave_block()?;
    Ok(())
  }
}

pub fn generate(func: &Function, f: &mut dyn fmt::Write) -> fmt::Result {
  let mut g = Gen::new(f);
  g.gen(func)
}