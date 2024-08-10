# WermersFinal
De Bruijn graph for genome assembly. 
Generating a string of DNA from fragments that make it up. This functions by taking the end of fragments of DNA making up a larger chain and comparing them to subsequences within other nodes. At first multiple children will be found but then you increase the specificity from taking longer and longer chunks (from the end of the parent, and from the found match in the child) until you are left with only one child.

Input 
  A typical file format used in bioinformatics is the FASTA file. These files are strucutred to have a title of the following DNA sequence preceded by >>. This title can be a name for the sequence, the name for a gene, or data on its source/composition. To read these files I created the generate_graph function as a member of the graph and created a mock FASTA file with some sequences that overlap by slightly varying amounts. This is the testfile.fasta you see within the repository. I only added this test file so it is hardcoded in final.cpp which contains the main function. The generate_nodes function works by first skipping the first line with >> (always the first line in the file) and compilining the lines of DNA the follow. In reality these lines of DNA, if not seperated by a line containing >>, are contiguos. However, the test function only has one line for each strings of DNA. The function works with multi line DNA strings but it not necessary to test the program. 
The Node Class 
  Private Members 
      kmer: The kmer is a full string of DNA found in the fasta file. It is a fragment of the parent DNA we are trying to make. 
      length: The length of the full kmer. 
      children: This is a list of node pointers to children that are found to have some overlap with the parent kmer of the node. Parents are not recorded as this is a directed graph. Public Members 
      pointed_to: a boolean that is true if this node is pointed to, if it is false, this represents the parent node. 
      pointed_by: a counter of how many nodes point to this one. 
      match_position: indicates where a match to another node occured. 
      set_data: sets the initial values of the node. 
      add_child: functions both to add a child to the list of children of the parent node, sets child pointed_to to true, and increments pointed_by of the child.       
      remove_child: does the opposite of add_child, if the child node is no longer pointed to, sets child pointed_to to false. 
      return_children: returns children list to by used without being modified. 
      get_kmer: returns kmer data without it being modified. 
      print_data: prints the above values of the node for debugging or following the progam. 
  The Graph Class 
    Private Members 
      graph_nodes: A list of nodes from the node class initialized from generate_graph->create_node. 
      create_node: initializes and returns a new node of the node class to be added to graph_nodes. Public Members 
      generate_graph: Reads the input FASTA file and generates nodes from file. 
      overlap_helper: This recursivly pops nodes off the children list of a node until 1 child is remaining, as it moves back up the stack it calls the non-member function true_overlap, with the node returned from the 
                      pervious iteration, and the node found in that interation. true_overlap returns the child with the longest overlap. When overlap_helper is complete, one node with the longest congruency is returned. 
      find_overlap: This is the initial overlap finder. It takes the last 3 characters of a nodes kmer and finds all places on all other nodes where these three characters in this order can be found. It calls the node 
      add_child function sending the node to be added and the position in the childs kmer where this overlap occured. 
      return_nodes: A function implemented so the graph nodes can be iterated through in the test Final.cpp function. 
      out_helper: Finds and returns the node that is not pointed to. 
      output_DNA: Calls outhelper to find which node to start with. It prints the kmer of the node, then moves to the next node. The proper location to print 
                  from is found, and the leading characters are trimmed. This results in a rebuild DNA sequence that should be the main sequence with no repeated sections.

One Challenge: 
  I stuggled getting this done on time. I had one test case that would loop indefinetly though it was constructed nearly the exact same as the other test case. I had a hard time iterating and trying to remove values from a vector and had to work around it. 
One thing I debugged: 
  I had to debug many things for this project. I really stuggled with the true_overlap function and its still not perfect. I had trouble making sure i didnt get a seg fault and a hard time making sure I was looking at the right data (right substring). When printing the DNA I had a hard time making sure that sections of DNA were not repeated. All the nodes worked except the last one which weirded me out. I realized I was not looking at the right match 
  position! 
One mistake I made: 
  Getting in way over my head. Not keeping match length and children pointers in a structure. I was too deep into the project to fix this.
