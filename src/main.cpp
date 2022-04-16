#include <iostream>
#include <clexer.hpp>
#include <iomanip>
#include <parser/parser.hpp>
#include <symbol.hpp>
using namespace std;

int main()
{
    // CLexer lex;

    string s = " int func(int x1, int x2){return 2;} \n void main(){ int z = func(2, 3);}";

    // unsigned long start = 0;
    // while (start < s.size())
    // {
    //     start = lex.lex(s, start);
    //     if (start > s.size())
    //     {
    //         cout << "Error at line " << lex.getLine() << endl;
    //     }
    // }
    // Symbol a("a");
    // Symbol b("b");
    // cout << (a != b);
    CLexer lexer;
    lexer.generateLexemes(s);
    for (auto lexeme : lexer.getLexemes())
    {
        cout << lexeme << endl;
    }

    parser::Grammar<Symbol> grammar{
    {"c", { {{"primitive", "id", "c1", "c"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
       {{"void", "id", "fn", "c" } , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
       {{"struct_or_union" , "id" , "struct_def", "c"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
       {{"enum" , "id" ,"enum_def", "c"} , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
       {{"#"} , {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}}

       }},
 
 {"fn", { {{"(", "paramlist" , ")", "c2" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"c1", { {{"(", "paramlist" , ")", "c2" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{"W",";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{",", "var_list" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
          }},
 
 {"c2", { {{ "block" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  
  {"struct_def", { {{ "{",  "}" , "D", ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"SM", { {{ "U" , "SM'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"SM'", { {{ "U","SM'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"U", { {{ "primitive" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  
  {"D", { {{ "var_list" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
            {{"#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  {"enum_def", { {{ "{", "var_list" , "}" , "D" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"var_list", { {{ "id" , "var_list'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  {"var_list'", { {{ ",", "id" , "var_list'" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
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

  {"param", { {{ "primitive", "id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
              {{ "struct_or_union" , "id","id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
              {{ "enum" , "id","id" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"block", { {{ "{", "stmtList" , "scope_end" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},
  {"scope_end", { {{ "}" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

  {"stmtList", { {{ "stmt", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
               {{ "loop", "stmtList" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
               {{ "#" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}}
         }},
  
  {"stmt", { {{ "something" , ";" }, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){ /*semantic action */ }}}},
         }},

{"something", {{{"primitive", "id" , "Z"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id" , "Y"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"ret"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"struct_or_union", "id" , "D"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"enum", "id" , "D"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Z",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"," , "var_list"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"Y",          {{{"W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"(" , "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"." , "id", "WW"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
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

{"arg",         {{{"id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
                 {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"prefix_op",     {{{"++", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"--", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"prefix_op",     {{{"++", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"--", "id", "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"ret",         {{{"return", "ret_var"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"ret_var",          {{{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id" , "dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"exprsn",      {{{"T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"E'",          {{{"+", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"-", "T", "E'"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"T",          {{{"(", "exprsn", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id", "F"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"constant"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"F",          {{{"(", "arglist", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"dot"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"constant",    {{{"int_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"fp_num"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"loop",       {{{"for", "condn", "block"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"condn",       {{{"(", "stmt1", ";", "stmt2", ";", "stmt3", ")"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"stmt1",    {{{"primitive", "id", "W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"id", "W"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"stmt2",    {{{"id", "relop", "exprsn"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"stmt3",    {{{"prefix_op"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},

{"dot",    {{{".", "id"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
               {{"#"}, {{0, [](Symbol parent, vector<Symbol *> siblingPointers){/*semantic action */}}}},
}},
    };

    parser::Parser<Symbol> parser(grammar, "#"s, "c"s);

    parser.parse(lexer.getLexemes());
}