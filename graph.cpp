#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

Edge::Edge()
   {
    linkId = 0;
    state = false;
   }

Edge::Edge( const Edge &edgeObject )
   {
     linkId = edgeObject.linkId;
     state = edgeObject.state;
   }

Edge::~Edge()
   {
    linkId = 0;
    state = false;
   }

int Edge:: getLinkId()
   {
    return linkId;
   }

void Edge:: setLinkId( int linkValue )
   {
    linkId = linkValue;
   }

EndHost::EndHost()
   {
     hostId = 0;
     numLinks = 0;
   }

EndHost::~EndHost()
   {
    hostId = 0;
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
