#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

Edge::Edge()
   {
     linkId = 0;
     state = false;
     visited = false;
   }

Edge::Edge( const Edge &edgeObject )
   {
     linkId = edgeObject.linkId;
     state = edgeObject.state;
     visited = edgeObject.visited;

   }

Edge::~Edge()
   {
     linkId = 0;
     state = false; // true = broken link
     visited = false;
   }

int Edge:: getLinkId()
   {
     return linkId;
   }

void Edge:: setLinkId( int linkValue )
   {
     linkId = linkValue;
   }

void Edge:: setState( bool newState )
   {
     state = newState;
   }

bool Edge:: getState()
   {
     return state;
   }

void Edge:: setVisited()
   {
     visited = true;
   }

bool Edge:: getVisited()
   {
     return visited;
   }

EndHost::EndHost()
   {
     hostId = 0;
     numLinks = 0;
   }

EndHost::~EndHost()
   {
     hostId = '0';
     numLinks = 0;
     link.clear();
   }

int EndHost:: getHostId()
   {
     return hostId;
   }

void EndHost:: setHostId( int hostValue )
   {
     hostId = hostValue;
   }

int EndHost:: getNumLinks()
   {
     return numLinks;
   }

void EndHost:: setLink( Edge linkValue )
   {
     link.push_back( linkValue );
     numLinks++;
   }

int EndHost:: getLink( int index )
   {
     return link.at( index ).getLinkId();
   }

Packet::Packet()
   {
     hops = 0; // ++ when value added to path
     dest = 0;
     arrived = false;
     path.resize(0);
   }

Packet::~Packet()
   {
     hops = 0; // ++ when value added to path
     dest = 0;
     arrived = false;
     path.clear();
   }
