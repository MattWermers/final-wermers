#ifndef GRAPH_H__
#define GRAPH_H__

#include "Node.h"
#include <list>
#include <fstream>
#include <iostream>
#include <string>

class Graph{
    private:
        list<Node*> graph_nodes;
        Node* create_node( string fragment );
    public:
        void generate_graph( string filename );

        Node* overlap_helper( Node* parent );

        void find_overlap();

        list<Node*> return_nodes();

        Node* out_helper();

        void output_DNA();
};



#endif