#include "graph.h"
#include <iostream>
#include <cstdlib>
#include <vector>

// FUNCTION PROTOTYPES ////////////////////////////////////
void generateGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts, int linkAmount);

void breakGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts );

void output( vector< vector<Edge> > &linkMatrix, int numEndHosts );

int Dijkstras( Packet packetRunner );

bool simulate( Packet packetRunner );


// MAIN PROGRAM ////////////////////////////////////////////
int main()
   {
     // vector of identical packets
      // all packets will go to the same destination and their numHops will be compared at the end
     vector<Packet> packets;
     vector< vector<Edge> > linkMatrix;
     int numEndHosts = -1;
     int linkAmount = 0;
     int rowIndex, columnIndex, resizeIndex;

     // ask user for data
      // how many end hosts (max 50)
      // how many links per end host (max 3)
      while( numEndHosts < 0 || numEndHosts > 20 )
         {
           cout << "Please input the number of desired routers (max 20): ";
           cin >> numEndHosts;
         }

      while( linkAmount < 2 || linkAmount > 5)
         {
           cout << "Please input the max amount of links a route can have (2 <= links <= 5): ";
           cin >> linkAmount;
         }


      // size link matrix to accomodate numEndHosts
      linkMatrix.resize( numEndHosts );

      for( resizeIndex = 0; resizeIndex < numEndHosts; resizeIndex++ )
         {
           linkMatrix[resizeIndex].resize( numEndHosts );
         }

      for( rowIndex = 0; rowIndex < numEndHosts; rowIndex++ )
         {
           for( columnIndex = 0; columnIndex < numEndHosts; columnIndex++ )
              {
                // initialize all values to -1 for checking purposes in generateGraph
                linkMatrix[rowIndex][columnIndex].setLinkId( -1 );
              }
         }

    // randomly generate graph based on user info with some broken links
    generateGraph( linkMatrix, numEndHosts, linkAmount );

    // randomly breaks links
    breakGraph( linkMatrix, numEndHosts );

    output( linkMatrix, numEndHosts );

    // packet always starts route at end host ID 1 and ends at the last end host ID

    return 0;
   }

// FUNCTION IMPLEMENTATIONS ////////////////////////////////////
void generateGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts, int linkAmount  )
   {
     int rowIndex, columnIndex, value;
     int counter = 0;

     for( rowIndex = 0; rowIndex < numEndHosts; rowIndex++ )
        {
          for( columnIndex = 0; columnIndex < numEndHosts; columnIndex++ )
             {
               if( rowIndex == columnIndex )
                  {
                    value = 0; // if host is itself = 0
                  }
               else
                  {
                    value = rand() % 2; // generates 0 or 1
                  }

               if( linkMatrix[rowIndex][columnIndex].getLinkId() == -1 )
                  {
                    linkMatrix[rowIndex][columnIndex].setLinkId( value );

                    if( linkMatrix[columnIndex][rowIndex].getLinkId() == -1 )
                       {
                         linkMatrix[columnIndex][rowIndex].setLinkId( value );
                       }
                  }
             }
        }
        counter ++;
   }

void breakGraph( vector< vector<Edge> > &linkMatrix, int numEndHosts )
   {
     float percentBroken = -1;
     int brokenLinks = 0;
     int brokenCounter = 0, breakRow = 0, breakCol = 0;

     // iterates through matrix and sets random states to true (broken/faulty)
     while( percentBroken < 0 || percentBroken > 100 )
        {
          cout << "Please input desired percentage of broken links (min 0, max 100): ";
          cin >> percentBroken;
        }

     percentBroken /= 100;
     brokenLinks = ((((numEndHosts *numEndHosts) - numEndHosts)/2)* percentBroken);
     while( brokenCounter < brokenLinks )
        {
          while( breakRow == breakCol || linkMatrix[breakRow][breakCol].getState() == true  )
             {
               breakRow = rand() % numEndHosts;
               breakCol = rand() % numEndHosts;
             }

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

// Dijkstras
  // searches through the packet vector and compares int hops
  // returns the index of the packet that had the least amount of hops
int Dijkstras( Packet packetRunner )
   {

     return 0; // stub
   }

bool simulate( Packet packetRunner )
   {
    // uses Dijkstras

    // for loop that iterates through all of the packets
     // checks that at least one packet arrived - return true
     // if zero packets arrived - return false and error message
     // uses the "arrived" variable in the packet struct

     return true; // stub
   }
