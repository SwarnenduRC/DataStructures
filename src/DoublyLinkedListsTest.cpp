/**
 * @file DoublyLinkedListsTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <exception>

#include "DoublyLinkedList.h"
#include "DoublyLinkedListTest.h"

using swarnendu_nodes::DoublyNode;
using swarnendu::DoublyLinkedList;

static void displayList(const DoublyLinkedList<int>& intList)
{
    intList.display();
    intList.displayBack();
}

static void insertElements(DoublyLinkedList<int>& intList)
{
    intList.push_back(2);
    displayList(intList);
    intList.push_front(1);
    displayList(intList);
    intList.push_back(3);
    displayList(intList);
    intList.push_back(4);
    displayList(intList);
    intList.push_at(7, 3);
    displayList(intList);
}

static void insertElementsSelective(DoublyLinkedList<int>& intList)
{
    intList.push_back(12);
    displayList(intList);
    /* intList.push_at(77, 3);
    displayList(intList); */
    /* intList.push_front(1);
    displayList(intList);
    intList.push_back(3);
    displayList(intList);
    intList.push_back(4);
    displayList(intList);
    intList.push_at(7, 3);
    displayList(intList); */
}

static void deleteElements(DoublyLinkedList<int>& intList)
{
    intList.pop_front();
    displayList(intList);
    intList.pop_back();
    displayList(intList);
    intList.erase(2);
    displayList(intList);
    intList.erase(3);
    displayList(intList);
    intList.pop_back();
    displayList(intList);
    intList.clear();
}

static void deleteElementsSelective(DoublyLinkedList<int>& intList)
{
    intList.pop_front();
    displayList(intList);
    /* intList.pop_back();
    displayList(intList);
    intList.erase(2);
    displayList(intList);
    intList.erase(3);
    displayList(intList);
    intList.pop_back();
    displayList(intList); */
}

static void testCopyContructor(DoublyLinkedList<int>& intList)
{
    displayList(intList);
    //insertElements(intList);
    if (intList.find(4))
        std::cout << std::endl << std::endl << "The value " << 4 << " is in the list already" << std::endl << std::endl;
    else
        std::cout << std::endl << std::endl << "The value " << 4 << " is not in the list yet" << std::endl << std::endl;
}

static void testMoveConstructor(DoublyLinkedList<int>& intList)
{
    displayList(intList);
    insertElements(intList);
    if (intList.find(4))
        std::cout << std::endl << std::endl << "The value " << 4 << " is in the list already" << std::endl << std::endl;
    else
        std::cout << std::endl << std::endl << "The value " << 4 << " is not in the list yet" << std::endl << std::endl;

    deleteElements(intList);
}

void testDoublyLinkedList()
{
    try
    {
        DoublyLinkedList<int> intList;
        insertElements(intList);
        
        auto copyList = intList;
        deleteElements(intList);

        std::cout << std::endl << std::endl << "==============Copy Constructor Test===================" << std::endl << std::endl;
        testCopyContructor(copyList);
        std::cout << std::endl << std::endl << "==============Copy Constructor Test===================" << std::endl << std::endl;

        std::cout << std::endl << std::endl << "==============Move Constructor Test===================" << std::endl << std::endl;
        auto movedList = std::move(copyList);
        displayList(copyList);
        testMoveConstructor(movedList);
        std::cout << std::endl << std::endl << "==============Move Constructor Test===================" << std::endl << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << std::endl << std::endl << "Standard exception occurred: " << e.what() << std::endl << std::endl;
    }
}