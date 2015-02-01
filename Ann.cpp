// ann.cpp
// aniss, yaseen
# include "Ann.h"
# include <math.h>
Ann *Ann::m_instance = NULL;
Ann *Ann::instance()
{
  if (m_instance == NULL)
  {
    m_instance = new Ann();
  }
 
  return m_instance;
}
double Ann::calculate_a(double in){
	return 1/(1+ exp(-in));
}
double Ann::calculate_result(vector <int> classifications, vector <int> output){
	double correct = 0;
	for (int i = 0; i < output.size(); i++){
		if (classifications[i] == output[i])
			correct++;
	}
	return correct/(double)output.size();
}
int Ann::classify(vector <pair <int, double> > euclidean_values){
	double smallest = 10000000000;
	int index = 0;
	for (int i = 0; i < euclidean_values.size(); i ++){
		if (euclidean_values[i].second < smallest){
			smallest = euclidean_values[i].second;
			index = i;
		}

	}
	return euclidean_values[index].first;
}
double Ann::calculate_output_layer_delta(double a, double y){
	return a * (1 - a) * (y - a);
}
double Ann::calculate_delta(double a, double multiplication_value){
	return a * (1 - a) * multiplication_value;
}
double Ann::calculate_weight(double weight, double alpha, double a, double delta){
	return weight + (alpha * a * delta);
}
void Ann::run_back_propogation(){
	if (m_x_values.size() != m_y_values.size()) {
		cerr << "ERROR IN BACK PROPOGATION FUNCTION" << endl;
		exit(0);
	}
	for (int iter = 0; iter < m_iter; iter ++){
		/* step 1 */
		for (int it = 0; it < m_x_values.size(); it++){ //for all the values 
		    // cout << "initializing the a values of the input layer" << endl;
			for (int i = 0; i < m_x_values.size(); i++){ //for each set of x values
				//initializing the a values of the input layer
				m_layers[0][i].m_a = m_x_values[it][i];
			}

			/* step 2, 3 */
			// cout << "step 2, 3" << endl;
			for (int layer = 1; layer < m_layers.size(); layer++){ //for each layer not including the input layer
				for (int current_node = 0; current_node < m_layers[layer].size(); current_node ++){ 
					//for each node in the current layer, calculate the a value
					m_layers[layer][current_node].m_in = m_layers[layer][current_node].m_dummy;
					for (int behind_node = 0; behind_node < m_layers[layer-1].size(); behind_node++){
						m_layers[layer][current_node].m_in += (m_layers[layer-1][behind_node].m_a * m_layers[layer-1][behind_node].m_weights[current_node]);
					}
					m_layers[layer][current_node].m_a = calculate_a(m_layers[layer][current_node].m_in);
				}
			}
			/* step 4 */
			int output_layer = m_layers.size()-1;
			for (int current_node = 0; current_node < m_layers[output_layer].size(); current_node++){ //for each node in the output layer
				m_layers[output_layer][current_node].m_delta = calculate_output_layer_delta(m_layers[output_layer][current_node].m_a , m_y_values[it][current_node]);
			}
			/* step 5, 6 */
			for (int layer = output_layer -1; layer >= 0; layer--){
				for (int current_node = 0; current_node < m_layers[layer].size(); current_node++){
					//looping through all nodes in the current layer
					int front_layer = layer +1;
					double multiplication_value = 0;
					//calculating the value of the addition of all the forwardnodes' delta * weight from current node to forwardnode
					for (int forward_node = 0; forward_node < m_layers[layer+1].size(); forward_node++){
						multiplication_value += (m_layers[front_layer][forward_node].m_delta * m_layers[layer][current_node].m_weights[forward_node]);
					}
						double a = m_layers[layer][current_node].m_a;
						m_layers[layer][current_node].m_delta = calculate_delta(m_layers[layer][current_node].m_a, multiplication_value);
				}
			}
			/* step 7 */
			/* calculating new dummy weights */
			for (int layer = 0; layer < m_layers.size(); layer ++){
				for (int current_node = 0; current_node < m_layers[layer].size(); current_node ++){
					m_layers[layer][current_node].m_dummy = calculate_weight(m_layers[layer][current_node].m_dummy, .01, 1, m_layers[layer][current_node].m_delta);
				}
			}
			/* calculating all other weights */
			for (int layer = 0; layer < m_layers.size()-1; layer ++){
				for (int current_node = 0; current_node < m_layers[layer].size(); current_node ++){
					for (int forward_node = 0; forward_node < m_layers[layer+1].size(); forward_node ++){
						m_layers[layer][current_node].m_weights[forward_node] = calculate_weight(m_layers[layer][current_node].m_weights[forward_node], .01, m_layers[layer][current_node].m_a, m_layers[layer+1][forward_node].m_delta);
					}
				}
			}
		}
	}

}
void Ann::print_values(){

	int layer = m_layers.size()-2;
	int first_node = 0;
	for (int forward_node = 0; forward_node < m_layers[layer+1].size(); forward_node ++){
		cout << m_layers[layer][first_node].m_weights[forward_node] << endl;
	}

	vector <int> classifications;
	for (int iter = 0; iter < m_nonconverted_output.size(); iter ++){
		/* step 1 */
			for (int i = 0; i < m_x_values.size(); i++){ //for each set of x values
				//initializing the a values of the input layer
				m_layers[0][i].m_a = m_x_values[iter][i];
			}

			/* step 2, 3 */
			for (int layer = 1; layer < m_layers.size(); layer++){ //for each layer not including the input layer
				for (int current_node = 0; current_node < m_layers[layer].size(); current_node ++){ 
					//for each node in the current layer, calculate the a value
					m_layers[layer][current_node].m_in = m_layers[layer][current_node].m_dummy;
					for (int behind_node = 0; behind_node < m_layers[layer-1].size(); behind_node++){
						m_layers[layer][current_node].m_in += (m_layers[layer-1][behind_node].m_a * m_layers[layer-1][behind_node].m_weights[current_node]);
					}
					m_layers[layer][current_node].m_a = calculate_a(m_layers[layer][current_node].m_in);
				}
			}
		/* calculating euclidean distance */
		int output_layer = m_layers.size()-1;
		vector <pair< int, double> > euclidean_values; 
		for (int i = 0; i < m_output_values.size(); i++){ 
			double inside_square_root_value = 0;
			for (int output_node = 0; output_node < m_layers[output_layer].size(); output_node++){ //for each node in the output layer
				inside_square_root_value += pow((m_layers[output_layer][output_node].m_a - m_output_values[i][output_node]), 2);
			}
			double euclidean_distance = sqrt(inside_square_root_value);
			pair<int,double> Pair = make_pair(m_nonconverted_output[i], euclidean_distance);
			euclidean_values.push_back(Pair);
		}
		classifications.push_back(classify(euclidean_values));
	}
    cout << setprecision(2) << fixed;
	double percentage = calculate_result(classifications, m_nonconverted_output);
	cout << "\n" << percentage * 100 << '%' << endl;
		ofstream outputFile("ann_output.txt");
		for (int i = 0; i < classifications.size(); i ++)
			outputFile << classifications[i] << endl; 
}
