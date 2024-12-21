#include <iostream>
#include <fstream>

#include "network_corrector.h"

int main () {

  Network_Corrector network_corrector;
  
  network_corrector.read_network_file ("start.inp");
  network_corrector.make_node_connection_matrix ();
  network_corrector.print_node_connection_matrix ();  
  network_corrector.make_node_call_counter ();     
  network_corrector.print_node_call_counter ();   
  network_corrector.find_hub_node_index ();  
  network_corrector.find_islands ();
  network_corrector.remove_islands ();
  network_corrector.output_network_file ("start_corrected.inp"); 
    
}

