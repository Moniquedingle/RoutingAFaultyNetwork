// we want to  create a graph and then break some of the edges
// then we want to send a packet from one host to another host

#include <vector>

using namespace std;

class Edge{

   public:
   Edge();
   ~Edge();


   private:
 
   int id;
   int cost;
   bool state;
};

class EndHost{

   public:
   EndHost();
   ~EndHost();

   private:
   
   int id;
   int numLinks;
   vector<Edge> link;
};


struct Packet{

   int dest;
   bool arrived;
   vector<int> path;
};
