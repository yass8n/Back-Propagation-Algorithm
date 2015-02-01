//main.cpp
//aniss, yaseen
# include "Ann.h"
# include "Parser.h"

int main(int argc, char *argv[]){
  cout << setprecision(16) << fixed;
  Parser parser;
  parser.parse_all(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], atoi(argv[7]));
  Ann *ann = Ann::instance();
  ann->run_back_propogation();
  ann->print_values();
  delete ann; 
  return 0;
}
