#include <vector>

using namespace std;

class Edge{

   public:

   Edge();
   Edge( const Edge &edgeObject );
   ~Edge();

   int getLinkId();
   void setLinkId( int linkValue );
   void setState( bool state );
   bool getState();
   bool getVisited();
   void setVisited();


   private:

   int linkId;
   bool state; // whether the edge is faulty or not
   bool visited;
};

struct Packet{

   int hops; // ++ when value added to path
   int dest;
   bool arrived;
   vector<int> path; // path characterized by Edge int id

   Packet();
   ~Packet();
};
