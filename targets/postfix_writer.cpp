#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/frame_size_calculator.h"
#include "targets/postfix_writer.h"
#include "l22_parser.tab.h"
#include ".auto/all_nodes.h" // all_nodes.h is automatically generated

//---------------------------------------------------------------------------

void l22::postfix_writer::do_sweep_node(l22::sweep_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  auto vec_type = cdk::reference_type::cast(node->vector()->type());

  // initializer: int i = low
  _pf.DATA();
  _pf.ALIGN();
  _pf.LABEL("__i__");
  node->low()->accept(this, lvl + 2);
  _pf.STINT();

  _pf.TEXT();
  _pf.ALIGN();

  // condition: i < high
  _pf.ADDR("__i__");
  _pf.LDINT();
  node->high()->accept(this, lvl + 2);
  _pf.LT();
  _pf.JZ("__end__");

  // block: if <condition> do f(v[i])
  _pf.LABEL("__cond__");
  node->condition()->accept(this, lvl + 2);
  _pf.JZ("__if_end__");

  node->vector()->accept(this, lvl + 2);
  _pf.LDINT(); // v
  _pf.ADDR("__i__");
  _pf.LDINT(); // i
  _pf.INT(vec_type->referenced()->size());
  _pf.MUL();
  _pf.ADD(); // &v[i]
  if (vec_type->referenced()->name() == cdk::TYPE_DOUBLE)
    _pf.LDDOUBLE();
  else
    _pf.LDINT();

  node->function()->accept(this, lvl + 2);
  _pf.BRANCH();
  if (vec_type->referenced()->name() == cdk::TYPE_DOUBLE) {
    _pf.LDFVAL64();
    _pf.DUP64();
  }
  else {
    _pf.LDFVAL32();
    _pf.DUP32();
  }
    
  node->vector()->accept(this, lvl + 2);
  _pf.LDINT(); // v
  _pf.ADDR("__i__");
  _pf.LDINT(); // i
  _pf.INT(vec_type->referenced()->size());
  _pf.MUL();
  _pf.ADD(); // &v[i]
  if (vec_type->referenced()->name() == cdk::TYPE_DOUBLE)
    _pf.STDOUBLE();
  else
    _pf.STINT();
  
  _pf.TRASH(vec_type->referenced()->size());

  _pf.LABEL("__if_end__");

  // increment: i = i + 1
  _pf.LABEL("__incr__");
  _pf.ADDR("__i__");
  _pf.LDINT();
  _pf.INT(1);
  _pf.DUP32();
  _pf.ADDR("__i__");
  _pf.STINT();
  _pf.TRASH(4);

  _pf.JMP("__cond__");

  _pf.LABEL("__end__");
}

void l22::postfix_writer::do_with_change_node(l22::with_change_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  auto vec_type = cdk::reference_type::cast(node->vector()->type());
  
  // initializer : int i = low
  _pf.DATA();
  _pf.ALIGN();
  _pf.LABEL("__i__");
  node->low()->accept(this, lvl + 2);
  _pf.STINT();

  _pf.TEXT();
  _pf.ALIGN();
  
  // condition : i < high
  _pf.LABEL("__condition__");
  _pf.ADDR("__i__");
  _pf.LDINT();
  node->high()->accept(this, lvl + 2);
  _pf.LT();
  _pf.JZ("__end__");

  // body: apply f to v[i]; v[i] = f(v[i])
  node->vector()->accept(this, lvl + 2);
  _pf.LDINT();
  _pf.ADDR("__i__");
  _pf.LDINT();
  _pf.INT(vec_type->referenced()->size());
  _pf.MUL();
  _pf.ADD();   // &v[i]
  _pf.LDINT(); // v[i]

  node->function()->accept(this, lvl + 2);
  _pf.BRANCH();

  // no conversion needed since we asserted types match
  if (vec_type->referenced()->name() == cdk::TYPE_DOUBLE) {
    _pf.LDFVAL64();
    _pf.DUP64();
  }
  else {
    _pf.LDFVAL32();
    _pf.DUP32();
  }

  node->vector()->accept(this, lvl + 2);
  _pf.LDINT();
  _pf.ADDR("__i__");
  _pf.LDINT();
  _pf.INT(vec_type->referenced()->size());
  _pf.MUL();
  _pf.ADD();   // &v[i]
  _pf.STINT(); // v[i]
  
  _pf.TRASH(vec_type->referenced()->size());

  // increment : i = i + 1
  _pf.LABEL("__increment__");
  _pf.ADDR("__i__");
  _pf.LDINT();
  _pf.INT(1);
  _pf.ADD();
  _pf.DUP32();
  _pf.ADDR("__i__");
  _pf.STINT();
  _pf.TRASH(4);

  _pf.JMP("__condition__");

  // end
  _pf.LABEL("__end__");
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_data_node(cdk::data_node *const node, int lvl)
{
  // EMPTY
}

void l22::postfix_writer::do_nil_node(cdk::nil_node *const node, int lvl)
{
  // EMPTY
}

void l22::postfix_writer::do_block_node(l22::block_node *const node, int lvl)
{
  _symtab.push(); // for block-local vars
  if (node->declarations())
    node->declarations()->accept(this, lvl + 2);
  if (node->instructions())
    node->instructions()->accept(this, lvl + 2);
  _symtab.pop();
}

void l22::postfix_writer::do_again_node(l22::again_node *const node, int lvl)
{
  if (_whileIni.size() != 0)
  {
    _pf.JMP(mklbl(_whileIni.top())); // jump to next cycle
    // std::cerr << "JMP" << std::endl;
  }
  else
    error(node->lineno(), "'again' outside 'while'");
}

void l22::postfix_writer::do_stop_node(l22::stop_node *const node, int lvl)
{
  if (_whileIni.size() != 0)
  {
    _pf.JMP(mklbl(_whileEnd.top())); // jump to end
    // std::cerr << "JMP" << std::endl;
  }
  else
    error(node->lineno(), "'stop' outside 'while'");
}

void l22::postfix_writer::do_program_node(l22::program_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  _function = new_symbol();
  _functions_to_declare.erase(_function->name()); // just in case
  reset_new_symbol();

  _offset = 8;    // prepare for arguments (4: remember to account for return address)
  _symtab.push(); // scope of args

  _currentBodyEnterLabel = "_main";
  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  // std::cerr << "TEXT" << std::endl;
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.GLOBAL("_main", _pf.FUNC());
  // std::cerr << "GLOBAL main, FUNC" << std::endl;
  _pf.LABEL("_main");
  // std::cerr << "LABEL main" << std::endl;

  frame_size_calculator lsc(_compiler, _symtab, _function);
  node->accept(&lsc, lvl);
  _pf.ENTER(lsc.localsize()); // total stack size reserved for local variables
  // std::cerr << "ENTER " << lsc.localsize() << std::endl;
  //_pf.ENTER(0); // Simple doesn't implement local variables

  _offset = 0; // prepare for local variable
  _inBlock = true;

  node->statements()->accept(this, lvl);

  // end the main function
  /*
  _pf.INT(0);
  //std::cerr << "INT 0" << std::endl;
  _pf.STFVAL32();
  //std::cerr << "STFVAL32" << std::endl;
  */
  _pf.LEAVE();
  // std::cerr << "LEAVE" << std::endl;
  _pf.RET();
  // std::cerr << "RET" << std::endl;

  _symtab.pop(); // scope of arguments

  _inBlock = false;

  // these are just a few library function imports
  for (std::string s : _functions_to_declare)
  {
    _pf.EXTERN(s);
    // std::cerr << "EXTERN " << s << std::endl;
  }
  // std::cerr << "FINAL" << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_sequence_node(cdk::sequence_node *const node, int lvl)
{
  for (size_t i = 0; i < node->size(); i++)
  {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_double_node(cdk::double_node *const node, int lvl)
{
  if (_inBlock)
  {
    _pf.DOUBLE(node->value()); // load number to the stack
    // std::cerr << "DOUBLE" << node->value() << std::endl;
  }

  else
  {
    _pf.SDOUBLE(node->value()); // double is on the DATA segment
    // std::cerr << "SDOUBLE" << node->value() << std::endl;
  }
}

void l22::postfix_writer::do_integer_node(cdk::integer_node *const node, int lvl)
{
  if (_inBlock)
  {
    _pf.INT(node->value());
    // std::cerr << "INT" << node->value() << std::endl;
  }

  else
  {
    _pf.SINT(node->value());
    // std::cerr << "SINT" << node->value() << std::endl;
  }
}

void l22::postfix_writer::do_string_node(cdk::string_node *const node, int lvl)
{
  int lbl1;

  _pf.RODATA(); // strings are DATA readonly
  // std::cerr << "RODATA" << std::endl;
  _pf.ALIGN(); // make sure we are aligned
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  // std::cerr << "LABEL " << mklbl(lbl1) << std::endl;
  _pf.SSTRING(node->value()); // output string characters
  // std::cerr << "SSTRING" << node->value() << std::endl;

  if (_inBlock)
  {
    if (!(_currentBodyEnterLabel == "_main"))
    {
      // local variable initializer
      _pf.TEXT(_currentBodyEnterLabel); // return to the TEXT segment
      // std::cerr << "TEXT" << _currentBodyEnterLabel << std::endl;
    }
    else
    {
      _pf.TEXT(); // return to the TEXT segment
      // std::cerr << "TEXT" << std::endl;
    }
    _pf.ADDR(mklbl(lbl1)); // the string to be printed
    // std::cerr << "ADDR " << mklbl(lbl1) << std::endl;
  }
  else
  {
    // global variable initializer
    _pf.DATA();
    // std::cerr << "DATA" << std::endl;
    _pf.SADDR(mklbl(lbl1));
    // std::cerr << "LABEL " << mklbl(lbl1) << std::endl;
  }
}

void l22::postfix_writer::do_nullptr_node(l22::nullptr_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  if (_inBlock)
  {
    _pf.INT(0);
    // std::cerr << "INT 0" << std::endl;
  }

  else
  {
    _pf.SINT(0);
    // std::cerr << "SINT 0" << std::endl;
  }
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_add_node(cdk::add_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->left()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  else if (node->is_typed(cdk::TYPE_POINTER) && node->left()->is_typed(cdk::TYPE_INT))
  {
    _pf.INT(8);
    // std::cerr << "INT 8" << std::endl;
    _pf.MUL();
    // std::cerr << "MUL" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  else if (node->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.INT(8);
    // std::cerr << "INT 8" << std::endl;
    _pf.MUL();
    // std::cerr << "MUL" << std::endl;
  }

  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    // std::cerr << "DADD" << std::endl;
    _pf.DADD();
  }

  else
  {
    // std::cerr << "ADD" << std::endl;
    _pf.ADD();
  }
}

void l22::postfix_writer::do_sub_node(cdk::sub_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->left()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "ID" << std::endl;
  }

  else if (node->is_typed(cdk::TYPE_POINTER) && node->left()->is_typed(cdk::TYPE_INT))
  {
    _pf.INT(8);
    // std::cerr << "INT 8" << std::endl;
    _pf.MUL();
    // std::cerr << "MUL" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  else if (node->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.INT(8);
    // std::cerr << "INT 8" << std::endl;
    _pf.MUL();
    // std::cerr << "MUL" << std::endl;
  }

  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DSUB();
    // std::cerr << "DSUB" << std::endl;
  }
  else if (node->is_typed(cdk::TYPE_INT) && !node->left()->is_typed(cdk::TYPE_POINTER))
  {
    _pf.SUB();
    // std::cerr << "SUB" << std::endl;
  }
  else
  {
    _pf.SUB();
    // std::cerr << "SUB" << std::endl;
    size_t size = cdk::reference_type::cast(node->left()->type())->referenced()->size();
    _pf.INT(size);
    // std::cerr << "INT" << size << std::endl;
    _pf.DIV();
    // std::cerr << "DIV" << std::endl;
  }
}

void l22::postfix_writer::do_mul_node(cdk::mul_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->left()->is_typed(cdk::TYPE_INT))
  {
    // std::cerr << "I2D" << std::endl;
    _pf.I2D();
  }

  node->right()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    // std::cerr << "I2D" << std::endl;
    _pf.I2D();
  }

  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    // std::cerr << "DMUL" << std::endl;
    _pf.DMUL();
  }

  else
  {
    // std::cerr << "MUL" << std::endl;
    _pf.MUL();
  }
}

void l22::postfix_writer::do_div_node(cdk::div_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->left()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DDIV();
    // std::cerr << "DDIV" << std::endl;
  }

  else
  {
    _pf.DIV();
    // std::cerr << "DIV" << std::endl;
  }
}

void l22::postfix_writer::do_mod_node(cdk::mod_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  _pf.MOD();
  // std::cerr << "MOD" << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_lt_node(cdk::lt_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) || node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT 0" << std::endl;
  }
  _pf.LT();
  // std::cerr << "LT" << std::endl;
}

void l22::postfix_writer::do_le_node(cdk::le_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) || node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT0)" << std::endl;
  }
  _pf.LE();
  // std::cerr << "LE" << std::endl;
}

void l22::postfix_writer::do_ge_node(cdk::ge_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) || node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT(0)" << std::endl;
  }
  _pf.GE();
  // std::cerr << "GE" << std::endl;
}

void l22::postfix_writer::do_gt_node(cdk::gt_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) || node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT(0)" << std::endl;
  }
  _pf.GT();
  // std::cerr << "GT" << std::endl;
}

void l22::postfix_writer::do_ne_node(cdk::ne_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->right()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT(0)" << std::endl;
  }

  _pf.NE();
  // std::cerr << "NE" << std::endl;
}

void l22::postfix_writer::do_eq_node(cdk::eq_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->left()->accept(this, lvl + 2);
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  node->right()->accept(this, lvl + 2);
  if (node->right()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.I2D();
    // std::cerr << "I2D" << std::endl;
  }

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.DCMP();
    // std::cerr << "DCMP" << std::endl;
    _pf.INT(0);
    // std::cerr << "INT(0)" << std::endl;
  }

  _pf.EQ();
  // std::cerr << "EQ" << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_not_node(cdk::not_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->argument()->accept(this, lvl + 2);
  _pf.INT(0);
  // std::cerr << "INT 0" << std::endl;
  _pf.EQ();
  // std::cerr << "EQ" << std::endl;
}

void l22::postfix_writer::do_and_node(cdk::and_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  // std::cerr << "DUP32" << std::endl;
  _pf.JZ(mklbl(lbl));
  // std::cerr << "JZ" << std::endl;
  node->right()->accept(this, lvl + 2);
  _pf.AND();
  // std::cerr << "AND" << std::endl;
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(mklbl(lbl));
  // std::cerr << "LABEL " << mklbl(lbl) << std::endl;
}

void l22::postfix_writer::do_or_node(cdk::or_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  // std::cerr << "DUP32" << std::endl;
  _pf.JNZ(mklbl(lbl));
  // std::cerr << "JNZ" << std::endl;
  node->right()->accept(this, lvl + 2);
  _pf.OR();
  // std::cerr << "OR" << std::endl;
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(mklbl(lbl));
  // std::cerr << "LABEL " << mklbl(lbl) << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_identity_node(l22::identity_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
}

void l22::postfix_writer::do_neg_node(cdk::neg_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG();                           // 2-complement
  // std::cerr << "NEG" << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_variable_node(cdk::variable_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  const std::string &id = node->name();
  auto symbol = _symtab.find(id);
  if (symbol->global())
  {
    _pf.ADDR(symbol->name());
  }
  else
  {
    _pf.LOCAL(symbol->offset());
  }
}

void l22::postfix_writer::do_rvalue_node(cdk::rvalue_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.LDDOUBLE();
    // std::cerr << "LDDOUBLE" << std::endl;
  }
  else
  {
    _pf.LDINT();
    // std::cerr << "LDINT" << std::endl;
  }
}

void l22::postfix_writer::do_evaluation_node(l22::evaluation_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.TRASH(node->argument()->type()->size());
  // std::cerr << "TRASH " << node->argument()->type()->size() << std::endl;
}

void l22::postfix_writer::do_write_node(l22::write_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->arguments()->accept(this, lvl);

  for (size_t ix = 0; ix < node->arguments()->size(); ++ix)
  {
    auto child = dynamic_cast<cdk::expression_node *>(node->arguments()->node(ix));

    if (child->is_typed(cdk::TYPE_INT))
    {
      _functions_to_declare.insert("printi");
      _pf.CALL("printi");
      // std::cerr << "CALL (printi)" << std::endl;
      _pf.TRASH(4); // trash int
      // std::cerr << "TRASH 4" << std::endl;
    }
    else if (child->is_typed(cdk::TYPE_DOUBLE))
    {
      _functions_to_declare.insert("printd");
      _pf.CALL("printd");
      // std::cerr << "CALL (printd)" << std::endl;
      _pf.TRASH(8); // trash double
      // std::cerr << "TRASH 8" << std::endl;
    }
    else if (child->is_typed(cdk::TYPE_STRING))
    {
      _functions_to_declare.insert("prints");
      _pf.CALL("prints");
      // std::cerr << "CALL (prints)" << std::endl;
      _pf.TRASH(4); // trash char pointer
      // std::cerr << "TRASH 4" << std::endl;
    }
    else
    {
      std::cerr << "cannot print expression of unknown type" << std::endl;
      return;
    }
  }

  if (node->newline())
  {
    _functions_to_declare.insert("println");
    _pf.CALL("println");
    // std::cerr << "CALL (println)" << std::endl;
  }
}

void l22::postfix_writer::do_input_node(l22::input_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  if (_lvalueType == cdk::TYPE_DOUBLE)
  {
    _functions_to_declare.insert("readd");
    _pf.CALL("readd");
    // std::cerr << "CALL (readd)" << std::endl;
    _pf.LDFVAL64();
    // std::cerr << "LDFVAL32" << std::endl;
  }
  else if (_lvalueType == cdk::TYPE_INT)
  {
    _functions_to_declare.insert("readi");
    _pf.CALL("readi");
    // std::cerr << "CALL (readi)" << std::endl;
    _pf.LDFVAL32();
    // std::cerr << "LDFVAL32" << std::endl;
  }
  else
  {
    std::cerr << "FATAL: " << node->lineno() << ": cannot read type" << std::endl;
    return;
  }
}

void l22::postfix_writer::do_while_node(l22::while_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  _whileIni.push(++_lbl);
  _whileEnd.push(++_lbl);

  _symtab.push();

  os() << "        ;; WHILE condition" << std::endl;
  // evaluate condition
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(mklbl(_whileIni.top()));
  // std::cerr << "LABEL " << mklbl(_whileIni.top()) << std::endl;
  node->condition()->accept(this, lvl + 2);
  _pf.JZ(mklbl(_whileEnd.top()));
  // std::cerr << "JZ" << std::endl;

  os() << "        ;; WHILE block" << std::endl;
  //_inBlock = true;
  // evaluate block
  node->block()->accept(this, lvl + 2);
  //_inBlock = false;
  _pf.JMP(mklbl(_whileIni.top()));
  // std::cerr << "JMP" << std::endl;

  os() << "        ;; WHILE end" << std::endl;
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(mklbl(_whileEnd.top()));
  // std::cerr << "LABEL " << mklbl(_whileEnd.top()) << std::endl;

  _symtab.pop();

  _whileIni.pop();
  _whileEnd.pop();
}

void l22::postfix_writer::do_if_node(l22::if_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  int if_end;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(if_end = ++_lbl));
  // std::cerr << "JZ" << std::endl;
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(if_end));
  // std::cerr << "LABEL " << mklbl(if_end) << std::endl;
}

void l22::postfix_writer::do_if_else_node(l22::if_else_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  int lbl_else, lbl_end;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl_else = ++_lbl));
  // std::cerr << "JZ" << std::endl;
  //_inBlock = true;
  node->thenblock()->accept(this, lvl + 2);
  //_inBlock = false;
  _pf.JMP(mklbl(lbl_end = ++_lbl));
  // std::cerr << "JMP" << std::endl;
  _pf.LABEL(mklbl(lbl_else));
  // std::cerr << "LABEL " << mklbl(lbl_else) << std::endl;
  //_inBlock = true;
  node->elseblock()->accept(this, lvl + 2);
  //_inBlock = false;
  _pf.LABEL(mklbl(lbl_else = lbl_end));
  // std::cerr << "LABEL " << mklbl(lbl_else) << std::endl;
}

void l22::postfix_writer::do_address_of_node(l22::address_of_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2);
}

void l22::postfix_writer::do_index_node(l22::index_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->base()->accept(this, lvl);
  node->index()->accept(this, lvl);

  auto base_type = cdk::reference_type::cast(node->base()->type());

  _pf.INT(base_type->referenced()->size());
  // std::cerr << "INT " << base_type->referenced()->size() << std::endl;
  _pf.MUL();
  // std::cerr << "MUL" << std::endl;
  _pf.ADD();
  // std::cerr << "ADD" << std::endl;
}

void l22::postfix_writer::do_sizeof_node(l22::sizeof_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  _pf.INT(node->expression()->type()->size());
  // std::cerr << "INT " << node->expression()->type()->size() << std::endl;
}

void l22::postfix_writer::do_stack_alloc_node(l22::stack_alloc_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  node->argument()->accept(this, lvl);
  _pf.INT(node->argument()->type()->size());
  // std::cerr << "INT " << node->argument()->type()->size() << std::endl;
  _pf.MUL();
  // std::cerr << "MUL" << std::endl;
  _pf.ADD();
  // std::cerr << "ADD" << std::endl;
  _pf.ALLOC();
  // std::cerr << "ALLOC" << std::endl;
  _pf.SP();
  // std::cerr << "SP" << std::endl;
}

//---------------------------------------------------------------------------

void l22::postfix_writer::do_assignment_node(cdk::assignment_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    if (node->rvalue()->is_typed(cdk::TYPE_INT))
    {
      _pf.I2D();
      // std::cerr << "I2D" << std::endl;
    }
    _pf.DUP64();
    // std::cerr << "DUP64" << std::endl;
  }
  else
  {
    _pf.DUP32();
    // std::cerr << "DUP32" << std::endl;
  }

  node->lvalue()->accept(this, lvl); // where to store the value

  if (node->is_typed(cdk::TYPE_DOUBLE))
  {
    _pf.STDOUBLE();
    // std::cerr << "STDOUBLE" << std::endl;
  }
  else
  {
    _pf.STINT();
    // std::cerr << "STINT" << std::endl;
  }
}

void l22::postfix_writer::do_variable_declaration_node(l22::variable_declaration_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  const std::string &id = node->identifier();

  /* calculate offset*/
  int offset = 0;
  int typesize = node->type()->size();

  if (_inFunctionArgs)
  {
    offset = _offset;
    _offset += typesize;
  }
  else if (_inBlock)
  {
    _offset -= typesize;
    offset = _offset;
  }
  else
  {
    offset = 0; // global variable
  }

  /* create symbol */
  auto symbol = new_symbol(); // symbol created in type_checker
  if (symbol)
  {
    symbol->set_offset(offset);
    reset_new_symbol();
  }

  /* the symbol is in a block (local variable) */
  if (_inBlock && !_inFunctionArgs)
  {
    /* only need to perform actions if the initializer exists */
    if (node->initializer())
    {
      node->initializer()->accept(this, lvl);
      if (node->is_typed(cdk::TYPE_INT) || node->is_typed(cdk::TYPE_STRING) || node->is_typed(cdk::TYPE_POINTER) || node->is_typed(cdk::TYPE_UNSPEC))
      {
        _pf.LOCAL(symbol->offset());
        // std::cerr << "LOCAL " << symbol->offset() << std::endl;
        _pf.STINT();
        // std::cerr << "STINT" << std::endl;
      }
      else if (node->is_typed(cdk::TYPE_DOUBLE))
      {
        if (node->initializer()->is_typed(cdk::TYPE_INT))
        {
          _pf.I2D();
          // std::cerr << "I2D" << std::endl;
        }
        _pf.LOCAL(symbol->offset());
        // std::cerr << "LOCAL " << symbol->offset() << std::endl;
        _pf.STDOUBLE();
        // std::cerr << "STDOUBLE" << std::endl;
      }
      else if (node->is_typed(cdk::TYPE_FUNCTIONAL))
      {
        // TODO
      }
      else
      {
        std::cerr << "cannot initialize" << std::endl;
      }
    }
  }

  /* the symbol is not in a block (global variable) */
  else if (!_inFunctionArgs)
  {
    /* the initializer doesn't exist: just create label */
    if (!node->initializer())
    {
      if (node->qualifier() == tFOREIGN)
      {
        _functions_to_declare.insert(id);
      }
      else if (node->qualifier() == tUSE)
      {
        // EMPTY
      }
      else
      {
        _pf.BSS();
        // std::cerr << "BSS" << std::endl;
        _pf.ALIGN();
        // std::cerr << "ALIGN" << std::endl;
        _pf.LABEL(id);
        // std::cerr << "LABEL " << id << std::endl;
        _pf.SALLOC(typesize);
        // std::cerr << "SALLOC " << typesize << std::endl;
      }
    }
    /* otherwise, create and initialize */
    else
    {
      if (node->is_typed(cdk::TYPE_INT) || node->is_typed(cdk::TYPE_DOUBLE) || node->is_typed(cdk::TYPE_POINTER) || node->is_typed(cdk::TYPE_STRING))
      {
        _pf.DATA();
        // std::cerr << "DATA" << std::endl;
        _pf.ALIGN();
        // std::cerr << "ALIGN" << std::endl;
        _pf.LABEL(id);
        // std::cerr << "LABEL " << id << std::endl;

        if (node->is_typed(cdk::TYPE_INT) || node->is_typed(cdk::TYPE_POINTER) || node->is_typed(cdk::TYPE_STRING))
        {
          node->initializer()->accept(this, lvl);
        }
        else if (node->is_typed(cdk::TYPE_DOUBLE))
        {
          if (node->initializer()->is_typed(cdk::TYPE_DOUBLE))
            node->initializer()->accept(this, lvl);
          else if (node->initializer()->is_typed(cdk::TYPE_INT))
          {
            cdk::integer_node *dclini = dynamic_cast<cdk::integer_node *>(node->initializer());
            cdk::double_node ddi(dclini->lineno(), dclini->value());
            ddi.accept(this, lvl);
          }
          else
          {
            std::cerr << node->lineno() << ": '" << id << "' has bad initializer for real value\n";
          }
        }
      }
      else if (node->is_typed(cdk::TYPE_FUNCTIONAL))
      {

        _pf.DATA();
        // std::cerr << "DATA" << std::endl;
        _pf.ALIGN();
        // std::cerr << "ALIGN" << std::endl;
        _pf.GLOBAL(id, _pf.OBJ());
        // std::cerr << "GLOBAL " << id << ", OBJ" << std::endl;
        _pf.LABEL(id);
        // std::cerr << "LABEL " << id << std::endl;

        node->initializer()->accept(this, lvl);
      }
      else
      {
        std::cerr << node->lineno() << ": '" << id << "' has unexpected initializer\n";
      }
    }
  }
}

void l22::postfix_writer::do_return_node(l22::return_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  auto output = cdk::functional_type::cast(_function->type())->output(0);
  if (output->name() != cdk::TYPE_VOID)
  {
    node->retval()->accept(this, lvl + 2);

    if (output->name() == cdk::TYPE_INT || output->name() == cdk::TYPE_STRING || output->name() == cdk::TYPE_POINTER)
    {
      _pf.STFVAL32();
      // std::cerr << "STFVAL32" << std::endl;
    }
    else if (output->name() == cdk::TYPE_DOUBLE)
    {
      if (node->retval()->is_typed(cdk::TYPE_INT))
      {
        _pf.I2D();
        // std::cerr << "I2D" << std::endl;
      }
      _pf.STFVAL64();
    }
    else if (output->name() == cdk::TYPE_FUNCTIONAL)
    { // EMPTY
    }
    else
    {
      std::cerr << node->lineno() << ": should not happen: unknown return type" << std::endl;
    }

    if (_currentBodyRetLabel.length() > 0)
    {
      _pf.JMP(_currentBodyRetLabel);
      // std::cerr << "JMP " << _currentBodyRetLabel << std::endl;
      _returnSeen = true;
    }
  }
}

void l22::postfix_writer::do_function_definition_node(l22::function_definition_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  _function = new_symbol(); // get the symbol we created in type_checker
  _functions_to_declare.erase(_function->name());
  reset_new_symbol(); // reset for future symbols

  _currentBodyRetLabel = std::string(mklbl(++_lbl));

  _offset = 8;
  _symtab.push();

  if (node->arguments()->size() > 0)
  {
    _inFunctionArgs = true; // FIXME really needed?
    for (size_t ix = 0; ix < node->arguments()->size(); ix++)
    {
      l22::variable_declaration_node *arg = dynamic_cast<l22::variable_declaration_node *>(node->arguments()->node(ix));
      if (arg == nullptr)
        break;              // this means an empty sequence of arguments
      arg->accept(this, 0); // the function symbol is at the top of the stack
    }
    _inFunctionArgs = false; // FIXME really needed?
  }
  /* Defining the label for the */
  _currentBodyEnterLabel = std::string(mklbl(++_lbl));

  _pf.TEXT(_currentBodyEnterLabel);
  // std::cerr << "TEXT " << _currentBodyEnterLabel << std::endl;
  _pf.ALIGN();
  // std::cerr << "ALIGN" << std::endl;
  _pf.LABEL(_currentBodyEnterLabel);
  // std::cerr << "LABEL " << _currentBodyEnterLabel << std::endl;

  frame_size_calculator lsc(_compiler, _symtab, _function);
  node->accept(&lsc, lvl);
  _pf.ENTER(lsc.localsize()); // total stack size reserved for local variables
  // std::cerr << "ENTER " << lsc.localsize() << std::endl;

  _offset = 0;
  bool reset = false;
  _inBlock ? reset = false : reset = true;
  _inBlock = true;
  node->block()->accept(this, lvl + 2); // block has its own scope
  reset ? _inBlock = false : _inBlock = true;
  _returnSeen = false;
  _pf.LABEL(_currentBodyRetLabel);
  // std::cerr << "LABEL " << _currentBodyRetLabel << std::endl;
  _pf.LEAVE();
  // std::cerr << "LEAVE" << std::endl;
  _pf.RET();
  // std::cerr << "RET" << std::endl;

  if (_inBlock)
  {
    _pf.TEXT();
    // std::cerr << "TEXT" << std::endl;
    _pf.ALIGN();
    // std::cerr << "ALIGN" << std::endl;
    _pf.ADDR(_currentBodyEnterLabel);
    // std::cerr << "ADDR " << _currentBodyEnterLabel << std::endl;
  }
  else
  {
    _pf.DATA();
    // std::cerr << "DATA" << std::endl;
    _pf.ALIGN();
    // std::cerr << "ALIGN" << std::endl;
    _pf.SADDR(_currentBodyEnterLabel);
    // std::cerr << "SADDR " << _currentBodyEnterLabel << std::endl;
  }

  _symtab.pop();
}

void l22::postfix_writer::do_function_call_node(l22::function_call_node *const node, int lvl)
{
  ASSERT_SAFE_EXPRESSIONS;

  auto rval = dynamic_cast<cdk::rvalue_node *>(node->pointer());
  auto var = dynamic_cast<cdk::variable_node *>(rval->lvalue());
  auto symbol = _symtab.find(var->name());
  size_t argsSize = 0;
  if (node->arguments()->size() > 0)
  {
    for (int ax = node->arguments()->size() - 1; ax >= 0; ax--)
    {
      cdk::expression_node *arg = node->argument(ax);
      arg->accept(this, lvl + 2);
      auto input_type = cdk::functional_type::cast(symbol->type())->input(ax);
      if (input_type->name() == cdk::TYPE_DOUBLE)
      {
        _pf.I2D();
        // std::cerr << "I2D" << std::endl;
      }
      argsSize += input_type->size();
    }
  }

  if (symbol->qualifier() == tFOREIGN)
  {
    _pf.CALL(var->name());
    // std::cerr << "CALL " << var->name() << std::endl;
    if (cdk::functional_type::cast(symbol->type())->output(0)->name() == cdk::TYPE_DOUBLE)
    {
      _pf.LDFVAL64();
      //std::cerr << "LDFVAL64" << std::endl;
    }
    else
    {
      _pf.LDFVAL32();
      //std::cerr << "LDFVAL32" << std::endl;
    }
    _pf.TRASH(argsSize);
    // std::cerr << "TRASH " << argsSize << std::endl;
  }

  else
  {
    node->pointer()->accept(this, lvl + 2);
    _pf.BRANCH();
    // std::cerr << "BRANCH" << std::endl;

    if (cdk::functional_type::cast(symbol->type())->output(0)->name() == cdk::TYPE_DOUBLE)
    {
      _pf.LDFVAL64();
      // std::cerr << "LDFVAL64" << std::endl;
    }
    else
    {
      _pf.LDFVAL32();
      // std::cerr << "LDFVAL32" << std::endl;
    }
  }
}

//---------------------------------------------------------------------------
//-----------------------     T H E    E N D     ----------------------------
//---------------------------------------------------------------------------
