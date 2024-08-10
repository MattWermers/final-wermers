#include "Graph.h"
#include <list>
#include <fstream>
#include <iostream>
#include <string>

// Graph::Graph(){
//     int length = 0;
// }

using namespace std;

Node* Graph::create_node( string fragment ){
    Node* new_node = new Node;
    new_node->set_data( fragment );
    return new_node;
}

Node* true_overlap( Node* parent , Node* c_one , Node* c_two ){
    string p_kmer = parent->get_kmer();
    string c_one_kmer = c_one->get_kmer();
    string c_two_kmer = c_two->get_kmer();

    string suffix = p_kmer.substr( p_kmer.size() - 3 , 3 );
    string prefix_one;
    string prefix_two;

    int c_one_mpos;
    int c_two_mpos;

    int loop_helper = 0;

    // cout << "\nin true overlap";
    // cout << "\n    p_kmer = " << p_kmer;
    // cout << "\n    p-kmer suffix = " << suffix;
    // cout << "\n    suffix length = " << suffix.size();
    // cout << "\n    c_one_kmer = " << c_one_kmer;
    // cout << "\n    c_one size = " << c_one_kmer.size();
    // cout << "\n    c_two_kmer = " << c_two_kmer;
    // cout << "\n    c_two size = " << c_two_kmer.size();
    // cout << endl;

    for ( int i = c_one->match_position.front() ; loop_helper < c_one->match_position.size() ; i++ ){
        prefix_one = c_one_kmer.substr( i , 3 );
        // cout << "\n    c_one_prefix = " << prefix_one;
        if ( suffix == prefix_one ){
            // cout << "\n    correct c_one_prefix = " << prefix_one;
            c_one_mpos = i;
            break;
        }
        loop_helper++;
    }
    // cout << endl;
    loop_helper = 0;
    for ( int i = c_two->match_position.front() ; loop_helper < c_two->match_position.size() ; i++ ){
        prefix_two = c_two_kmer.substr( i , 3 );
        // cout << "\n    c_two_prefix = " << prefix_two;
        if ( suffix == prefix_two ){
            // cout << "\n    correct c_two_prefix = " << prefix_two;
            c_two_mpos = i;
            break;
        }
        loop_helper++;
    }

    // cout << endl;
    loop_helper = 1;

    // cout << "\n    c_one size - c_one_mpos = " << c_one_kmer.size() - c_one_mpos;
    // cout << "\n    c_two size - c_two_mpos = " << c_two_kmer.size() - c_two_mpos;

    while ( true ){
        suffix = p_kmer.substr( p_kmer.size() - (3 + loop_helper ) , 3 + loop_helper );
        // cout << "\n    suffix in while loop = " << suffix;
        // cout << "\n    ( 1 + c_one_kmer.size()) - ( (c_one_kmer.size() - c_one_mpos) + loop_helper = " << (1 + c_one_kmer.size()) - ( (c_one_kmer.size() - c_one_mpos) + loop_helper );
        // cout << "\n    ( 1 + c_two_kmer.size()) - ( (c_two_kmer.size() - c_two_mpos) + loop_helper ) = " << (1 + c_two_kmer.size()) - ( (c_two_kmer.size() - c_two_mpos) + loop_helper );
        if ( ( 1 + c_one_kmer.size()) - ( (c_one_kmer.size() - c_one_mpos) + loop_helper ) > 0 ){
            if ( ( 1 + c_two_kmer.size()) - ( (c_two_kmer.size() - c_two_mpos) + loop_helper ) > 0 ){
                prefix_one = c_one_kmer.substr( c_one_mpos - loop_helper , 3 + loop_helper );
                // cout << "\n    prefix one = " << prefix_one;
                prefix_two = c_two_kmer.substr( c_two_mpos - loop_helper , 3 + loop_helper );
                // cout << "\n    prefix two = " << prefix_two;
                if ( prefix_one == suffix && prefix_two != suffix ){
                    parent->remove_child(c_two);
                    return c_one;
                }
                else if ( prefix_two == suffix ){
                    parent->remove_child(c_one);
                    return c_two;
                }
            }
            else{
                prefix_one = c_one_kmer.substr( c_one_mpos - 1 - loop_helper , 4 + loop_helper );
                suffix = p_kmer.substr( p_kmer.size() - (3 + loop_helper + 1) , 4 + loop_helper );
                if ( prefix_one == suffix ){
                    parent->remove_child(c_two);
                    return c_one;
                }
                else{
                    parent->remove_child(c_one);
                    return c_two;
                }
            }
        }
        else{
            prefix_two = c_two_kmer.substr( c_two_mpos - 1 - loop_helper , 4 + loop_helper );
            suffix = p_kmer.substr( p_kmer.size() - (3 + loop_helper + 1) , 4 + loop_helper );
            if ( prefix_two == suffix ){
                parent->remove_child(c_one);
                return c_two;
            }
            else{
                parent->remove_child(c_two);
                return c_one;
            }
        }
        // cout << endl;

        loop_helper++;
    }
    // cout << "\nleaving true overlap\n\n";
    return c_one;
}

Node* Graph::overlap_helper( Node* parent ){
    list<Node*> children = parent->return_children();
    Node* c_node = children.front();
    children.pop_front();
    Node* c_node_two;
    if ( children.size() > 1 ){
        c_node_two = overlap_helper( parent );
    }
    else{
        // c_node_two = children.front();
        // children.pop_front();
        return c_node;
    }
    return true_overlap( parent , c_node , c_node_two );
}

void Graph::find_overlap(){
    string p_kmer;
    string suffix;
    string prefix;
    string c_kmer;
    int j;
    for ( auto pot_parent : graph_nodes ){
        p_kmer = pot_parent->get_kmer();
        // cout << "\np kmer = " << p_kmer;
        // cout << "\nhere";
        suffix = p_kmer.substr( p_kmer.size() - 3 , 3 );
        // cout << "\nparent suffix = " << suffix;
        for ( auto pot_child : graph_nodes ){
            if ( pot_parent != pot_child ){
                // cout << endl << suffix;
                c_kmer = pot_child->get_kmer();
                // cout << "\nc_kmer = " << c_kmer;
                j = c_kmer.size() - 4;
                while ( j > 0 ){
                    // cout << "\nthere";
                    // cout<< "\nj = " << j;
                    prefix = c_kmer.substr( j , 3 );
                    // cout << "\n    " << prefix;
                    // cout << "\n is prefix == suffix ?" << (suffix == prefix);
                    if ( suffix == prefix ){
                        // cout << "\nmathc found!";
                        pot_parent->add_child( pot_child , j );
                        pot_parent->parent_to++;
                        break;
                    }
                    j--;
                }
            }
        }
    }
    // for ( auto parent : graph_nodes ){
    //     if ( parent->parent_to > 1 ){
    //         overlap_helper( parent );
    //     }
    // }
}

void Graph::generate_graph( string filename ){
    ifstream FASTA( filename );
    string line;
    string full_line = "";
    bool firsttime = true;
    while ( getline( FASTA, line ) ){
        if ( line.front() == '>' && firsttime != true ){
            // if ( full_line.size() < smallest_length ){
            //     smallest_length = full_line.size();
            // }
            graph_nodes.push_back( create_node( full_line ) );
            full_line = "";
        }
        else if ( line.front() != '>' ){
            line = line.substr( 0 , line.size() - 1);
            full_line = full_line + line;
        }
        else ( firsttime = false );

    }
    graph_nodes.push_back( create_node( full_line ) );
    FASTA.close();
}

list<Node*> Graph::return_nodes(){
    return graph_nodes;
}

Node* Graph::out_helper(){
    for ( auto node : graph_nodes ){
        if ( node->pointed_by == 0 ){
            return node;
        }
    }
    return NULL;
}

void Graph::output_DNA(){
    Node* node_oi = out_helper();
    
    string output_string;
    
    list<Node*> c_children;
    
    cout << endl;
    
    string last_suffix;
    string current_prefix;
    
    int loop_helper = 0;
    int length_to_cut = 0;
    bool first = true;
    
    do{
        output_string = node_oi->get_kmer();
        c_children = node_oi->return_children();
        if ( !first ){
            // cout << "\n last suffix = " << last_suffix << "\n";
            // cout << "\n loop helper = " << loop_helper << "\n";
            // cout << " match_position.size() " << node_oi->match_position.size();
            for ( auto mpos : node_oi->match_position ){
                current_prefix = output_string.substr( mpos , 3 );
                // cout << "\nloop helper = " << loop_helper;
                // cout << "\n current prefix = " << current_prefix;
                // cout << "\n mpos = " << mpos;
                if ( last_suffix == current_prefix ){
                    length_to_cut = mpos + 3;
                    //cout << "\nlength to cut = " <<  length_to_cut << "\n";
                    break;
                }
                loop_helper++;
            }
            
            // cout << output_string.substr( length_to_cut , output_string.size() ) + " | ";
            //cout << "\nbfore cut " << output_string << "\nafter cut ";
            cout << output_string.substr( length_to_cut );
            loop_helper = 0;
            length_to_cut = 0;
        }
        else {
            first = false;
            cout << output_string;
            
        }
        last_suffix = output_string.substr( output_string.size() - 3 , 3 );
        node_oi = c_children.front();
    } while ( node_oi != NULL );
}