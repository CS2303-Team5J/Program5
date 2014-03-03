EIN-JRW-Program5 Readme

NOTES:
------
This program should run correctly. There are no major issues in the code. 

HOW TO COMPILE/RUN:
------
Expand the tar file into a empty directory.
Type 'make (return)'
to run type './prog5 S R M D <inputfile (return)'
where:
	S is the number of sources
	R is the number of receivers
	M is the number of mules
	D indicates the length of one side of the field
	inputfile is the file containing the source node data

HOW IT WORKS:
------
The program begins by getting input from the command line telling it the number of sources, receivers, mules, and field length.
It intitalizes the simtime( to zero), the eventlist, the vector "network" (to store router ids), and the 3 grids for the routers, the revievers, and hosts.
The program then randomly generates all the hosts' locations, and adds them to the network vector and the host grid. It then randomly generates all the mules' locations, and adds them to the routerGrid and the network vector. It then generates all of the recievers' locations, and adds them to the router and receiver grids, and adds them to the network.
The program then reads in all of the node information from the input file specified in the command line, stores that information in temporary variables, and passes that information to a new packet, which is then sent to the proper host. This process is looped until all the packets have been read in and sent to the proper host.
The program then begins the simulation. Each object in the network vector, which is every host/router/reciever, has its cycle method called with the current sim time, which causes it to simulate that objects actions for that simtime.
When the global event list is empty, representing that no more actions need to be simulated, the program ends the simulation section, and prints out the results. These results are the total simtime in seconds, the max queue size, and the average packet response time. The program then terminates.