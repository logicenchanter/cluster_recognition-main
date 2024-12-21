#ifndef NETWORK_CORRECTOR_H
#define NETWORK_CORRECTOR_H

#include <string>
#include <vector>

class Network_Corrector {
public:
  Network_Corrector ();
  ~Network_Corrector ();

  void read_network_file (const std::string &);
  void make_node_connection_matrix ();
  void make_node_call_counter ();  
  void print_node_connection_matrix ();  
  void print_node_call_counter ();
  void find_hub_node_index ();    
  void find_islands ();
  void remove_islands ();
  void output_network_file (const std::string &); 
  
private:
  unsigned int no_nodes;
  unsigned int hub_node_index;  
  std::vector <std::vector<int>> column_1_to_3;
  std::vector <std::vector<int>> node_connections;
  std::vector <int> node_call_counter;
  std::vector <int> island_node;
  std::vector <double> column_4;

    
};

#endif
