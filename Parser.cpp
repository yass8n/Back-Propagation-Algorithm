# include "Parser.h"
# include <sstream>

Parser::Parser()
{
}
void Parser::convert(vector <double> &output, int data, int size_of_output_layer){
	for (int i =0; i < size_of_output_layer; i++){
		output.push_back(0.9);
	}
	output[data] = 0.1;

}
void Parser::parse_all(char *train_input, char *train_output, char *test_input, char *test_output, char *structure, char *weights, int iter){
	Ann *ann = Ann::instance();
	ann->m_iter = iter;
	parse_structure(structure);
	parse_weights(weights);
	parse_train_input(train_input);
	parse_train_output(train_output);
	parse_test_input(test_input);
	parse_test_output(test_output);
}
void Parser::parse_train_input(char *train_input){
    Ann *ann = Ann::instance();
	string data;
	m_train_input_file.open(train_input, ifstream::in);
	while (getline(m_train_input_file, data) ){
		istringstream stream(data); //creating a stringstream to hold the line
		string token; //this will hold each string...these strings contain number values..example "0.11"
		vector <double> x_values; //creating a temporary vector to store the x values
		while(getline(stream, token, ' ')) //we are seperating the stream by spaces and putting each value into the token variable
		{
			x_values.push_back(atof(token.c_str())); //adding the x values into the vector 
		}
		ann->m_x_values.push_back(x_values); //adding the vector into the the ann vector of x_value vectors
	}
}
void Parser::parse_train_output(char *train_output){
    Ann *ann = Ann::instance();
    string data;
    int size_of_output_layer = ann->m_structure[ann->m_structure.size()-1];
	m_train_output_file.open(train_output, ifstream::in);
	while (m_train_output_file >> data) {
		vector <double> output;
		convert(output, atoi(data.c_str()), size_of_output_layer);
		ann->m_y_values.push_back(output);
    }
}
void Parser::parse_test_output(char *test_output){
    Ann *ann = Ann::instance();
    string data;
    int size_of_output_layer = ann->m_structure[ann->m_structure.size()-1];
	m_test_output_file.open(test_output, ifstream::in);
	while (m_test_output_file >> data) {
		vector <double> output;
		ann->m_nonconverted_output.push_back((int)atof(data.c_str()));
		convert(output, atoi(data.c_str()), size_of_output_layer);
		ann->m_output_values.push_back(output);
    }
}
void Parser::parse_test_input(char *test_input){
   Ann *ann = Ann::instance();
	string data;
	m_test_input_file.open(test_input, ifstream::in);
	while (getline(m_test_input_file, data) ){
		istringstream stream(data); //creating a stringstream to hold the line
		string token; //this will hold each string...these strings contain number values..example "0.11"
		vector <double> x_values; //creating a temporary vector to store the x values
		while(getline(stream, token, ' ')) //we are seperating the stream by spaces and putting each value into the token variable
		{
			x_values.push_back(atof(token.c_str())); //adding the x values into the vector 
		}
		ann->m_input_values.push_back(x_values); //adding the vector into the the ann vector of input_value vectors
	}
}
void Parser::parse_weights(char *weights){
    Ann *ann = Ann::instance();
    string data;
    vector <int> structure_vect = ann->m_structure;
	m_weights_file.open(weights, ifstream::in);
	for (int i=0; i < structure_vect.size(); i++){ //loop structure.size() times ...3 times in our case
		vector <Node> node_vector; //creating 3 total node vectors that we will put in our ann m_layers vector of vectors
		for(int j=0; j < structure_vect[i]; j++){ //looping n times, where n is the current structure value starting from structure[0]
		    vector <double> weights_vect; 
			for(int k=0; k < structure_vect[i+1]; k++){
				/* we are creating a vector of size structure[i+1], structure[i] times */
				m_weights_file >> data;
				weights_vect.push_back(atof(data.c_str())); 
			}
			Node node;
			node.m_weights = weights_vect;
			node_vector.push_back(node);
		}
		ann->m_layers.push_back(node_vector);
    }
}
void Parser::parse_structure(char *structure){
    Ann *ann = Ann::instance();
    string data;
	m_structure_file.open(structure, ifstream::in);
	while (m_structure_file >> data) {
		ann->m_structure.push_back(stoi(data));
    }
}
