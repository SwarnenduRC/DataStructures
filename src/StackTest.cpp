/**
 * @file StackTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "TestData.h"
#include "StackTest.h"
#include "Stack.h"

using swarnendu::Stack;

static void testCopyOperator(Stack<Employee>& s)
{
    s.push(Employee("Swarnendu"));
    std::cout << std::endl << "Displaying first object of the copy stack: "<< s.top() << std::endl << std::endl;
    std::cout << "Displaying copy stack below" << std::endl;
    s.display();
}
static void testMoveOperator(Stack<Employee>& s)
{
    s.push(Employee("Deepa"));
    std::cout << std::endl << std::endl << s.top() << std::endl << std::endl;
    while (!s.empty())
    {
        s.display();
        s.pop();
    }
    s.display();
}

void testStack()
{
    Stack<Employee> stack;
    stack.push(Employee("Dhruv"));
    stack.push(Employee("Aravind"));
    stack.push(Employee("Rajiv"));

    std::cout << std::endl << "Frist element in the stack: " << stack.top() << std::endl << std::endl;
    std::cout << "Displaying original stack below" << std::endl;
    stack.display();

    Stack<Employee> stackCopy;
    stackCopy = stack;
    stack.pop();
    std::cout << std::endl << "Displaying original stack after popping the first element" << std::endl;
    stack.display();
    testCopyOperator(stackCopy);
    std::cout << std::endl << "Displaying original stack below before moving it" << std::endl;
    stack.display();
    Stack<Employee> stackMove;
    stackMove = std::move(stack);
    std::cout << "\nDisplaying original stack below after moving it" << std::endl;
    stack.display();
    testMoveOperator(stackMove);
}