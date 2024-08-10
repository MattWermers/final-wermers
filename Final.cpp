#include "Node.h"
#include "Graph.h"

int main(){

    // cout << "\n\nTesting node.cpp\n";
    // Node* test_node = new Node;
    // test_node->set_data( "ACTGACTGA" );
    // cout << "Test node pre-child";
    // test_node->print_data();
    // Node* test_node_dos = new Node;
    // test_node_dos->set_data( "LETS GOOOOOOO" );
    // test_node->add_child( test_node_dos , 1 );
    // cout << "\nTest node post-child";
    // test_node->print_data();
    // cout << "\nTest node dos";
    // test_node_dos->print_data();
    // test_node->remove_child( test_node_dos );
    // cout << "\nTest node after childs death";
    // test_node->print_data();
    // cout << endl;

    cout << "\n\nTesting graph node generation";
    Graph* test_graph = new Graph;
    test_graph->generate_graph( "testfile.fasta");
    list<Node*> c_nodes = test_graph->return_nodes();
    for ( auto node : c_nodes ){
        node->print_data();
    }

    cout << "\n\nTesting find_overlap";
    test_graph->find_overlap();
    for ( auto node : c_nodes ){
        node->print_data();
    }

    cout << "\n\nTesting true_overlap";
    for ( auto parent : c_nodes ){
        if ( parent->parent_to > 1 ){
            test_graph->overlap_helper( parent );
        }
    }
    for ( auto node : c_nodes ){
        node->print_data();
    }


    cout << "\nPrinting DNA, fingers crossed";
    test_graph->output_DNA();
    cout << endl;
}