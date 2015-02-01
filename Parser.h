// ann.h
// aniss, yaseen
# ifndef _PARSER_H
# define _PARSER_H
# include <iostream>
# include <fstream>
# include "Ann.h"
#include <iomanip> //for set precision
using namespace std;

class Parser{
  public:
  	Parser();
  	~Parser(){};
  	void parse_all(char *, char *, char *, char *, char *, char *, int);
  private:
  	ifstream m_test_input_file;
  	ifstream m_test_output_file;
  	ifstream m_train_input_file;
  	ifstream m_train_output_file;
  	ifstream m_weights_file;
  	ifstream m_structure_file;
  	void parse_test_input(char *);
  	void parse_test_output(char *);
  	void parse_train_input(char *);
  	void parse_train_output(char *);
  	void parse_weights(char *);
  	void parse_structure(char *);
  	void convert(vector <double> &, int, int);
  };

#endif
