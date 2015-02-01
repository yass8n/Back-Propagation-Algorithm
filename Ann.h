// ann.h
// aniss, yaseen
# ifndef _ANN_H
# define _ANN_H
# include <iostream>
using namespace std;
# include "Node.h"
# include "Parser.h"
# include <stdlib.h>

class Ann{
  public:
  	friend class Parser;
  	static Ann *instance();
  	void run_back_propogation();
  	void print_values();
    ~Ann(){exit(0);}
    Ann(){};
  private:
  	static Ann *m_instance;
  	double calculate_a(double);
    double calculate_result(vector <int>, vector <int>);
  	double calculate_weight(double, double, double, double);
    double calculate_output_layer_delta(double, double);
    double calculate_delta(double, double);
  	int classify(vector <pair<int, double> >);
  	vector <vector <Node> > m_layers;
  	vector <vector <double> > m_x_values;
  	vector <vector <double> > m_input_values;
  	vector <int> m_structure;
  	vector < vector <double> > m_y_values;
  	vector < vector <double> > m_output_values;
  	vector <int> m_nonconverted_output;
  	int m_iter;
  };

#endif
