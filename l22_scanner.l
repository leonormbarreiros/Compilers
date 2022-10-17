%option c++ prefix="l22_scanner_" outfile="l22_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <sstream>
#include <iostream>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "l22_parser.tab.h"

// output stream for building string literals
static std::ostringstream strlit;

static std::ostringstream prev;

static bool restart_functions = false;
static int lLevelsToPop = 0, lIndex = 0;
static std::vector<int> indents; 

inline bool valid(int indent) {
    lLevelsToPop = lIndex = -1;
    bool indentOk = false;
    for (size_t ix = 0; ix < indents.size(); ix++) {
        if (indent == indents[ix]) {
            lLevelsToPop = indents.size() - ix - 1;
            lIndex = ix;
            indentOk = true;
        }
    }
    return indentOk;
}

// don't change this
#define yyerror LexerError
%}

SPACE     [ ]

%x X_STRING X_COMMENT X_SLASH X_END_STRING X_CONCAT
%x X_NEWLINE

%%

  /*yydebug=1; set_debug(1);*/

  {
    /*set_debug(true);*/
    if (restart_functions) {
      indents.pop_back();
      if (indents.size() == 0) {
        restart_functions = false;
      } 
      return '}';
    }
    else {
      if (lLevelsToPop > 0) {
        lLevelsToPop--;
        indents.pop_back();
        return '}';
      }
    }    
  }
  
  /* ====================================================================== */
  /* ====[                 3 - Convencoes lexicais                    ]==== */
  /* ====[              3.1.2 - Marcador de continuacao               ]==== */
  /* ====================================================================== */

{SPACE}*"..."\n                   ; /* ignore continuation marks */

  /* ====================================================================== */
  /* ====[                      3.2.2 - Identacao                     ]==== */
  /* ====================================================================== */

\n                                yy_push_state(X_NEWLINE); /* delay decision */

<X_NEWLINE>^{SPACE}+  { 
    yy_pop_state();
    if (valid(yyleng)) {
      /* case 1: same level - just send ';' */
      if (lLevelsToPop == 0) {
        return ';';
      }
      /* case 2: ignore, unless we've reached the end - send block-end token */
      else {
        if (lLevelsToPop > 0) {
          lLevelsToPop--;
          indents.pop_back();
          return '}';
        }
      }
    }
    /* first block */
    else if (indents.size() == 0) {
      indents.push_back(yyleng);
      return '{';
    }
    /* new block opening */
    else if (yyleng > indents.back()) {
      indents.push_back(yyleng);
      return '{';
    }
    else {
      std::cerr << "bad indent at line " << yylineno;
    }
}
<X_NEWLINE>\n                     ;
<X_NEWLINE>.                      {
  yyless(0);
  yy_pop_state();
  if (indents.size() > 0) {
    indents.pop_back();
    if (indents.size() > 0) { 
      restart_functions = true; 
    }
    return '}';
  }
  else return ';';
}

  /* ====================================================================== */
  /* ====[                    3.3 - Comentarios                       ]==== */
  /* ====================================================================== */

";".*$                            ; /* ignore comments */

"(*"                              yy_push_state(X_COMMENT);
<X_COMMENT>"(*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"*)"                   yy_pop_state();
<X_COMMENT>.|\n                   ; /* ignore content */

  /* ====================================================================== */
  /* ====[                        TESTE PRATICO                       ]==== */
  /* ====================================================================== */

"with"                            return tWITH;
"change"                          return tCHANGE;
".."                              return tDOTS;
"sweep"                           return tSWEEP;

  /* ====================================================================== */
  /* ====[                   3.4 - Palavras-chave                     ]==== */
  /* ====================================================================== */

"null"                            return tNULL;

"foreign"                         return tFOREIGN;
"use"                             return tUSE;
"public"                          return tPUBLIC;
"var"                             return tVAR;

"if"                              return tIF; 
"then:"                           return tTHEN;
"elif"                            return tELIF;
"else:"                           return tELSE;

"while"                           return tWHILE; 
"do:"                             return tDO;

"stop"                            return tSTOP;
"again"                           return tAGAIN;
"write"                           return tWRITE; 
"writeln"                         return tWRITELN;
"return"                          return tRETURN;

"input"                           return tINPUT;

"begin"                           return tBEGIN; 
"end"                             return tEND; 

"sizeof"                          return tSIZEOF;

  /* ====================================================================== */
  /* ====[                        3.5 - Tipos                         ]==== */
  /* ====================================================================== */

"int"                             return tINT_TYPE;
"double"                          return tREAL_TYPE;
"text"                            return tSTRING_TYPE;
"void"                            return tVOID_TYPE;

  /* ====================================================================== */
  /* ====[               3.6 - Operadores de expressoes               ]==== */
  /* ====[             3.7 - Delimitadores e terminadores             ]==== */
  /* ====================================================================== */

"->"                              return tRETURN_TYPE;

[-()<>=+*/%?@,\[\]:]              return *yytext;

"and"                             return '&';
"or"                              return '|';
"not"                             return tNOT;

">="                              return tGE; 
"<="                              return tLE; 
"=="                              return tEQ; 
"!="                              return tNE; 

  /* ====================================================================== */
  /* ====[                3.8 - Identificadores (nomes)               ]==== */
  /* ====================================================================== */

[A-Za-z][A-Za-z0-9_]*             { 
                                    yylval.s = new std::string(yytext); 
                                    return tIDENTIFIER; 
                                  }
  
  /* ====================================================================== */
  /* ====[                       3.9 - Literais                       ]==== */
  /* ====[                      3.9.1 - inteiros                      ]==== */
  /* ====================================================================== */

[0][0-6]+                         { 
                                    try{
                                    yylval.i = std::stoul(yytext, NULL, 7); 
                                    return tINTEGER; 
                                    } catch (std::out_of_range &e) { yyerror("Overflow in integer."); }
                                  }
[0][0-9]+                         yyerror("Invalid base 7 number.");

[0]|[1-9][0-9]*                   { 
                                    try{
                                    yylval.i = std::stoul(yytext, NULL, 10); 
                                    return tINTEGER; 
                                    } catch (std::out_of_range &e) { yyerror("Overflow in integer."); }
                                  }

  /* ====================================================================== */
  /* ====[                   3.9.2 - reais                            ]==== */
  /* ====================================================================== */

[0-9]+\.[0-9]*([Ee][-+]?[0-9]+)?  { 
                                    try{
                                    yylval.d = std::stod(yytext, NULL);
                                    return tREAL; 
                                    } catch (std::out_of_range &e) { yyerror("Overflow in double."); }
                                  }
[0-9]*\.[0-9]+([Ee][-+]?[0-9]+)?  { 
                                    try{
                                    yylval.d = std::stod(yytext, NULL);
                                    return tREAL; 
                                    } catch (std::out_of_range &e) { yyerror("Overflow in double."); }
                                  }
[0-9]+([Ee][-+]?[0-9]+)           { 
                                    try{
                                    yylval.d = std::stod(yytext, NULL);
                                    return tREAL; 
                                    } catch (std::out_of_range &e) { yyerror("Overflow in double."); } 
                                  }

  /* ====================================================================== */
  /* ====[              3.9.3 - Cadeias de caracteres                 ]==== */
  /* ====================================================================== */

"\""                              yy_push_state(X_STRING);
<X_STRING>\\                      yy_push_state(X_SLASH);
<X_STRING>"\""                    {
                                    yylval.s = new std::string(strlit.str());
                                    strlit.str("");
                                    yy_pop_state();
                                    return tSTRING;
                                  }
<X_STRING>{SPACE}*"..."\n         ;
<X_STRING>.                       strlit << *yytext;

<X_SLASH>[0-6]{1,3}               {
                                    long aux = (long)strtoul(yytext, NULL, 7);
                                    if (aux >= 256) {
                                      yyerror("overflow!");
                                    }
                                    strlit << (char)(unsigned char)strtoul(yytext, NULL, 7);
                                    yy_pop_state();
                                  }

<X_SLASH>n                        { strlit << '\n'; yy_pop_state(); }
<X_SLASH>r                        { strlit << '\r'; yy_pop_state(); }
<X_SLASH>t                        { strlit << '\t'; yy_pop_state(); }
<X_SLASH>"\""                     { strlit << '"' ; yy_pop_state(); }
<X_SLASH>\\                       { strlit << '\\'; yy_pop_state(); }

<X_SLASH>.                        { strlit << *yytext; yy_pop_state(); }

<<EOF>>                           {
  if (indents.size() > 0) {
    indents.pop_back();
    return '}';
  }
  return 0;
}

[ ]+                              ; /* ignore whitespace */

.                                 yyerror("Unknown character");

%%
