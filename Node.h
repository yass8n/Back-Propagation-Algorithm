//Yaseen Aniss
//Node.h
# ifndef _NODE_H
# define _NODE_H
# include <string>
# include <iostream>
# include <vector>
using namespace std;
class Node {
  public :
    friend class Ann;
    friend class Parser;
    ~Node(){};
    Node ();
  private:
    double m_a;
    double m_in;
    double m_delta;
    double m_dummy;
    vector <double> m_weights;
};

# endif
