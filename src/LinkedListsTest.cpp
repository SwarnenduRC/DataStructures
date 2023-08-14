#include <iostream>
#include <string>
#include <thread>

#include "SinglyLinkedList.h"
#include "LinkedListsTest.h"

using swarnendu::SinglyLinkedList;
using swarnendu_nodes::DoublyNode;

void testDoublyNode()
{
    DoublyNode<Student> shamNode(Student("Sham"));
    shamNode.m_pNext = std::make_shared<DoublyNode<Student>>(Student("Yadu"));
    shamNode.m_pPrev = std::make_shared<DoublyNode<Student>>(Student("Ram"));

    {
        std::cout << std::endl << std::endl << "======Move Constructor Test======" << std::endl << std::endl;
        DoublyNode<Student> madhuNode(Student("Madhu"));
        madhuNode.m_pNext = std::move(shamNode.m_pNext);
        madhuNode.m_pPrev = std::move(shamNode.m_pPrev);
        
        std::cout << std::endl << std::endl << "Student's name = " << madhuNode.getData().getName() << std::endl << std::endl;
        std::cout << std::endl << std::endl << "Student's name = " << madhuNode.m_pNext->getData().getName() << std::endl << std::endl;
        std::cout << std::endl << std::endl << "Student's name = " << madhuNode.m_pPrev->getData().getName() << std::endl << std::endl;

        std::cout << std::endl << std::endl << "======Move Constructor Test======" << std::endl << std::endl;
    }
    std::cout << std::endl << std::endl << "Student's name = " << shamNode.getData().getName() << std::endl << std::endl;
    if (shamNode.m_pNext)
        std::cout << std::endl << std::endl << "Student's name = " << shamNode.m_pNext->getData().getName() << std::endl << std::endl;
    if (shamNode.m_pPrev)
    std::cout << std::endl << std::endl << "Student's name = " << shamNode.m_pPrev->getData().getName() << std::endl << std::endl;
}

static void initiateList(int argc, char** argv, SinglyLinkedList& list)
{
    list.insertAtFront(5);
    list.insertAtFront(2);
    list.insertAtFront(1);    
    list.insertAtBack(8);
    list.insertAtBack(13);
    list.displayList();

    std::cout << "Inserting 3 at the middle of the linked list" << std::endl;
    list.insertAtMiddle(3);
    list.displayList();
    std::cout << std::endl << "The list contains " << list.size() << " elements" << std::endl << std::endl;

    if (argc >= 3)
    {
        std::cout << "Inserting " << std::stoi(argv[2]) << " at the postion " <<  std::stoi(argv[1]) << " of the linked list" << std::endl;
        list.insertAtPos(std::stoi(argv[1]), std::stoi(argv[2]));
        list.displayList();
        std::cout << "The list contains " << list.size() << " elements" << std::endl;
    }
}

static void testMethods(SinglyLinkedList& list)
{
    std::cout << "Deleting node from the middle of the linked list" << std::endl;
    list.deleteAtMiddle();
    list.displayList();
    std::cout << std::endl << "The list contains " << list.size() << " elements" << std::endl;

    std::cout << std::endl << "Deleting node at the front of the linked list" << std::endl;
    list.deleteAtFront();
    list.displayList();
    std::cout << std::endl << "The list contains " << list.size() << " elements" << std::endl;

    std::cout << "Deleting node at the back of the linked list" << std::endl;
    list.deleteAtBack();
    list.displayList();
    std::cout << "The list contains " << list.size() << " elements" << std::endl;

    std::cout << std::endl << "Deleting node at the pos 3 of the linked list" << std::endl;
    list.deleteAtPos(3);
    list.displayList();
    std::cout << "The list contains " << list.size() << " elements" << std::endl;
    
    std::cout << "Clearing the list now" << std::endl;
    list.clearList();
    std::cout << "The list contains " << list.size() << " elements" << std::endl;
    list.displayList();

    std::cout << std::endl << std::endl;
}

static void testCopyConstructor(const SinglyLinkedList& list)
{
    std::cout << "===========Copy construtor testing started=======" << std::endl << std::endl;
    SinglyLinkedList listCopy = list;
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    std::cout << "===========Copy construtor testing ended=========" << std::endl << std::endl;
}
static void testAssignmentOperator(int argc, char** argv, const SinglyLinkedList& list)
{
    std::cout << "===========Assignment operator testing started=======" << std::endl << std::endl;
    SinglyLinkedList listCopy;
    listCopy = list;
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    initiateList(argc, argv, listCopy);
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    std::cout << "===========Assignment operator testing ended=========" << std::endl << std::endl;
}

static void testMoveConstructor(SinglyLinkedList& list)
{
    std::cout << "===========Move construtor testing started=======" << std::endl << std::endl;
    SinglyLinkedList listCopy = std::move(list);
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    std::cout << "===========Move construtor testing ended=========" << std::endl << std::endl;
}

static void testMoveAssignmentOperator(int argc, char** argv, SinglyLinkedList& list)
{
    std::cout << "=========== Move assignment operator testing started=======" << std::endl << std::endl;
    SinglyLinkedList listCopy;
    listCopy = std::move(list);
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    initiateList(argc, argv, listCopy);
    listCopy.displayList();
    std::cout << std::endl << "The list contains " << listCopy.size() << " elements" << std::endl << std::endl;
    testMethods(listCopy);
    std::cout << "===========Move assignment operator testing ended=========" << std::endl << std::endl;
}

void testSinglyLinkedList(int argc, char** argv)
{
    SinglyLinkedList list;
    initiateList(argc, argv, list);
    std::cout << std::endl << std::endl;
    testCopyConstructor(list);
    testAssignmentOperator(argc, argv, list);
    testMoveConstructor(list);
    testMoveAssignmentOperator(argc, argv, list);
    testMethods(list);
}