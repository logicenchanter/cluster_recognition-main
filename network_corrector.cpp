#include "network_corrector.h"

#include <fstream>
#include <iostream>
#include <vector>

 
Network_Corrector::Network_Corrector () : no_nodes{0}, hub_node_index{0} { }

Network_Corrector::~Network_Corrector ()  { }

// =========
// =========
// =========

void Network_Corrector::read_network_file (const std::string & input_file_name) {
  std::ifstream input_file (input_file_name.c_str ()); 
  int col1 = -1;
  unsigned int line_counter = 0;
  while (!input_file.eof()) {
    int col1_tmp, col2, col3;
    double col4;
    input_file >> col1_tmp;
    if (col1 == col1_tmp) break;
    col1 = col1_tmp;
    input_file >> col2;    
    input_file >> col3;
    input_file >> col4;
    ///std::cout << col1 << " " << col2 << " " << col3 << " " << col4 << std::endl;
    ++line_counter;
    column_1_to_3.resize (line_counter);
    column_1_to_3[line_counter-1].push_back (col1);
    column_1_to_3[line_counter-1].push_back (col2);
    column_1_to_3[line_counter-1].push_back (col3);
    column_4.push_back (col4);
    
    if (no_nodes < col2) no_nodes = col2;
    if (no_nodes < col3) no_nodes = col3;    
  }
  
  node_call_counter.resize (no_nodes, 0);
//  for (unsigned int i = 0; i<node_call_counter.size(); ++i)
 //   node_call_counter[i] = 0;
}

// =========
// =========
// =========

void Network_Corrector::make_node_connection_matrix () {
  for (unsigned int i = 0; i<column_4.size(); ++i) {
    int current_node = column_1_to_3[i][1];
    if (node_connections.size() < current_node) 
      node_connections.resize(column_1_to_3[i][1]);
    //std::cout << current_node << " " << column_1_to_3[i][2] << " " << node_connections.size() << std::endl;
   node_connections[current_node-1].push_back (column_1_to_3[i][2]);

  }
}

// =========
// =========
// =========

void Network_Corrector::make_node_call_counter () {
  for (unsigned int i = 0; i<column_4.size(); ++i) {
   ++node_call_counter[column_1_to_3[i][2]-1];
   ++node_call_counter[column_1_to_3[i][1]-1];   
  }
}

// =========
// =========
// =========

void Network_Corrector::print_node_connection_matrix () {
  std::cout << "\nnode connection matrix:\n";
  for (unsigned int i = 0; i < node_connections.size(); ++i) {
    std::cout << i+1 << " : ";
    for (unsigned int j = 0; j < node_connections[i].size(); ++j) {
      std::cout << " " << node_connections[i][j];
    }
    std::cout << "\n";    
  }
  std::cout << std::endl;      
}

// =========
// =========
// =========

void Network_Corrector::print_node_call_counter () {
  std::cout << "\nnode node call counter:\n";
  for (unsigned int i = 0; i < node_call_counter.size(); ++i) {
    std::cout << i+1 << " : " << node_call_counter[i] << "\n";
  }
  std::cout << std::endl;      
}

// =========
// =========
// =========

void Network_Corrector::find_hub_node_index () {
  int max = 0, max_index = 0;
  for (unsigned int i = 1; i < node_call_counter.size(); ++i) {
    if (max < node_call_counter[i]) {
      max = node_call_counter[i];
      max_index = i;
    }
  }
  hub_node_index = max_index + 1;
  std::cout << "\nhub node index = " << hub_node_index << std::endl;      
}

// =========
// =========
// =========

void Network_Corrector::find_islands () {
  for (unsigned int i = 0; i < node_call_counter.size(); ++i) {
    if (node_call_counter[i] == 1) {
      if (node_connections[i].size () == 0) {
        // std::cout << "isolated node : " << i+1 << std::endl;
        // an island
      } else if (node_connections[i].size() == 1) {
        if (node_call_counter [node_connections[i][0]-1] == 1) {
          // an island
        std::cout << "island of : " << i+1 << " and " << node_connections[i][0] << std::endl;
        }
      } else continue;
    }
  }
}

// =========
// =========
// =========

void Network_Corrector::remove_islands () {

}

// =========
// =========
// =========

void Network_Corrector::output_network_file (const std::string &) {

}
