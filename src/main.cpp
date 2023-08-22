#include <iostream>
#include <string>
#include <thread>
#include <exception>

#include "LinkedListsTest.h"
#include "DoublyLinkedListTest.h"
#include "QueueTest.h"

int main (int argc, char** argv)
{    
    if (argc < 1)
    {
        std::cerr << "Invalid program" << std::endl << std::endl;
        return -1;
    }
    
    auto programName = argv[0];
    std::cout << std::endl << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "         " << programName << " Program Started       " << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << std::endl << std::endl;

    try
    {
        //testSinglyLinkedList(argc, argv);
        //testDoublyNode();
        //testDoublyLinkedList();
        testQueue();
    }
    catch(const std::exception& e)
    {
        std::cout << std::endl << "Standard exception received: " << e.what() << std::endl;
    }

    std::cout << std::endl << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "         " << programName << " Program ended         " << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << std::endl << std::endl;

    //auto threadId = std::this_thread::get_id();

    return 0;
}