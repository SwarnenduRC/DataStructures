
#include "QueueTest.h"
#include "Queue.h"

using swarnendu::Queue;

static void testCopyConstructor(Queue<Employee>& q)
{
    q.push(Employee("Swarnendu"));
    std::cout << std::endl << std::endl << q.top() << std::endl << std::endl;
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

    Queue<Employee> queueCopy = queue;
    std::cout << std::endl << std::endl << queue.top() << std::endl << std::endl;
    queue.display();
    queue.pop();
    queue.display();
    testCopyConstructor(queueCopy);
    queue.display();
    Queue<Employee> queueMove = std::move(queue);
    queue.display();
    testMoveConstructor(queueMove);
}

