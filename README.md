# DataStructures
 Simple Data Structures like Linked List, Stack, Queues, Tree etc
## Description
It is a repo of various simple data structures in modern C++-17 like
Singly Linked List, Doubly Linked List, Queue, Stack, Dynamic Array etc.
The data structures Stack and Queue are built upon the Doubly Linked list
itslef and using all its methods under the top level wrappers. The program
has been tested for memory leaks using `leaks` on MacOS and none found.
If you can spot anything then kindly either resolve it or can let me know
## Build
To build the application simply make which will build two
binaries under the bin folder for Debug & Release. To clean 
it run `make clean`. To build only debug/release run `make debug` 
or `make release`. Also keep in mind that as all the data 
structures are templated ones and thus headers only so if you make 
any changes on any of the header file you need to run a clean build 
for the changes to take effect.
