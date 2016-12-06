/*******************************************************************/
/* Project title: Learning to Route through a Faulty Network       */
/* Group members: Monique Dingle, Gicelle Calderon, Phoebe Argon   */
/* Objectives: Create a graph based on user input                  */
/*             Randomly generate connections between nodes          */
/*             Randomly break links between nodes throughout graph  */
/*                    based on user input                          */
/*             Develop a routing algorithm to send a packet         */
/*                    through the faulty network                   */
/* Version: 1.0                                                    */
/* Date: 12-7-16                                                   */
/*******************************************************************/


// HEADER FILES ///////////////////////////////////////////
#include "graph.h"
#include <iostream>
#include <cstdlib>
#include <vector>

// FUNCTION PROTOTYPES ////////////////////////////////////

/*
Description: Resizes the adjancency matrix (vector) to accomodate num end hosts
Parameters: The adjacency matrix and the number of end hosts
Precondition: The user has given the number of end hosts
Postcondition: The adjancency matrix is accurately sized
Notes: None
Return: The accurately sized adjancency matrix
*/
void sizeMatrix( vector< vector<Edge> > &linkMatrix, int numEndHosts );

/*
Description: Generates a graph based on user input
Parameters: Adjacency matrix, number of end hosts, number of links per host
Precondition: Requires user input for the number of end hosts and links per host
Postcondition: Generates a graph
Notes: linkId = 0 means not connected, linkId = 1 means connected
Algorithm: Iterates through adjancency matrix and assigns link connections using
           random number generator between 0 and 1
Return: The generated adjancency matrix
*/
void generateGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts, int linkAmount);

/*
Description: Breaks links throughout the graph based on user input
Parameters: Adjacency matrix, number of end hosts
Precondition: The graph has been generated
Postcondition: The graph consists of broken links
Notes: User chooses the percentage of links to be broken
Algorithm: Randomly generate coordinates and breaks at that index based on user input
Return: Broken adjancency matrix
*/
void breakGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts );

/*
Description: Outputs the adjancency matrix/graph
Parameters: Adjacency matrix, number of end hosts
Precondition: The graph exists
Postcondition: The graph is displayed on the screen
Notes: Can only output up to 20 end hosts due to screen size
Algorithm: Iterates through graph and outputs row by row
Return: None
*/
void output( vector< vector<Edge> > &linkMatrix, int numEndHosts );

/*
Description: Simulates a packet being sent through the faulty graph
Parameters: Adjacency matrix, number of end hosts
Precondition: The graph has been generated and broken
Postcondition: The packet has attempted to route through a faulty network
Notes: The packet always starts at end host A and the destination is always the last end host
Algorithm: checks to see if the current end host is connected to the destination end host
           if yes, it hops there and the packet arrived successfully
           if no, it hops to other connected end hosts
           it repeats the above steps until either a solution is found or it is impossible
Return: true if the solution is found, false if there exists no solution
        the path the packet followed, the number of hops the packet did
*/
bool simulate( Packet &packetRunner, vector< vector<Edge> > &linkMatrix, int numEndHosts );


// MAIN PROGRAM ////////////////////////////////////////////
int main()
   {
     int numEndHosts = -1, linkAmount = -1; // -1 flag for invalid info
     unsigned int pathCounter;
     bool solutionFound = false;
     Packet packetRunner;
     vector< vector<Edge> > linkMatrix;

     // ask user for data
      // how many end hosts (max 20 to accomodate screen size)
      // how many links per end host (min 2, max 5)
      while( numEndHosts < 0 || numEndHosts > 20 )
         {
           cout << "Please input the number of desired routers (max 20): ";
           cin >> numEndHosts;
         }

      while( linkAmount < 2 || linkAmount > 5)
         {
           cout << "Please input the number of links per node (min 2, max 5): ";
           cin >> linkAmount;
         }

    // size link matrix to accomodate numEndHosts based on user input
       // all link IDs are initialized -1
    sizeMatrix( linkMatrix, numEndHosts );

    // randomly generate graph links/connections
    generateGraph( linkMatrix, numEndHosts, linkAmount );

    // randomly breaks links based on user input of how many links to break
    breakGraph( linkMatrix, numEndHosts );

    // output the graph in its current state
    output( linkMatrix, numEndHosts );

    // simulates the packet moving through the graph using developed routing algorithm
    solutionFound = simulate( packetRunner, linkMatrix, numEndHosts );

    // if the packet successfully reached the end
    if( solutionFound )
       {
         // output the destination, the number of hops the packet took, and the path followed
         cout << "Destination: " << char(packetRunner.dest + 'A') << endl;
         cout << "The packet hopped " << packetRunner.hops << " times" << endl;
         cout << "The packet followed the path: ";
         for( pathCounter = 0; pathCounter < packetRunner.path.size(); pathCounter++)
            {
             cout << char(packetRunner.path[pathCounter] + 'A') << " ";
            }
         cout << endl;
       }
    // if the packet was unable to reach the end
    else
       {
         // output the attempted destination, that no solution was found, and the attempted path
         cout << "Attempted destination: " << char(packetRunner.dest + 'A') << endl;
         cout << "No possible solution found" << endl;
         cout << "The attempted path was: ";
         for( pathCounter = 0; pathCounter < packetRunner.path.size(); pathCounter++)
            {
             cout << char(packetRunner.path[pathCounter] + 'A') << " ";
            }
         cout << endl;
       }

    return 0;
   }

// FUNCTION IMPLEMENTATIONS ////////////////////////////////////

void sizeMatrix( vector< vector<Edge> > &linkMatrix, int numEndHosts )
   {
     int rowIndex, columnIndex, resizeIndex;

     // resize the vector row
     linkMatrix.resize( numEndHosts );

     // resizes the vector columns
     for( resizeIndex = 0; resizeIndex < numEndHosts; resizeIndex++ )
        {
          linkMatrix[resizeIndex].resize( numEndHosts );
        }

     // initializes all indeces to -1 to show that they haven't been set
     for( rowIndex = 0; rowIndex < numEndHosts; rowIndex++ )
        {
          for( columnIndex = 0; columnIndex < numEndHosts; columnIndex++ )
             {
               linkMatrix[rowIndex][columnIndex].setLinkId( -1 );
             }
        }
   }

void generateGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts, int linkAmount  )
   {
     int rowIndex, columnIndex, value;

     // iterates through the graph index by index
     for( rowIndex = 0; rowIndex < numEndHosts; rowIndex++ )
        {
          for( columnIndex = 0; columnIndex < numEndHosts; columnIndex++ )
             {
               if( rowIndex == columnIndex )
                  {
                    value = 0; // end host cannot be connected to itself
                  }
               else
                  {
                    value = rand() % 2; // generates 0 or 1 / connected or not connected
                  }

               // if the current link hasn't already been set
               if( linkMatrix[rowIndex][columnIndex].getLinkId() == -1 )
                  {
                    // set the link to the randomly generated value
                    linkMatrix[rowIndex][columnIndex].setLinkId( value );

                    // if the reversed index hasn't been set, set it so that they match
                       // for example, if A -> B is 1, B -> A should also be 1
                    if( linkMatrix[columnIndex][rowIndex].getLinkId() == -1 )
                       {
                         linkMatrix[columnIndex][rowIndex].setLinkId( value );
                       }
                  }
             }
        }
   }

void breakGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts )
   {
     float percentBroken = -1;
     int brokenLinks = 0;
     int brokenCounter = 0, breakRow = 0, breakCol = 0;

     // asks user for the percentage of links to break
     while( percentBroken < 0 || percentBroken > 100 )
        {
          cout << "Please input desired percentage of broken links (min 0, max 100): ";
          cin >> percentBroken;
        }

     // calculates the number of broken links based on user input percentage
     percentBroken /= 100;
     brokenLinks = ((((numEndHosts *numEndHosts) - numEndHosts)/2)* percentBroken);

     // iterates until the proper amount of links has been broken
     while( brokenCounter < brokenLinks )
        {
          // while the numbers that are generated are going to break either
             // a host's connection to itself (doesn't exist)
             // an already broken link
          while( breakRow == breakCol || linkMatrix[breakRow][breakCol].getState() == true  )
             {
               // randomly generate a row index and column index to break in the graph
               breakRow = rand() % numEndHosts;
               breakCol = rand() % numEndHosts;
             }

          // set the link state to broken at the generated indeces
          linkMatrix[breakRow][breakCol].setState( true ); // true = broken
          linkMatrix[breakCol][breakRow].setState( true );
          brokenCounter++;
        }
   }

void output( vector< vector<Edge> > &linkMatrix, int numEndHosts )
   {
     int rowIndex, columnIndex, counter;
     bool state;

    // output for row indicators of matrix
    cout << endl << "N = Not Broken Link, B = BROKEN Link" << endl << endl << "   |";
    for( counter = 0; counter < numEndHosts; counter++ )
       {
        cout << "  " << char(counter + 'A') << "  |";
       }

     cout << endl << "----";
     for( counter = 0; counter < numEndHosts; counter++ )
        {
         cout << "------";
        }
     cout << endl;

     // output values (ID AND STATE)
     for( rowIndex = 0; rowIndex < numEndHosts; rowIndex++ )
        {
          cout << " " << char(rowIndex + 'A') << " | ";

          for( columnIndex = 0; columnIndex < numEndHosts; columnIndex++ )
             {
               cout << linkMatrix[rowIndex][columnIndex].getLinkId();
               state = linkMatrix[rowIndex][columnIndex].getState();

               if( state == false )
                  {
                    cout << " N | ";
                  }
               else
                  {
                    cout << " B | ";
                  }
             }

          // OUTPUT DESIGN - LINE UNDER EACH ROW
          cout << endl << "----";
          for( counter = 0; counter < numEndHosts; counter++ )
             {
              cout << "------";
             }
          cout << endl;
        }
   }

bool simulate( Packet &packetRunner, vector< vector<Edge> > &linkMatrix, int numEndHosts )
   {
     int rowIndex = 0, columnIndex = 0;
     bool continueSearch = true;
     int searchCounter = 0;

     // set packet runner destination to last possible end host
     packetRunner.dest = numEndHosts - 1;

     // keep searching until the packet has arrived at dest or all end hosts have been searched
     while( continueSearch && searchCounter < numEndHosts )
        {
          // set search to false to continue loop if necessary
          continueSearch = false;

          // add current end host to path vector
          packetRunner.path.push_back( rowIndex );

          // if the current end host is connected to the destination end host
          if( linkMatrix[rowIndex][packetRunner.dest].getLinkId() == 1
              && linkMatrix[rowIndex][packetRunner.dest].getState() == false )
             {
               // set location as visited and update packetRunner info
               linkMatrix[rowIndex][packetRunner.dest].setVisited();
               linkMatrix[packetRunner.dest][rowIndex].setVisited();
               packetRunner.path.push_back( packetRunner.dest );
               packetRunner.hops++;
               packetRunner.arrived = true;

               // no longer continue search - return true and end function
               continueSearch = false;
               return true;
             }
          else
             {
               // search through the row until a connection is found
               while( linkMatrix[rowIndex][columnIndex].getLinkId() != 1
                      || linkMatrix[rowIndex][columnIndex].getState() == true
                      || linkMatrix[columnIndex][rowIndex].getVisited() == true )
                  {
                   columnIndex++;

                   if( columnIndex > numEndHosts )
                      {
                        return false; // did not find a solution
                      }
                  }

               // set current and future index as visited so that they don't check again
               linkMatrix[rowIndex][columnIndex].setVisited();
               linkMatrix[columnIndex][rowIndex].setVisited();

               // set row index to the future row to search
               rowIndex = columnIndex;
               columnIndex = 0;

               // increment hops packet has taken and continue the search for dest
               continueSearch = true;
               packetRunner.hops++;
             }

          searchCounter++; // increment search counter
        }

     return false; // did not find a solution
   }
