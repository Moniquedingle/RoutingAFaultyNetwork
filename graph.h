// we want to  create a graph and then break some of the edges
// then we want to send a packet from one host to another host

#include <vector>

using namespace std;

class Edge{

   public:
   Edge();
   Edge( const Edge &edgeObject );
   ~Edge();

   int getLinkId();
   void setLinkId( int linkValue );
   void setState( bool newState );
   bool getState();


   private:

   int linkId;
   bool state; // whether the edge is faulty or not
};

class EndHost{

   public:
   EndHost();
   // EndHost( const EndHost &endHostObject  );
   ~EndHost();

   int getHostId();
   void setHostId( int hostValue );
   int getNumLinks();
   void setLink( Edge linkValue );
   int getLink( int index ); // returns Edge ID

   private:

   int hostId;
   int numLinks;
   vector<Edge> link;
};


struct Packet{

   int hops; // ++ when value added to path
   int dest;
   bool arrived;
   vector<int> path; // path characterized by Edge int id
};
