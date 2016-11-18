#include "graph.h"

int main()
   {
     // vector of identical packets
      // all packets will go to the same destination and their numHops will be compared at the end
     vector<Packet> packets;

     // ask user for data
      // how many end hosts (max 50)
      // how many links per end host (max 3)

    // randomly generate graph based on user info with some broken links

    // ask sengupta for life

    // packet always starts route at end host ID 1 and ends at the last end host ID

    return 0;
   }

// generateGraph
void generateGraph( int numEndHosts, int numLinksPerHost )
   {

   }

// Dijkstras
  // searches through the packet vector and compares int hops
  // returns the index of the packet that had the least amount of hops
int Dijkstras( Packet packetRunner )
   {

   }

bool simulate( Packet packetRunner )
   {
    // uses Dijkstras

    // for loop that iterates through all of the packets
     // checks that at least one packet arrived - return true
     // if zero packets arrived - return false and error message
     // uses the "arrived" variable in the packet struct
   }
