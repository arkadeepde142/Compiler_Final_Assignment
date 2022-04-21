#include <cparser.hpp>
#include <vector>
#include <stdlib.h>
#define EPSILON "\u03F5"s
using namespace std;
using namespace parser;

void CParser::printSymbolTable(){
    symbolTable.printSymbolTable();
}

CParser::CParser():Parser<Symbol>({
{"c", { {{"char", "id", "c1", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {Row row; 
              row.type="char"; 
              string k = siblingPointers[1]->lexval;
              if (!symbolTable.declareVariable(k, row))
              {
                     cout<<k<<endl;
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
              siblingPointers[2]->type = "char";
              }}}},
              {{"string", "id", "c1", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {Row row; 
              row.type="string"; 
              string k = siblingPointers[1]->lexval;
              if (!symbolTable.declareVariable(k, row))
              {
                     cout<<k<<endl;
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
              siblingPointers[2]->type = "string";
              }}}},
       {{"void", "id", "fn", "c" } , {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {Row row; 
              row.type="void"; 
              string k = siblingPointers[1]->lexval;
              if (!symbolTable.declareVariable(k, row))
              {
                    cout << k << endl;
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " function already declared ! "<<endl;
              }
              }}}},
       {{EPSILON} , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}}

       }},
 
 {"fn", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
         }},

  {"c1", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
            {{";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{"W",";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ siblingPointers[0]->type = parent.type; }}}},
            {{",", "var_list" , ";" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
              { 
                     siblingPointers[1]->aspect = "declaration";
                     siblingPointers[1]->type = "primitive";
              }}}}
          }},
 
 {"c2", { {{ "block" }, {}},
            {{ ";" }, {}},
         }},

  {"var_list", { {{ "id" , "var_list'" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { 
               if(parent.aspect == "body")
                    {
                        //add id to details of var_list.id
                        Row* row = symbolTable.resolveVariable(parent.id);
                        row->details.insert(siblingPointers[0]->lexval);                    
                    }
               else if(parent.aspect == "declaration") 
                    {
                        // add id to sym table
                        Row row;
                        string k = siblingPointers[0]->lexval;
                        row.type = parent.type ;
                        if (!symbolTable.declareVariable(k, row))
                        {
                                cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                                cerr<<siblingPointers[0]->colNum<<endl<< " variable already declared ! "<<endl;
                                exit(EXIT_FAILURE);
                        }
                    }
                
                siblingPointers[1]->id = parent.id;
                siblingPointers[1]->aspect = parent.aspect;
                siblingPointers[1]->type = parent.type;
            }}
            
            }},
         }},
  {"var_list'", { {{ ",", "id" , "var_list'" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { 
                if(parent.aspect == "body")
                    {
                        //add id to details of var_list.id
                        Row* row = symbolTable.resolveVariable(parent.id);
                        row->details.insert(siblingPointers[1]->lexval);
                    }
               else if(parent.aspect == "declaration") 
                    {
                        // add id to sym table
                        Row row;
                        string k = siblingPointers[1]->lexval;
                        row.type = parent.type ;
                        if (!symbolTable.declareVariable(k, row))
                        {
                                cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                                cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                                exit(EXIT_FAILURE);
                        }
                    }
            }}
            }},
                 {{ EPSILON }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  {"paramlist", { {{ "params" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
                 {{ EPSILON }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"params", { {{ "param" , "params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
                 {{ EPSILON }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"params'", { {{ "," ,"param" ,"params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}},
                 {{ EPSILON }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}}
         }},

  {"param", { {{ "string", "id" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            {  //Check this.
              Row row;
              string k = siblingPointers[1]->lexval;
              row.type = "string";
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
                
            }}
            
            }},
            {{ "char", "id" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            {  //Check this.
              Row row;
              string k = siblingPointers[1]->lexval;
              row.type = "char";
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
                
            }}
            
            }},
         }},
  
  {"block", { {{ "{", "stmtList" , "scope_end" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  {"scope_end", { {{ "}" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { 
               //return to parent scope.
               symbolTable.endScope(); 
            }}
            }},
         }},

  {"stmtList", { {{ "stmt", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
               {{ "loop", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
               {{ EPSILON }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"stmt", { {{ "something" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

{"something", {{{"string", "id" , "Z"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { //add id to symbol table.
                Row row;
                string k = siblingPointers[1]->lexval;
                row.type = "string";
                if (!symbolTable.declareVariable(k, row))
                {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                        exit(EXIT_FAILURE);
                }
                siblingPointers[2]->type = "string";
                siblingPointers[2]->lineNum = siblingPointers[1]->lineNum;
                siblingPointers[2]->colNum = siblingPointers[1]->colNum;
            }}
            }},
            {{"char", "id" , "Z"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { //add id to symbol table.
                Row row;
                string k = siblingPointers[1]->lexval;
                row.type = "char";
                if (!symbolTable.declareVariable(k, row))
                {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                        exit(EXIT_FAILURE);
                }
                siblingPointers[2]->type = "char";
                siblingPointers[2]->lineNum = siblingPointers[1]->lineNum;
                siblingPointers[2]->colNum = siblingPointers[1]->colNum;
            }}
            }},
            {{"id" , "Y"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                { //id lookup
                    Row* row = symbolTable.resolveVariable(siblingPointers[0]->lexval);
                    if(row!= nullptr)
                    {
                        
                        //Y.type = type of id from sym table
                        siblingPointers[1]->type = row->type;
                    }
                    else{
                        cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                        cerr<<siblingPointers[0]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
   
                }}

                }},
            {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{"ret"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Z",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){
                    siblingPointers[0]->type = parent.type;
                    siblingPointers[0]->lineNum = parent.lineNum;
                    siblingPointers[0]->colNum = parent.colNum;
                }}}},
               {{"," , "var_list"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                 {/*var_list.aspect = "declaration"; var_list.type = primitive*/
                    siblingPointers[1]->aspect = "declaration";
                    siblingPointers[1]->type = parent.type;
                 }}
                 }},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Y",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"(" , "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"W",         {{{"=", "V"}, {{1, [](Symbol parent, vector<Symbol *> siblingPointers){
    siblingPointers[1]->type = parent.type;
    siblingPointers[1]->lineNum = parent.lineNum;
    siblingPointers[1]->colNum = parent.colNum;
}}}},
}},

{"V",          {{{"exprsn"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){
                    if(parent.type == "string")
                   {
                       cerr << parent.lineNum << endl;
                       cerr<<"Error at line: "<<parent.lineNum<<" and column: ";
                        cerr<<parent.colNum<<endl << " Cannot assign char to string ! "<<endl;
                        exit(EXIT_FAILURE);
                   }
                }}}},
               {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){
                   if(parent.type == "string")
                   {
                       cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                        cerr<<siblingPointers[0]->colNum<<endl << " Cannot assign string literal to char ! "<<endl;
                        exit(EXIT_FAILURE);
                   }
               }}}},
               {{"string_literal"}, {{1, [](Symbol parent, vector<Symbol *> siblingPointers){
                   if(parent.type == "char")
                   {
                       cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                        cerr<<siblingPointers[0]->colNum<<endl << " Cannot assign string literal to char ! "<<endl;
                        exit(EXIT_FAILURE);
                   }
               }}}},
}},

{"arglist",     {{{"args"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"args",         {{{"arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"args'",     {{{",", "arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"arg",         {{{"id"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[0]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[1]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                        cerr<<siblingPointers[0]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                }},
                 {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"prefix_op",     {{{"++", "id"}, {{0, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[1]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[2]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                
                }},
               {{"--", "id"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[1]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[2]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                }},
}},

{"ret",         {{{"return", "ret_var"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"ret_var",      {{{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[0]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[1]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                }},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"exprsn",      {{{"T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"E'",          {{{"+", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"-", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{EPSILON}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"T",          {{{"(", "exprsn", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id", "F"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
               {
                   // look up for id.lexval in sym table ; if yes -> F.type = type of id from symbol table
                   Row* row= symbolTable.resolveVariable(siblingPointers[0]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[1]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                        cerr<<siblingPointers[0]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
               }}
               }},
               {{"char_literal"}, {}},
               {{"int_num"}, {}}
}},

{"F",          {{{"(", "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{EPSILON}, {}},
}},

{"constant",    {{{"int_num"}, {}},
               {{"char_literal"}, {}},
               {{"string_literal"}, {}},
}},

{"loop",       {{{"while", "condn", "block"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    //move to new scope
                    symbolTable.openScope();
                }}
                }},
}},

{"condn",       {{{"(", "stmt1", ")"}, {}},
}},

{"stmt1",    {{{"id", "relop", "exprsn"}, {}},
}},
    }, EPSILON, "c"s)
{}