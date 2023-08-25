/**
 * @file QueueTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "TestData.h"
#include "QueueTest.h"
#include "Queue.h"

using swarnendu::Queue;

static void testCopyConstructor(Queue<Employee>& q)
{
    q.push(Employee("Swarnendu"));
    std::cout << std::endl << "Displaying first object of the copy queue: "<< q.top() << std::endl << std::endl;
    std::cout << "Displaying copy queue below" << std::endl;
    q.display();
}
static void testMoveConstructor(Queue<Employee>& q)
{
    q.push(Employee("Deepa"));
    std::cout << std::endl << std::endl << q.top() << std::endl << std::endl;
    while (!q.empty())
    {
        q.display();
        q.pop();
    }
    q.display();
}

void testQueue()
{
    Queue<Employee> queue;
    queue.push(Employee("Dhruv"));
    queue.push(Employee("Aravind"));
    queue.push(Employee("Rajiv"));

    std::cout << std::endl << "Frist element in the queue: " << queue.top() << std::endl << std::endl;
    std::cout << "Displaying original queue below" << std::endl;
    queue.display();

    Queue<Employee> queueCopy = queue;
    queue.pop();
    std::cout << std::endl << "Displaying original queue below after popping the first element" << std::endl;
    queue.display();
    testCopyConstructor(queueCopy);
    std::cout << std::endl << "Displaying original queue below before moving it" << std::endl;
    queue.display();
    Queue<Employee> queueMove = std::move(queue);
    std::cout << "\nDisplaying original queue below after moving it" << std::endl;
    queue.display();
    testMoveConstructor(queueMove);
}

