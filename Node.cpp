#include "Node.h"

using namespace std;

Node::Node(){
    bool finished = false;
    bool pointed_to = false;
    int pointed_by = 0;
    int parent_to = 0;
}

void Node::set_data( string fragment ){
    this->kmer = fragment;
    this->length = this->kmer.size();
}

void Node::add_child( Node* nChild , int match_position ){
    this->children.push_back( nChild );
    nChild->pointed_by++;
    nChild->pointed_to = true;
    nChild->match_position.push_back( match_position );
}

void Node::remove_child ( Node* nChild ){
    this->children.remove( nChild );
    nChild->pointed_by--;
    this->parent_to--;
    if ( nChild->pointed_by < 1 ){
        nChild->pointed_by = 0;
        nChild->pointed_to = false;
    }
}

list<Node*> Node::return_children(){
    return this->children;
}

string Node::get_kmer(){
    return this->kmer;
}

void Node::print_data(){
    cout << "\nkmer = " << this->kmer;
    cout << "\n   Length = " << this->length;
    cout << "\n   Pointed to = " << this->pointed_to;
    cout << "\n   Pointed by = " << this->pointed_by;
    if ( pointed_to != 0 ){
        cout << "\n   Match Positions = ";
        for ( auto i : match_position ){
            cout << i << " ";
        }
    }
    cout << "\n   Parent to = " << this->parent_to;
    cout << endl;
}