#include <string>
#include "targets/type_checker.h"
#include ".auto/all_nodes.h" // automatically generated
#include <cdk/types/primitive_type.h>

#include "l22_parser.tab.h"

#define ASSERT_UNSPEC                                                 \
  {                                                                   \
    if (node->type() != nullptr && !node->is_typed(cdk::TYPE_UNSPEC)) \
      return;                                                         \
  }

//---------------------------------------------------------------------------

void l22::type_checker::do_sweep_node(l22::sweep_node * const node, int lvl) {
  node->vector()->accept(this, lvl + 2);
  if (!node->vector()->is_typed(cdk::TYPE_POINTER))
    throw std::string("vector (pointer) expected");
  
  node->low()->accept(this, lvl + 2);
  if (!node->low()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expected for lower bound");

  node->high()->accept(this, lvl + 2);
  if (!node->high()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expected for upper bound");

  node->condition()->accept(this, lvl + 2);
  if (!node->condition()->is_typed(cdk::TYPE_INT))
    throw std::string("integer evaluating condition expected");
  
  node->function()->accept(this, lvl + 2);
  if (!node->function()->is_typed(cdk::TYPE_FUNCTIONAL))
    throw std::string("function expected");
  
  auto fun_type = cdk::functional_type::cast(node->function()->type());
  if (fun_type->input_length() != 1)
    throw std::string("function can only receive 1 argument");
  
  auto ref_type = cdk::reference_type::cast(node->vector()->type());
  if (fun_type->input(0)->name() != ref_type->referenced()->name())
    throw std::string("function input and vector elements must have the same type");
  else if (fun_type->input(0)->name() == cdk::TYPE_FUNCTIONAL) 
    check_functional_types(cdk::functional_type::cast(fun_type->input(0)), cdk::functional_type::cast(ref_type->referenced()));
  else if (fun_type->input(0)->name() == cdk::TYPE_POINTER)
    check_pointer_types(cdk::reference_type::cast(fun_type->input(0)), cdk::reference_type::cast(ref_type->referenced()));  
}

void l22::type_checker::do_with_change_node(l22::with_change_node * const node, int lvl) {
  node->function()->accept(this, lvl + 2);
  if (!node->function()->is_typed(cdk::TYPE_FUNCTIONAL))
    throw std::string("function required.");
  
  auto fun_type = cdk::functional_type::cast(node->function()->type());
  if (fun_type->input_length() != 1)
    throw std::string("function can only receive 1 argument.");

  node->vector()->accept(this, lvl + 2);
  if (!node->vector()->is_typed(cdk::TYPE_POINTER))
    throw std::string("vector required.");
  
  auto vec_type = cdk::reference_type::cast(node->vector()->type());

  /* check type match: input and vector element */
  if (fun_type->input(0)->name() != vec_type->referenced()->name())
    throw std::string("function input and vector elements must have matching types.");
  else if (fun_type->input(0)->name() == cdk::TYPE_FUNCTIONAL) {
    auto in_type = cdk::functional_type::cast(fun_type->input(0));
    auto el_type = cdk::functional_type::cast(vec_type->referenced());
    check_functional_types(in_type, el_type);
  }
  else if (fun_type->input(0)->name() == cdk::TYPE_POINTER) {
    auto in_type = cdk::reference_type::cast(fun_type->input(0));
    auto el_type = cdk::reference_type::cast(vec_type->referenced());
    check_pointer_types(in_type, el_type);
  }

  node->low()->accept(this, lvl + 2);
  if (!node->low()->is_typed(cdk::TYPE_INT))
    throw std::string("lower bound must be integer.");
  node->high()->accept(this, lvl + 2);
  if (!node->high()->is_typed(cdk::TYPE_INT))
    throw std::string("upper bound must be integer.");
}

//---------------------------------------------------------------------------

void l22::type_checker::do_data_node(cdk::data_node *const node, int lvl)
{
  // EMPTY
}

void l22::type_checker::do_nil_node(cdk::nil_node *const node, int lvl)
{
  // EMPTY
}

void l22::type_checker::do_block_node(l22::block_node *const node, int lvl)
{
  // EMPTY
}

void l22::type_checker::do_again_node(l22::again_node *const node, int lvl)
{
  // EMPTY
}

void l22::type_checker::do_stop_node(l22::stop_node *const node, int lvl)
{
  // EMPTY
}

void l22::type_checker::do_program_node(l22::program_node *const node, int lvl)
{
  auto function = l22::make_symbol(cdk::functional_type::create(cdk::primitive_type::create(4, cdk::TYPE_INT)), "_main", tPRIVATE);
  _symtab.insert(function->name(), function);
  _parent->set_new_symbol(function);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_sequence_node(cdk::sequence_node *const node, int lvl)
{
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_double_node(cdk::double_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
}

void l22::type_checker::do_integer_node(cdk::integer_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::do_string_node(cdk::string_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(4, cdk::TYPE_STRING));
}

void l22::type_checker::do_nullptr_node(l22::nullptr_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(4, cdk::TYPE_POINTER));
}

//---------------------------------------------------------------------------

void l22::type_checker::do_add_node(cdk::add_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  processScalarPIDExpression(node, lvl);
}

void l22::type_checker::do_sub_node(cdk::sub_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (node->left()->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_POINTER))
  {
    check_pointer_types(cdk::reference_type::cast(node->left()->type()), cdk::reference_type::cast(node->right()->type()));
    node->type(cdk::primitive_type::create(8, cdk::TYPE_INT));
  }
  else
    processScalarPIDExpression(node, lvl);
}

void l22::type_checker::do_mul_node(cdk::mul_node *const node, int lvl)
{
  processScalarIDExpression(node, lvl);
}

void l22::type_checker::do_div_node(cdk::div_node *const node, int lvl)
{
  processScalarIDExpression(node, lvl);
}

void l22::type_checker::do_mod_node(cdk::mod_node *const node, int lvl)
{
  processScalarIntOnlyExpression(node, lvl);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_lt_node(cdk::lt_node *const node, int lvl)
{
  processScalarLogicalExpression(node, lvl);
}

void l22::type_checker::do_le_node(cdk::le_node *const node, int lvl)
{
  processScalarLogicalExpression(node, lvl);
}

void l22::type_checker::do_ge_node(cdk::ge_node *const node, int lvl)
{
  processScalarLogicalExpression(node, lvl);
}

void l22::type_checker::do_gt_node(cdk::gt_node *const node, int lvl)
{
  processScalarLogicalExpression(node, lvl);
}

void l22::type_checker::do_ne_node(cdk::ne_node *const node, int lvl)
{
  processGeneralLogicalExpression(node, lvl);
}

void l22::type_checker::do_eq_node(cdk::eq_node *const node, int lvl)
{
  processGeneralLogicalExpression(node, lvl);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_not_node(cdk::not_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->argument()->accept(this, lvl + 2);
  if (node->argument()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));

  // input node
  else if (node->argument()->is_typed(cdk::TYPE_UNSPEC))
  {
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    node->argument()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  else
    throw std::string("wrong type in unary logical expression (not)");
}

void l22::type_checker::do_and_node(cdk::and_node *const node, int lvl)
{
  processLogicalIntOnlyExpression(node, lvl);
}

void l22::type_checker::do_or_node(cdk::or_node *const node, int lvl)
{
  processLogicalIntOnlyExpression(node, lvl);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_identity_node(l22::identity_node *const node, int lvl)
{
  processUnaryExpression(node, lvl);
}

void l22::type_checker::do_neg_node(cdk::neg_node *const node, int lvl)
{
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_variable_node(cdk::variable_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  auto symbol = _symtab.find(id);

  if (symbol != nullptr)
  {
    node->type(symbol->type());
  }
  else
  {
    throw std::string("undeclared variable '" + id + "'");
  }
}

void l22::type_checker::do_rvalue_node(cdk::rvalue_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  try
  {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  }
  catch (const std::string &id)
  {
    throw "undeclared variable '" + id + "'";
  }
}

void l22::type_checker::do_evaluation_node(l22::evaluation_node *const node, int lvl)
{
  node->argument()->accept(this, lvl + 2);
}

void l22::type_checker::do_write_node(l22::write_node *const node, int lvl)
{
  node->arguments()->accept(this, lvl + 2);

  for (size_t i = 0; i < node->arguments()->size(); i++)
  {
    cdk::expression_node *expression = dynamic_cast<cdk::expression_node *>(node->arguments()->node(i));
    if (expression != nullptr && (expression->is_typed(cdk::TYPE_VOID) || expression->is_typed(cdk::TYPE_POINTER)))
    {
      throw std::string("Wrong type in write arguments.");
    }
  }
}

void l22::type_checker::do_input_node(l22::input_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(0, cdk::TYPE_UNSPEC));
}

void l22::type_checker::do_while_node(l22::while_node *const node, int lvl)
{
  node->condition()->accept(this, lvl + 4);
  // condition needs to evaluate to true or false -> type int
  if (!node->condition()->is_typed(cdk::TYPE_INT))
    throw std::string("expected integer condition");
}

void l22::type_checker::do_if_node(l22::if_node *const node, int lvl)
{
  node->condition()->accept(this, lvl + 4);

  if (!node->condition()->is_typed(cdk::TYPE_INT))
    throw std::string("expected integer condition");
}

void l22::type_checker::do_if_else_node(l22::if_else_node *const node, int lvl)
{
  node->condition()->accept(this, lvl + 4);
  // condition needs to evaluate to true or false -> type int
  if (!node->condition()->is_typed(cdk::TYPE_INT))
    throw std::string("expected integer condition");
}

void l22::type_checker::do_address_of_node(l22::address_of_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  node->type(cdk::reference_type::create(4, node->argument()->type()));
}

void l22::type_checker::do_index_node(l22::index_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->base()->accept(this, lvl + 2);

  if (!node->base()->is_typed(cdk::TYPE_POINTER))
    throw std::string("pointer expression expected in index left-value");

  auto base_type = cdk::reference_type::cast(node->base()->type());

  if (base_type->referenced()->name() == cdk::TYPE_FUNCTIONAL)
    throw std::string("cannot index pointers do functions");

  node->index()->accept(this, lvl + 2);
  if (!node->index()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expected in left-value index");

  node->type(base_type->referenced());
}

void l22::type_checker::do_sizeof_node(l22::sizeof_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->expression()->accept(this, lvl + 2);
  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::do_stack_alloc_node(l22::stack_alloc_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (!node->argument()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expression expected in allocation expression");

  auto alloc_type = cdk::reference_type::create(4, cdk::primitive_type::create(node->argument()->type()->size(), node->argument()->type()->name()));
  node->type(alloc_type);
}

//---------------------------------------------------------------------------

void l22::type_checker::do_assignment_node(cdk::assignment_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->lvalue()->accept(this, lvl + 2);
  node->rvalue()->accept(this, lvl + 2);

  // Assignment to integer
  if (node->lvalue()->is_typed(cdk::TYPE_INT))
  {
    if (node->rvalue()->is_typed(cdk::TYPE_INT))
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));

    else if (node->rvalue()->is_typed(cdk::TYPE_UNSPEC))
    {
      node->rvalue()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    }
    else
      throw std::string("wrong assigment to integer.");
  }

  // Assignment to double
  else if (node->lvalue()->is_typed(cdk::TYPE_DOUBLE))
  {
    if (node->rvalue()->is_typed(cdk::TYPE_INT) || node->rvalue()->is_typed(cdk::TYPE_DOUBLE))
    {
      node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
    }
    else if (node->rvalue()->is_typed(cdk::TYPE_UNSPEC))
    {
      node->rvalue()->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
      node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
    }
    else
      throw std::string("wrong assigment to double.");
  }

  // Assignment to string
  else if (node->lvalue()->is_typed(cdk::TYPE_STRING))
  {
    if (node->rvalue()->is_typed(cdk::TYPE_STRING))
      node->type(cdk::primitive_type::create(4, cdk::TYPE_STRING));
    else
      throw std::string("wrong assigment to string.");
  }

  // Assignment to pointer
  else if (node->lvalue()->is_typed(cdk::TYPE_POINTER))
  {
    if (node->rvalue()->is_typed(cdk::TYPE_POINTER))
    {
      check_pointer_types(cdk::reference_type::cast(node->lvalue()->type()), cdk::reference_type::cast(node->rvalue()->type()));
      node->type(node->lvalue()->type());
    }
    else if (node->rvalue()->is_typed(cdk::TYPE_INT))
    {
      auto check_zero = dynamic_cast<cdk::integer_node *>(node->rvalue());
      if (check_zero->value() != 0)
        throw std::string("expected 0 in assignment to pointer.");
      node->type(cdk::primitive_type::create(4, cdk::TYPE_POINTER));
    }
    else
      throw std::string("wrong assignment to pointer.");
  }

  else if (node->lvalue()->is_typed(cdk::TYPE_FUNCTIONAL))
  {
    if (!node->rvalue()->is_typed(cdk::TYPE_FUNCTIONAL))
      throw std::string("wrong assignment to function.");
    check_functional_types(cdk::functional_type::cast(node->lvalue()->type()), cdk::functional_type::cast(node->rvalue()->type()));
    node->type(node->rvalue()->type());
  }
}

void l22::type_checker::do_variable_declaration_node(l22::variable_declaration_node *const node, int lvl)
{
  /* Variaveis inicializadas */
  if (node->initializer())
  {
    node->initializer()->accept(this, lvl + 2);

    auto pointer_ini = dynamic_cast<cdk::integer_node *>(node->initializer());
    if (pointer_ini && pointer_ini->value() == 0 && node->type() && node->is_typed(cdk::TYPE_POINTER))
    {
      node->type(cdk::primitive_type::create(4, cdk::TYPE_POINTER));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_INT))
    {
      if (node->type() && !node->is_typed(cdk::TYPE_INT) && !node->is_typed(cdk::TYPE_DOUBLE))
        throw std::string("wrong type for initializer.");
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_DOUBLE))
    {
      if (node->type() && !node->is_typed(cdk::TYPE_DOUBLE))
        throw std::string("wrong type for initializer.");
      node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_STRING))
    {
      if (node->type() && !node->is_typed(cdk::TYPE_STRING))
        throw std::string("wrong type for initializer.");
      node->type(cdk::primitive_type::create(4, cdk::TYPE_STRING));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_POINTER))
    {
      if (node->type() && !node->is_typed(cdk::TYPE_POINTER))
        throw std::string("wrong type for initializer.");
      check_pointer_types(cdk::reference_type::cast(node->type()), cdk::reference_type::cast(node->initializer()->type()));
      node->type(cdk::reference_type::cast(node->initializer()->type()));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_UNSPEC))
    {
      if (node->type() && !(node->is_typed(cdk::TYPE_UNSPEC) || !node->is_typed(cdk::TYPE_DOUBLE) || !node->is_typed(cdk::TYPE_INT)))
        throw std::string("wrong type for initializer.");
      node->type(cdk::primitive_type::create(4, cdk::TYPE_UNSPEC));
    }

    else if (node->initializer()->is_typed(cdk::TYPE_FUNCTIONAL))
    {
      /* if the node doesn't have a functional type, it has to have the output type */
      if ((!node->is_typed(cdk::TYPE_FUNCTIONAL)) && (node->type() != cdk::functional_type::cast(node->initializer()->type())->output(0)))
        throw std::string("wrong type for initializer.1");

      if (node->is_typed(cdk::TYPE_FUNCTIONAL))
      {
        check_functional_types(cdk::functional_type::cast(node->initializer()->type()), cdk::functional_type::cast(node->type()));
      }
      /* check types */
      node->type(cdk::functional_type::cast(node->initializer()->type()));
    }
    else
      throw std::string("unknown type for initializer.");
  }

  const std::string &id = node->identifier();
  auto symbol = l22::make_symbol(node->type(), id, node->qualifier());
  if (_symtab.insert(id, symbol))
    _parent->set_new_symbol(symbol); // advise parent that a symbol has been inserted
  else if (node->initializer() && !node->initializer()->is_typed(cdk::TYPE_FUNCTIONAL))
    throw std::string("variable '" + id + "' redeclared");
}

void l22::type_checker::do_return_node(l22::return_node *const node, int lvl)
{
  if (node->retval())
  {
    auto out_type = cdk::functional_type::cast(_function->type())->output(0);
    auto in_types = cdk::functional_type::cast(_function->type())->input();
    if (out_type != nullptr && out_type->name() == cdk::TYPE_VOID)
      throw std::string("return specified for void function.");
    node->retval()->accept(this, lvl + 2);
    if (_inBlockReturnType == nullptr)
    {
      _inBlockReturnType = node->retval()->type();
    }

    else
    {
      if (_inBlockReturnType != node->retval()->type())
      {
        throw std::string("all return statements in a function must return the same type.");
      }
    }

    if (node->retval()->is_typed(cdk::TYPE_FUNCTIONAL))
    {
      if (cdk::functional_type::cast(node->retval()->type())->output(0)->name() != out_type->name())
        throw std::string("wrong type for initializer.");
    }
    else if (out_type->name() == cdk::TYPE_INT)
    {
      if (!node->retval()->is_typed(cdk::TYPE_INT))
        throw std::string("wrong type for initializer (integer expected).");
    }

    else if (out_type->name() == cdk::TYPE_DOUBLE)
    {
      if (!node->retval()->is_typed(cdk::TYPE_INT) && !node->retval()->is_typed(cdk::TYPE_DOUBLE))
      {
        throw std::string("wrong type for initializer (integer or double expected).");
      }
    }
    else if (out_type->name() == cdk::TYPE_STRING)
    {
      if (!node->retval()->is_typed(cdk::TYPE_STRING))
      {
        throw std::string("wrong type for initializer (string expected).");
      }
    }
    else if (out_type->name() == cdk::TYPE_POINTER)
    {
      check_pointer_types(cdk::reference_type::cast(out_type), cdk::reference_type::cast(node->retval()->type()));
    }
    else if (out_type->name() == cdk::TYPE_FUNCTIONAL)
    {
      check_functional_types(cdk::functional_type::cast(out_type), cdk::functional_type::cast(node->retval()->type()));
    }
    else
    {
      throw std::string("unknown type for initializer.");
    }
  }
}

void l22::type_checker::do_function_definition_node(l22::function_definition_node *const node, int lvl)
{
  _inBlockReturnType = nullptr;

  /* construct functional type */
  if (!node->is_typed(cdk::TYPE_FUNCTIONAL))
  {
    std::shared_ptr<cdk::basic_type> output = node->type();

    std::vector<std::shared_ptr<cdk::basic_type>> arg_types;
    for (size_t ax = 0; ax < node->arguments()->size(); ++ax)
    {
      arg_types.push_back(dynamic_cast<l22::variable_declaration_node *>(node->arguments()->node(ax))->type());
    }

    arg_types.size() > 0 ? node->type(cdk::functional_type::create(arg_types, output)) : node->type(cdk::functional_type::create(output));
  }

  /* create (auxiliary) symbol */
  auto function = l22::make_symbol(node->type(), "batata", tPRIVATE);
  _symtab.insert(function->name(), function);
  _parent->set_new_symbol(function);
}

void l22::type_checker::do_function_call_node(l22::function_call_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  std::shared_ptr<cdk::functional_type> funType;
  std::shared_ptr<l22::symbol> symbol;
  if (!node->pointer())
  {
    symbol = _symtab.find("batata", 1);
    funType = cdk::functional_type::cast(symbol->type());
    if (!symbol)
      throw std::string("symbol is undeclared.");
    if (!symbol->is_typed(cdk::TYPE_FUNCTIONAL))
      throw std::string("symbol is not a function.");
  }
  else
  {
    node->pointer()->accept(this, lvl + 2);
    funType = cdk::functional_type::cast(node->pointer()->type());
  }

  node->type(funType->output(0));

  if (node->arguments()->size() == funType->input_length())
  {
    node->arguments()->accept(this, lvl + 4);
    for (size_t ax = 0; ax < node->arguments()->size(); ax++)
    {
      if (node->argument(ax)->type() == funType->input(ax))
        continue;

      if (node->argument(ax)->is_typed(cdk::TYPE_INT) && (funType->input(ax)->name() == cdk::TYPE_DOUBLE))
        continue;

      throw std::string("type mismatch in function call arguments");
    }
  }
  else
  {
    throw std::string("wrong number of arguments. " + std::to_string(node->arguments()->size()) + " were given; " + std::to_string(funType->input_length()) + "expected.");
  }
}

//---------------------------------------------------------------------------

void l22::type_checker::processScalarIntOnlyExpression(cdk::binary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expression expected in binary operator (left)");

  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expression expected in binary operator (right)");

  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::processLogicalIntOnlyExpression(cdk::binary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expression expected in binary logical expression (left)");

  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_INT))
    throw std::string("integer expression expected in binary logical expression (right)");

  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::processScalarPIDExpression(cdk::binary_operation_node *const node, int lvl)
{
  // 2 doubles -> double
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_DOUBLE))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));

  // 1 double and 1 int -> double
  else if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
  else if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));

  // 1 int and 1 pointer -> pointer
  else if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_POINTER))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_POINTER));
  else if (node->left()->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_POINTER));

  // 2 ints -> int
  else if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));

  else if (node->left()->is_typed(cdk::TYPE_UNSPEC) && node->right()->is_typed(cdk::TYPE_UNSPEC))
  {
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    node->left()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    node->right()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  else
    throw std::string("wrong types in binary expression");
}

void l22::type_checker::processScalarIDExpression(cdk::binary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  // 2 doubles -> double
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_DOUBLE))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));

  // 1 int and 1 double -> double
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_DOUBLE))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
  if (node->left()->is_typed(cdk::TYPE_DOUBLE) && node->right()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));

  // 2 ints -> int
  if (node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));

  else if (node->left()->is_typed(cdk::TYPE_UNSPEC) && node->right()->is_typed(cdk::TYPE_UNSPEC))
  {
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    node->left()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    node->right()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  else
    throw std::string("wrong types in binary expression");
}

void l22::type_checker::processScalarLogicalExpression(cdk::binary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_INT) && !node->left()->is_typed(cdk::TYPE_DOUBLE))
    throw std::string("integer or double expression expected in binary logical expression (left)");

  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_INT) && !node->right()->is_typed(cdk::TYPE_DOUBLE))
    throw std::string("integer or double expression expected in binary logical expression (right)");

  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::processGeneralLogicalExpression(cdk::binary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_INT) && !node->left()->is_typed(cdk::TYPE_DOUBLE) && !node->left()->is_typed(cdk::TYPE_POINTER))
    throw std::string("only integer, double and pointer accepted for comparison (left)");

  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_INT) && !node->right()->is_typed(cdk::TYPE_DOUBLE) && !node->right()->is_typed(cdk::TYPE_POINTER))
    throw std::string("only integer, double and pointer accepted for comparison (right)");

  if ((node->left()->is_typed(cdk::TYPE_POINTER) && !node->right()->is_typed(cdk::TYPE_POINTER)) ||
      (!node->left()->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_POINTER)))
    throw std::string("pointer can only be compared with other pointer.");

  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void l22::type_checker::processUnaryExpression(cdk::unary_operation_node *const node, int lvl)
{
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (!node->argument()->is_typed(cdk::TYPE_INT) && !node->argument()->is_typed(cdk::TYPE_DOUBLE))
    throw std::string("wrong type in argument of unary expression");

  if (node->argument()->is_typed(cdk::TYPE_INT))
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));

  else if (node->argument()->is_typed(cdk::TYPE_DOUBLE))
    node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
}

//---------------------------------------------------------------------------

void l22::type_checker::check_pointer_types(std::shared_ptr<cdk::reference_type> pointer1, std::shared_ptr<cdk::reference_type> pointer2)
{
  int lvl1 = 0;
  int lvl2 = 0;

  auto ref1 = pointer1->referenced();
  auto ref2 = pointer2->referenced();

  while (true)
  {
    if (ref1->name() != cdk::TYPE_POINTER)
      break;
    lvl1++;
    ref1 = cdk::reference_type::cast(ref1)->referenced();
  }

  while (true)
  {
    if (ref2->name() != cdk::TYPE_POINTER)
      break;
    lvl2++;
    ref2 = cdk::reference_type::cast(ref2)->referenced();
  }

  if (lvl1 != lvl2)
    throw std::string("Pointer leves differ in operation.");
  if (ref1->name() != cdk::TYPE_INT && ref1->name() != cdk::TYPE_DOUBLE && ref2->name() != cdk::TYPE_INT && ref2->name() != cdk::TYPE_DOUBLE)
  {
    if (ref1->name() != ref2->name())
      throw std::string("Pointer types differ in operation.");
  }
}

void l22::type_checker::check_functional_types(std::shared_ptr<cdk::functional_type> fun_type1, std::shared_ptr<cdk::functional_type> fun_type2)
{
  if ((fun_type1->input_length() != fun_type2->input_length()) || (fun_type1->output_length() != fun_type2->output_length()))
    throw std::string("functional types differ");
  for (size_t ix = 0; ix < fun_type1->input_length(); ix++)
  {
    if (fun_type1->input(ix) != fun_type2->input(ix))
      throw std::string("functional types differ");
  }
  /* hack -> there is always only 1 output */
  if (fun_type1->output(0) != fun_type2->output(0))
    throw std::string("functional types differ");
}

//---------------------------------------------------------------------------
//-----------------------     T H E    E N D     ----------------------------
//---------------------------------------------------------------------------
