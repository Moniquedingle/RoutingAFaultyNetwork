## This is for use at the University of Nevada, Reno CPE 400 Network class
This is a simulation on routing through a faulty network.

## Routing Through A Faulty Network

### Dependencies
All code was tested using Ubuntu 14.04. The following applications must be
installed on the machine:

- gcc/g++ compiler:
  - $ sudo apt-get install g++

### Compilation
A makefile is used to compile the program.
- cd RoutingAFaultyNetwork
- make
- ./simulation

### Versions
- Version 1.0: The simulation algorithm finds the first possible route by
starting at 'A' and finding its way to the destination end host.
- Version 2.0: The simulation algorithm finds the first possible route by
starting at the destination end host and making its way through the
source end host.
