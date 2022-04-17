#include <iostream>
#include <clexer.hpp>
#include <iomanip>
#include <cparser.hpp>
#include <symbol.hpp>
#include <fstream>
#include <string>
#include <cerrno>
using namespace std;

std::string get_file_contents(const char *filename)
{
       std::ifstream in(filename, std::ios::in | std::ios::binary);
       if (in)
       {
              std::string contents;
              in.seekg(0, std::ios::end);
              contents.resize(in.tellg());
              in.seekg(0, std::ios::beg);
              in.read(&contents[0], contents.size());
              in.close();
              return (contents);
       }
       throw(errno);
}

int main(int argc, char const **argv)
{
       if (argc > 1)
       {
              string s = get_file_contents(argv[1]);
              CLexer lexer;
              lexer.generateLexemes(s);
              // for(auto lexeme : lexer.getLexemes()){
              //        cout<<lexeme.lexval<<" "<<lexeme.lineNum<<" "<<lexeme.colNum<<endl;
              // }
              if (lexer.isError())
              {
                     cerr << "Error at ";
                     cerr << "line " << lexer.getLine() << " ";
                     cerr << "col " << lexer.getColNum() << endl;
                     exit(EXIT_FAILURE);
              }
              else
              {
                     CParser parser;
                     bool isParsed = parser.parse(lexer.getLexemes());
                     if(isParsed)
                     {
                            cout << "Successfully Parsed" << endl;
                            parser.printSymbolTable();
                            parser.printParseTable();
                     }
              }
       }
       else
       {
              cerr << "Filepath not given" << endl;
       }
}