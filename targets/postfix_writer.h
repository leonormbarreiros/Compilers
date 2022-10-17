#ifndef __L22_TARGETS_POSTFIX_WRITER_H__
#define __L22_TARGETS_POSTFIX_WRITER_H__

#include "targets/basic_ast_visitor.h"

#include <set>
#include <stack>
#include <sstream>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include <cdk/types/reference_type.h>
#include <cdk/types/functional_type.h>
#include <cdk/types/primitive_type.h>

namespace l22
{

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer : public basic_ast_visitor
  {
    cdk::symbol_table<l22::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;

    // Added
    std::set<std::string> _functions_to_declare;
    bool _inFunctionArgs;
    bool _inBlock;
    bool _inWhileInit;
    bool _returnSeen; // when building a function

    std::stack<int> _whileIni, _whileEnd; // for stop/again

    int _offset; // current framepointer offset (0 means no vars defined)
    cdk::typename_type _lvalueType;

    std::shared_ptr<l22::symbol> _function;

    // remember function name for resolving '@'
    std::string _currentFunctionName;
    std::string _currentBodyRetLabel;   // where to jump when a return occurs of an exclusive section ends
    std::string _currentBodyEnterLabel; // where to jump when a return occurs in the end section
    int _currentBodyEnterLabel2;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<l22::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) : basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0), _inFunctionArgs(false),
                                                     _inBlock(false), _inWhileInit(false), _returnSeen(false), _offset(0),
                                                     _lvalueType(cdk::TYPE_VOID), _function(nullptr), _currentFunctionName(""), _currentBodyRetLabel(""), _currentBodyEnterLabel(""),
                                                     _currentBodyEnterLabel2(0) {}

  public:
    ~postfix_writer()
    {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl)
    {
      std::ostringstream oss;
      if (lbl < 0)
      {
        oss << ".L" << -lbl;
      }
      else
      {
        oss << "_L" << lbl;
      }
      std::string label = oss.str();
      return label;
    }

    void error(int lineno, std::string s)
    {
      std::cerr << "error: " << lineno << ": " << s << std::endl;
    }

  public:
    // do not edit these lines
#define __IN_VISITOR_HEADER__
#include ".auto/visitor_decls.h" // automatically generated
#undef __IN_VISITOR_HEADER__
    // do not edit these lines: end
  };

} // l22

#endif
