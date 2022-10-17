%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <algorithm>
#include <memory>
#include <cstring>
#include <cdk/compiler.h>
#include <cdk/types/types.h>
#include ".auto/all_nodes.h"
#define LINE                         compiler->scanner()->lineno()
#define yylex()                      compiler->scanner()->scan()
#define yyerror(compiler, s)         compiler->scanner()->error(s)
//-- don't change *any* of these --- END!

#define NIL (new cdk::nil_node(LINE))
%}

%parse-param {std::shared_ptr<cdk::compiler> compiler}

%union {
  //--- don't change *any* of these: if you do, you'll break the compiler.
  YYSTYPE() : type(cdk::primitive_type::create(0, cdk::TYPE_VOID)) {}
  ~YYSTYPE() {}
  YYSTYPE(const YYSTYPE &other) { *this = other; }
  YYSTYPE& operator=(const YYSTYPE &other) { type = other.type; return *this; }

  std::shared_ptr<cdk::basic_type> type;        /* expression type */
  //-- don't change *any* of these --- END!
  
  int                   i;	/* integer value */
  double                d;    /* real value */
  std::string          *s;	/* symbol name or string literal */

  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;

  l22::block_node      *block;     /* Block node */
  std::vector<std::shared_ptr<cdk::basic_type>>   *iotypes;  /* Input and Output types for functions */
};

%token <i> tINTEGER tFOREIGN tUSE tPUBLIC tPRIVATE
%token <d> tREAL
%token <s> tIDENTIFIER tSTRING
%token <s> tBEGIN tEND
%token <type> tINT_TYPE tREAL_TYPE tSTRING_TYPE tVOID_TYPE tVAR
%token tWHILE tDO
%token tIF tTHEN tELSE tELIF
%token tWRITE tWRITELN tINPUT
%token tSTOP tAGAIN tRETURN tRETURN_TYPE
%token tSIZEOF
%token tNULL
%token tNOT
%token tUNARY
%token tCHANGE tWITH tDOTS tSWEEP

%nonassoc tIF tWHILE
%nonassoc tTHEN tDO
%nonassoc tELIF tELSE

%right '='
%left '|'
%left '&'
%nonassoc tNOT
%left tEQ tNE
%left '<' '>' tGE tLE
%left '+' '-'
%left '*' '/' '%'
%nonassoc '(' '['
%right tUNARY

%type <node> instr program block_instr elif decl vardecl fundecl var
%type <expression> expr fun_def fun_call block_expr
%type <sequence> instrs exprs file decls vars
%type <type> type type_void type_func
%type <iotypes> args
%type <block> block
%type <lvalue> lval
%type <s> string

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}

%%

/* ====================================================================== */
/* ====[                          Ficheiro                          ]==== */
/* ====================================================================== */

/* Ficheiro: <declaracao>[programa-principal] */
file :       program  { compiler->ast($$ = new cdk::sequence_node(LINE, $1, nullptr)); }
     | decls program  { compiler->ast($$ = new cdk::sequence_node(LINE, $2, $1));      }
     ;

/* ====================================================================== */
/* ====[                    Programa Principal                      ]==== */
/* ====================================================================== */

/* Programa principal: begin bloco end */
program : tBEGIN block tEND  { $$ = new l22::program_node(LINE, $2); }
        ;

/* ====================================================================== */
/* ====[                         Declaracoes                        ]==== */
/* ====================================================================== */

decls :       decl  { $$ = new cdk::sequence_node(LINE, $1);     }
      | decls decl  { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;

/* ====================================================================== */
/* ====[                         Declaracao                         ]==== */
/* ====================================================================== */

/* Declaracao: [ qualificador ] tipo identificador [ = expressão ] 
               OU
               [ qualificador ] [ var ] identificador = expressão */
decl : vardecl ';' { $$ = $1; } /* declaracao de variavel "normal" */
     | fundecl     { $$ = $1; } /* declaracao de variavel do tipo funcao */
     ;

vardecl : tPUBLIC  type tIDENTIFIER             { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, $2, *$3, nullptr);     delete $3; }
        | tPUBLIC  type tIDENTIFIER '=' expr    { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, $2, *$3, $5);          delete $3; }
        | tPUBLIC  tVAR tIDENTIFIER '=' expr    { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, nullptr, *$3, $5);  delete $3; }
        | tPUBLIC       tIDENTIFIER '=' expr    { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, nullptr, *$2, $4);  delete $2; }
        /* USE: cannot be used with tVAR (no initial value) */
        | tUSE     type tIDENTIFIER             { $$ = new l22::variable_declaration_node(LINE, tUSE, $2, *$3, nullptr);        delete $3; }
        /* FOREIGN: for declaring function symbols - only verify that later */
        | tFOREIGN type tIDENTIFIER             { $$ = new l22::variable_declaration_node(LINE, tFOREIGN, $2, *$3, nullptr);    delete $3; }
        /* NO_QUALIFIER */
        | var                                   { $$ = $1; }
        |          type tIDENTIFIER '=' expr    { $$ = new l22::variable_declaration_node(LINE, tPRIVATE, $1, *$2, $4);         delete $2; } 
        |          tVAR tIDENTIFIER '=' expr    { $$ = new l22::variable_declaration_node(LINE, tPRIVATE, nullptr, *$2, $4); delete $2; } 
        ;

fundecl : tPUBLIC type  tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, $2, *$3, $5);          delete $3; }
        | tPUBLIC tVAR  tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, $5->type(), *$3, $5);  delete $3; }
        | tPUBLIC       tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tPUBLIC, $4->type(), *$2, $4);  delete $2; }
        /* FOREIGN: for declaring function symbols */
        | tFOREIGN type tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tFOREIGN, $2, *$3, $5);         delete $3; }
        | tFOREIGN tVAR tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tFOREIGN, $5->type(), *$3, $5); delete $3; }
        | tFOREIGN      tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tFOREIGN, $4->type(), *$2, $4); delete $2; }
        /* NO_QUALIFIER */
        |          type tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tPRIVATE, $1, *$2, $4);         delete $2; }
        |          tVAR tIDENTIFIER '=' block_expr { $$ = new l22::variable_declaration_node(LINE, tPRIVATE, $4->type(), *$2, $4); delete $2; }
        ;

/* ====================================================================== */
/* ====[                           Funcao                           ]==== */
/* ====================================================================== */

/* Funcao: ( ) -> tipo : bloco OU ( variaveis ) -> tipo : bloco */

fun_def : '(' vars ')' tRETURN_TYPE type      ':' block   { $$ = new l22::function_definition_node(LINE, $5, $2 ,$7);                           }
        | '('      ')' tRETURN_TYPE type      ':' block   { $$ = new l22::function_definition_node(LINE, $4, new cdk::sequence_node(LINE), $6); }
        | '(' vars ')' tRETURN_TYPE type_void ':' block   { $$ = new l22::function_definition_node(LINE, $5, $2 ,$7);                           }
        | '('      ')' tRETURN_TYPE type_void ':' block   { $$ = new l22::function_definition_node(LINE, $4, new cdk::sequence_node(LINE), $6); }
        ;

/* Invocacao de funcao: a partir de qualquer expressao que a refira 
   Usando '@', fazemos uma invocacao recursiva
   Se houver argumentos, ao ponteiro segue-se uma lista de expressoes delimitadas por () */
fun_call : expr            '(' exprs ')'   { $$ = new l22::function_call_node(LINE, $1, $3);      }
         | expr            '('       ')'   { $$ = new l22::function_call_node(LINE, $1);          }
         /* recursive call */
         | '@'             '(' exprs ')'   { $$ = new l22::function_call_node(LINE, nullptr ,$3); }
         | '@'             '('       ')'   { $$ = new l22::function_call_node(LINE, nullptr);     }
         /* "special": define + call */
         | '(' fun_def ')' '(' exprs ')'   { $$ = new l22::function_call_node(LINE, $2, $5);      }
         | '(' fun_def ')' '('       ')'   { $$ = new l22::function_call_node(LINE, $2);          }
         ;

/* ====================================================================== */
/* ====[                         Variaveis                          ]==== */
/* ====================================================================== */

/* Variaveis: variavel ⟨ , variavel ⟩ */
vars : var              { $$ = new cdk::sequence_node(LINE, $1);       }
     | var ',' vars     { 
                          std::reverse($3->nodes().begin(), $3->nodes().end()); 
                          $$ = new cdk::sequence_node(LINE, $1, $3); 
                          std::reverse($$->nodes().begin(), $$->nodes().end());
                        }
     ;

var : type tIDENTIFIER  { $$ = new l22::variable_declaration_node(LINE, tPRIVATE, $1, *$2, nullptr); delete $2; }
    ;

/* ====================================================================== */
/* ====[                            Tipo                            ]==== */
/* ====================================================================== */

/* Tipo: int | double | text | [ tipo ] | tipo-de-função */
type : tINT_TYPE                   { $$ = cdk::primitive_type::create(4, cdk::TYPE_INT);                                            }
     | tREAL_TYPE                  { $$ = cdk::primitive_type::create(8, cdk::TYPE_DOUBLE);                                         }
     | tSTRING_TYPE                { $$ = cdk::primitive_type::create(4, cdk::TYPE_STRING);                                         }
     | '[' type      ']'           { $$ = cdk::reference_type::create(4, $2);                                                       }
     /* TODO ponteiro para void: o aninhamento e indiferente */
     | '[' type_void   ']'         { $$ = cdk::reference_type::create(4, $2);                                                       }
     | type_func                   { $$ = $1; }
     ;

type_void : tVOID_TYPE             { $$ = cdk::primitive_type::create(4, cdk::TYPE_VOID);                                           }
          ;

/* Tipo de funcao: tipo < ⟨ tipo ⟩ > */
type_func : type      '<' args '>' { $$ = cdk::functional_type::create(*$3, $1);                                                    }
          | type      '<'      '>' { $$ = cdk::functional_type::create(*(new std::vector<std::shared_ptr<cdk::basic_type>>()), $1); }
          | type_void '<' args '>' { $$ = cdk::functional_type::create(*$3, $1);                                                    }
          | type_void '<'      '>' { $$ = cdk::functional_type::create(*(new std::vector<std::shared_ptr<cdk::basic_type>>()), $1); }
          ;

args : type                        { $$ = new std::vector<std::shared_ptr<cdk::basic_type>>(); $$->insert($$->begin(), $1);         } 
     | type ',' args               { $$ = $3; $$->insert($$->begin(), $1);                                                          }
     ;

/* ====================================================================== */
/* ====[                            Bloco                           ]==== */
/* ====================================================================== */

/* Bloco: <declaracao><instrucao> */
block : '{'           instrs '}'      { $$ = new l22::block_node(LINE, new cdk::sequence_node(LINE), $2); }
      | '{' decls            '}'      { $$ = new l22::block_node(LINE, $2, new cdk::sequence_node(LINE)); }
      | '{' decls     instrs '}'      { $$ = new l22::block_node(LINE, $2, $3);                           }
      ;

/* ====================================================================== */
/* ====[                          Instrucoes                        ]==== */
/* ====================================================================== */

instrs : instr              { $$ = new cdk::sequence_node(LINE, $1); }
       | block_instr        { $$ = new cdk::sequence_node(LINE, $1); }
       | instr ';' instrs   { 
                              std::reverse($3->nodes().begin(), $3->nodes().end()); 
                              $$ = new cdk::sequence_node(LINE, $1, $3); 
                              std::reverse($$->nodes().begin(), $$->nodes().end()); 
                            }
       | block_instr instrs { 
                              std::reverse($2->nodes().begin(), $2->nodes().end()); 
                              $$ = new cdk::sequence_node(LINE, $1, $2); 
                              std::reverse($$->nodes().begin(), $$->nodes().end()); 
                            }
       ;  

/* ====================================================================== */
/* ====[                          Instrucao                         ]==== */
/* ====================================================================== */

instr : tWRITE exprs        { $$ = new l22::write_node(LINE, $2, false); }
      | tWRITELN exprs      { $$ = new l22::write_node(LINE, $2, true);  }
      | tAGAIN              { $$ = new l22::again_node(LINE);            }
      | tSTOP               { $$ = new l22::stop_node(LINE);             }
      | tRETURN expr        { $$ = new l22::return_node(LINE, $2);       }
      | tRETURN             { $$ = new l22::return_node(LINE, nullptr);  }
      | expr                { $$ = new l22::evaluation_node(LINE, $1);   }
      /* TESTE PRATICO */
      | tWITH       expr tCHANGE expr tRETURN_TYPE expr tDOTS expr    { $$ = new l22::with_change_node(LINE, $2, $4, $6, $8); }
      | tWITH block_expr tCHANGE expr tRETURN_TYPE expr tDOTS expr    { $$ = new l22::with_change_node(LINE, $2, $4, $6, $8); }
      | tSWEEP expr tRETURN_TYPE expr tDOTS expr tWITH       expr tIF expr { $$ = new l22::sweep_node(LINE, $2, $4, $6, $8, $10); }
      | tSWEEP expr tRETURN_TYPE expr tDOTS expr tWITH block_expr tIF expr { $$ = new l22::sweep_node(LINE, $2, $4, $6, $8, $10); }
      ;

/* Instrucao condicional: if ( expressão ) then: bloco ⟨ elif ( expressão ) then: bloco ⟩ [ else: bloco ] */
/* Instrucao de iteracao: while ( expressão ) do: bloco */
block_instr : tIF    '(' expr ')' tTHEN block      { $$ = new l22::if_node(LINE, $3, $6);          }
            | tIF    '(' expr ')' tTHEN block elif { $$ = new l22::if_else_node(LINE, $3, $6, $7); }
            /* instrucao de iteracao */
            | tWHILE '(' expr ')' tDO   block      { $$ = new l22::while_node(LINE, $3, $6);       }
            /* expressao de inicializacao, em que a funcao foi pre-declarada */
            | lval   '=' block_expr                { $$ = new cdk::assignment_node(LINE, $1, $3);  }
            /* o valor de retorno pode ser uma expressao do tipo definicao de funcao */
            | tRETURN fun_def                      { $$ = new l22::return_node(LINE, $2);          }
            ;

elif : tELSE block                                 { $$ = $2;                                      }
     | tELIF  '(' expr ')' tTHEN block             { $$ = new l22::if_node(LINE, $3, $6);          }
     | tELIF  '(' expr ')' tTHEN block elif        { $$ = new l22::if_else_node(LINE, $3, $6, $7); }
     ;

/* ====================================================================== */
/* ====[                         Expressoes                         ]==== */
/* ====================================================================== */

/* Expressoes: expressão < , expressão > */
exprs : expr                 { $$ = new cdk::sequence_node(LINE, $1);     }
      | exprs ',' expr       { $$ = new cdk::sequence_node(LINE, $3, $1); }
      | block_expr           { $$ = new cdk::sequence_node(LINE, $1);     }
      | exprs ',' block_expr { $$ = new cdk::sequence_node(LINE, $3, $1); }
      ;

/* ====================================================================== */
/* ====[                          Expressao                         ]==== */
/* ====================================================================== */

// TODO MUDAR ISTO
expr : tINTEGER                        { $$ = new cdk::integer_node(LINE, $1);        }
     | tREAL                           { $$ = new cdk::double_node(LINE, $1);         }
     | string                          { $$ = new cdk::string_node(LINE, $1);         }
     | tNULL                           { $$ = new l22::nullptr_node(LINE);            }
     /* LEFT-VALUE */
     | lval                            { $$ = new cdk::rvalue_node(LINE, $1);         } 
     /* ASSIGNMENT */
     | lval '=' expr                   { $$ = new cdk::assignment_node(LINE, $1, $3); }
     /* ARITHMETIC EXPRESSIONS */
     | expr '+' expr	              { $$ = new cdk::add_node(LINE, $1, $3);        }
     | expr '-' expr	              { $$ = new cdk::sub_node(LINE, $1, $3);        }
     | expr '*' expr	              { $$ = new cdk::mul_node(LINE, $1, $3);        }
     | expr '/' expr	              { $$ = new cdk::div_node(LINE, $1, $3);        }
     | expr '%' expr	              { $$ = new cdk::mod_node(LINE, $1, $3);        }
     /* LOGICAL EXPRESSIONS */
     | expr '|' expr                   { $$ = new cdk::or_node(LINE, $1, $3);         }
     | expr '&' expr                   { $$ = new cdk::and_node(LINE, $1, $3);        }
     | expr '<' expr	              { $$ = new cdk::lt_node(LINE, $1, $3);         }
     | expr '>' expr	              { $$ = new cdk::gt_node(LINE, $1, $3);         }
     | expr tGE expr	              { $$ = new cdk::ge_node(LINE, $1, $3);         }
     | expr tLE expr                   { $$ = new cdk::le_node(LINE, $1, $3);         }
     | expr tNE expr	              { $$ = new cdk::ne_node(LINE, $1, $3);         }
     | expr tEQ expr	              { $$ = new cdk::eq_node(LINE, $1, $3);         }
     | tNOT expr                       { $$ = new cdk::not_node(LINE, $2);            }        
     /* UNARY EXPRESSIONS */
     | '+' expr %prec tUNARY           { $$ = new l22::identity_node(LINE, $2);       }
     | '-' expr %prec tUNARY           { $$ = new cdk::neg_node(LINE, $2);            }
     /* OTHER EXPRESSIONS */
     | '(' expr ')'                    { $$ = $2;                                     }
     | tSIZEOF '(' expr ')'            { $$ = new l22::sizeof_node(LINE, $3);         }
     | '[' expr ']'                    { $$ = new l22::stack_alloc_node(LINE, $2);    }
     | lval '?'                        { $$ = new l22::address_of_node(LINE, $1);     }
     | tINPUT                          { $$ = new l22::input_node(LINE);              }
     /* FUNCTION CALL */
     | fun_call                        { $$ = $1;                                     }
     ;

/* expressao, mas nao e uma unica linha, porque envolve definicao de funcoes */
block_expr : fun_def                               { $$ = $1;                                      }
           | lval '=' block_expr                   { $$ = new cdk::assignment_node(LINE, $1, $3);  }
           ;

lval : tIDENTIFIER                     { $$ = new cdk::variable_node(LINE, $1);       }
     | expr '[' expr ']'               { $$ = new l22::index_node(LINE, $1, $3);      }
     ;                        

string : tSTRING                       { $$ = $1; }
       | string tSTRING                { 
                                        $$ = new std::string(*$1 + *$2); 
                                        delete $1; 
                                        delete $2; 
                                       }
       ;

%%