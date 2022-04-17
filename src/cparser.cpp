#include <cparser.hpp>
#include <vector>
#include <stdlib.h>

using namespace std;
using namespace parser;

// CParser::CParser():Parser<Symbol>({
// {"c", { {{"primitive", "id", "c1", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
//               {Row row; 
//               row.type="primitive"; 
//               string k = siblingPointers[1]->lexval;
//               if (!symbolTable.declareVariable(k, row))
//               {
//                      cout<<k<<endl;
//                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
//                      cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
//                      exit(EXIT_FAILURE);
//               }
//               }}}},
//        {{"void", "id", "fn", "c" } , {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
//               {Row row; 
//               row.type="primitive"; 
//               string k = siblingPointers[1]->lexval;
//               if (!symbolTable.declareVariable(k, row))
//               {
//                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
//                      cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
//               }
//               }}}},
//        {{"struct_or_union" , "id" , "struct_def", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
//               {
//               Row row;
//               string k = siblingPointers[1]->lexval;
//               siblingPointers[2]->id = k;
//               row.type = "custom";
//               if (!symbolTable.declareVariable(k, row))
//               {
//                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
//                      cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
//                      exit(EXIT_FAILURE);
//               }
//               }}}},
//        {{"enum" , "id" ,"enum_def", "c"} , {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
//               {
//               Row row;
//               string k = siblingPointers[1]->lexval;
//               siblingPointers[2]->id = k;
//               row.type = "custom";
//               if (!symbolTable.declareVariable(k, row))
//               {
//                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
//                      cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
//                      exit(EXIT_FAILURE);
//               }
//               }}}},
//        {{"#"} , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}}

//        }},
 
//  {"fn", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
//          }},

//   {"c1", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
//             {{";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//             {{"W",";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//             {{",", "var_list" , ";" }, {{1, [](Symbol parent, vector<Symbol *> siblingPointers)
//               { 
//                      siblingPointers[1]->aspect = "declaration";
//                      siblingPointers[1]->type = "primitive";
//               }}}}
//           }},
 
//  {"c2", { {{ "block" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},
  
//   {"struct_def", { {{ "{", "SM", "}" , "D", ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

//   {"SM", { {{ "U" , "SM'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

//   {"SM'", { {{ "U","SM'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//             {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
  
//   {"U", { {{ "primitive","var_list", ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},
  
//   {"D", { {{ "var_list" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//             {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
//   {"enum_def", { {{ "{", "var_list" , "}" , "D" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

//   {"var_list", { {{ "id" , "var_list'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},
//   {"var_list'", { {{ ",", "id" , "var_list'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//                  {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
//   {"paramlist", { {{ "params" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//                  {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
  
//   {"params", { {{ "param" , "params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//               {{ ",", "param" , "params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//                  {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

//   {"params'", { {{ "," ,"param" ,"params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}},
//                  {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}}
//          }},

//   {"param", { {{ "primitive", "id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//               {{ "struct_or_union" , "id","id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//               {{ "enum" , "id","id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
  
//   {"block", { {{ "{", "stmtList" , "scope_end" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},
//   {"scope_end", { {{ "}" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

//   {"stmtList", { {{ "stmt", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//                {{ "loop", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//                {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
//          }},
  
//   {"stmt", { {{ "something" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
//          }},

// {"something", {{{"primitive", "id" , "Z"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"id" , "Y"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"ret"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"struct_or_union", "id" , "D"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"enum", "id" , "D"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"Z",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"," , "var_list"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"Y",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"(" , "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"." , "id", "WW"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"WW",         {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"W",         {{{"=", "V"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"V",          {{{"exprsn"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"arglist",     {{{"args"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"args",         {{{"arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"args'",     {{{",", "arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"arg",         {{{"id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                  {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"prefix_op",     {{{"++", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"--", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"prefix_op",     {{{"++", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"--", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"ret",         {{{"return", "ret_var"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"ret_var",          {{{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"id" , "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"exprsn",      {{{"T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"E'",          {{{"+", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"-", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"T",          {{{"(", "exprsn", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"id", "F"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"F",          {{{"(", "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"constant",    {{{"int_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"fp_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"loop",       {{{"for", "condn", "block"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"condn",       {{{"(", "stmt1", ";", "stmt2", ";", "stmt3", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"stmt1",    {{{"primitive", "id", "W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"id", "W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"stmt2",    {{{"id", "relop", "exprsn"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"stmt3",    {{{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},

// {"dot",    {{{".", "id"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
//                {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
// }},
//     }, "#"s, "c"s)
// {}

CParser::CParser():Parser<Symbol>({
{"c", { {{"primitive", "id", "c1", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {Row row; 
              row.type="primitive"; 
              string k = siblingPointers[1]->lexval;
              if (!symbolTable.declareVariable(k, row))
              {
                     cout<<k<<endl;
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
              }}}},
       {{"void", "id", "fn", "c" } , {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {Row row; 
              row.type="primitive"; 
              string k = siblingPointers[1]->lexval;
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
              }
              }}}},
       {{"struct_or_union" , "id" , "struct_def", "c"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {
              Row row;
              string k = siblingPointers[1]->lexval;
              siblingPointers[2]->id = k;
              row.type = "custom";
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
              }}}},
       {{"enum" , "id" ,"enum_def", "c"} , {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {
              Row row;
              string k = siblingPointers[1]->lexval;
              siblingPointers[2]->id = k;
              row.type = "custom";
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
              }}}},
       {{"#"} , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}}

       }},
 
 {"fn", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
         }},

  {"c1", { {{"(", "paramlist" , ")", "c2" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers){ symbolTable.openScope(); }}}},
            {{";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{"W",";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{",", "var_list" , ";" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
              { 
                     siblingPointers[1]->aspect = "declaration";
                     siblingPointers[1]->type = "primitive";
              }}}}
          }},
 
 {"c2", { {{ "block" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  
  {"struct_def", { {{ "{", "SM", "}" , "D", ";" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { siblingPointers[1]->id = parent.id; }},
            {3, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { siblingPointers[3]->type = parent.id; }}
            }},
         }},

  {"SM", { {{ "U" , "SM'" }, {{0, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { siblingPointers[0]->id = parent.id; }},

            {1, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { siblingPointers[1]->id = parent.id; }}

            }},
         }},

  {"SM'", { {{ "U","SM'" }, {{0, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { siblingPointers[0]->id = parent.id; }}
            }},
            {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"U", { {{ "primitive","var_list", ";" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { 
                siblingPointers[1]->aspect = "body";
                siblingPointers[1]->id = parent.id;
                siblingPointers[1]->type = "primitive";
             }}
            
            }},
         }},
  
  {"D", { {{ "var_list" }, {{0, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { 
                siblingPointers[0]->aspect = "declaration";
                siblingPointers[0]->type = parent.type;
            }}
            }},
            {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  {"enum_def", { {{ "{", "var_list" , "}" , "D" , ";" }, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
  
            { 
               siblingPointers[1]->type = "primitive";
               siblingPointers[1]->aspect = "body";
               siblingPointers[1]->id = parent.id;
            }},
            {3, [&](Symbol parent, vector<Symbol *> siblingPointers)
  
            { 
               siblingPointers[3]->type = parent.id ;
               
            }}
            
            }},
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
                 {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  {"paramlist", { {{ "params" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
                 {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"params", { {{ "param" , "params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
              {{ ",", "param" , "params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
                 {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"params'", { {{ "," ,"param" ,"params'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}},
                 {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action*/ }}}}
         }},

  {"param", { {{ "primitive", "id" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            {  //Check this.
              Row row;
              string k = siblingPointers[1]->lexval;
              row.type = "primitive";
              if (!symbolTable.declareVariable(k, row))
              {
                     cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                     cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                     exit(EXIT_FAILURE);
              }
                
            }}
            
            }},
              {{ "struct_or_union" , "id","id" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              {  //Methods need to be corrected.
                 string lval = siblingPointers[1]->lexval;
                 Row* res = symbolTable.resolveVariable(lval);
                  if(res != nullptr)
                  {
                    Row row;
                    string k = siblingPointers[2]->lexval;
                    row.type = siblingPointers[1]->lexval;
                    if (!symbolTable.declareVariable(k, row))
                    {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                  }
                  else{
                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: "<<siblingPointers[1]->colNum<<endl;
                      cerr<<"Type : "<<siblingPointers[1]->lexval <<"does not exist";
                      exit(EXIT_FAILURE);
                  }
               }}
              }},
              {{ "enum" , "id","id" }, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
              { 
                  string lval = siblingPointers[1]->lexval;
                  Row* res = symbolTable.resolveVariable(lval);
                  if(res != nullptr)
                  {
                    Row row;
                    string k = siblingPointers[2]->lexval;
                    row.type = siblingPointers[1]->lexval;
                    if (!symbolTable.declareVariable(k, row))
                    {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                  }
                  else{
                      cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: "<<siblingPointers[1]->colNum<<endl;
                      cerr<<"Type : "<<siblingPointers[1]->lexval <<"does not exist";
                      exit(EXIT_FAILURE);
                  }
                  
              }}
              
              }}
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
               {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"stmt", { {{ "something" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

{"something", {{{"primitive", "id" , "Z"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            { //add id to symbol table.
                Row row;
                string k = siblingPointers[1]->lexval;
                row.type = "primitive";
                if (!symbolTable.declareVariable(k, row))
                {
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                        exit(EXIT_FAILURE);
                }
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
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
   
                }}

                }},
            {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{"ret"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
            {{"struct_or_union", "id" , "D"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                { //D.type = id.lex_val
                     Row * row = symbolTable.resolveVariable(siblingPointers[1]->lexval);
                     if(row != nullptr && (row->type=="custom"))
                            siblingPointers[2]->type = siblingPointers[1]->lexval;
                     else{
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " custom type does not exist ! "<<endl;
                        exit(EXIT_FAILURE);
                     }
                }}
                }},
            {{"enum", "id" , "D"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {   //D.type = id.lex_val
                    Row * row = symbolTable.resolveVariable(siblingPointers[1]->lexval);
                     if(row != nullptr && (row->type=="custom"))
                            siblingPointers[2]->type = siblingPointers[1]->lexval;
                     else{
                        cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                        cerr<<siblingPointers[1]->colNum<<endl<< " custom type does not exist ! "<<endl;
                        exit(EXIT_FAILURE);
                     }
                }}
                }},
            {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Z",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"," , "var_list"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                 {/*var_list.aspect = "declaration"; var_list.type = primitive*/
                    siblingPointers[1]->aspect = "declaration";
                    siblingPointers[1]->type = "primitve";
                 }}
                 }},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Y",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"(" , "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"." , "id","WW"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                { // check if id.lexval present in details list of Y.type in symbol table
                    //To be done
                    Row* row = symbolTable.resolveVariable(parent.type);
                    if(row != nullptr )
                    {
                        if(row->details.find(siblingPointers[1]->lexval) == row->details.end())
                        {
                            cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                            cerr<<siblingPointers[1]->colNum<<endl<< " invalid attribute ! "<<endl;
                            exit(EXIT_FAILURE);
                        }
                    }
                }}
                
                }},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"WW",         {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"W",         {{{"=", "V"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"V",          {{{"exprsn"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"arglist",     {{{"args"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"args",         {{{"arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"args'",     {{{",", "arg", "args'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"arg",         {{{"id", "dot"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
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
                 {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"prefix_op",     {{{"++", "id", "dot"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[1]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[2]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[2]->lineNum<<" and column: ";
                        cerr<<siblingPointers[2]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                
                }},
               {{"--", "id", "dot"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    // look up for id.lexval in sym table ; if yes -> dot.type = type of id from symbol table
                    Row* row= symbolTable.resolveVariable(siblingPointers[1]->lexval);
                    if(row != nullptr)
                    {
                        siblingPointers[2]->type = row->type;
                    }
                    else
                    {
                        cerr<<"Error at line: "<<siblingPointers[2]->lineNum<<" and column: ";
                        cerr<<siblingPointers[2]->colNum<<endl<< " identifier not declared ! "<<endl;
                        exit(EXIT_FAILURE);
                    }
                }}
                }},
}},

{"prefix_op",     {{{"++", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"--", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"ret",         {{{"return", "ret_var"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"ret_var",      {{{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id" , "dot"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
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
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"exprsn",      {{{"T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"E'",          {{{"+", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"-", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
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
               {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"F",          {{{"(", "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers)
               {
                   //dot.type = F.type
                   siblingPointers[0]->type = parent.type;
               }}
               }},
}},

{"constant",    {{{"int_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"fp_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"loop",       {{{"for", "condn", "block"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    //move to new scope
                    symbolTable.openScope();
                }}
                }},
}},

{"condn",       {{{"(", "stmt1", ";", "stmt2", ";", "stmt3", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"stmt1",    {{{"primitive", "id", "W"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
                {
                    //add id to sym table
                    Row row;
                    string k = siblingPointers[1]->lexval;
                    row.type = "primitive";
                    if (!symbolTable.declareVariable(k, row))
                    {
                            cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                            cerr<<siblingPointers[1]->colNum<<endl<< " variable already declared ! "<<endl;
                            exit(EXIT_FAILURE);
                    }
                }}
                }},

               {{"id", "W"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
               {
                   //lookup for id.lexval
                   if(!symbolTable.canBeResolvedVariable(siblingPointers[0]->lexval))
                   {
                       cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                       cerr<<siblingPointers[0]->colNum<<endl<< " variable never declared ! "<<endl;
                       exit(EXIT_FAILURE);
                   }

               }}
               }},
}},

{"stmt2",    {{{"id", "relop", "exprsn"}, {{1, [&](Symbol parent, vector<Symbol *> siblingPointers)
               {
                   //lookup for id.lexval
                   if(!symbolTable.canBeResolvedVariable(siblingPointers[0]->lexval))
                   {
                       cerr<<"Error at line: "<<siblingPointers[0]->lineNum<<" and column: ";
                       cerr<<siblingPointers[0]->colNum<<endl<< " variable never declared ! "<<endl;
                       exit(EXIT_FAILURE);
                   }
               }}
               }},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"stmt3",    {{{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"dot",    {{{".", "id"}, {{2, [&](Symbol parent, vector<Symbol *> siblingPointers)
            {
                //check if id.lexval present in details list of dot.type in symbol table
               
                Row* row = symbolTable.resolveVariable(parent.type);
                if(row != nullptr)
                {
                    if(row->details.find(siblingPointers[1]->lexval) == row->details.end())
                        {
                            cerr<<"Error at line: "<<siblingPointers[1]->lineNum<<" and column: ";
                            cerr<<siblingPointers[1]->colNum<<endl<< " invalid attribute ! "<<endl;
                            exit(EXIT_FAILURE);
                        }
                }

            }}
            }},
            {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},
    }, "#"s, "c"s)
{}