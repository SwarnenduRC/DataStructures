/**
 * @file StackTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "StackTest.h"

TEST_F(StackTest, testDefaultConstructor)
{
    ASSERT_TRUE(m_stack.empty());
    size_t stackExpectedSize = 0;
    ASSERT_EQ(stackExpectedSize, m_stack.size());
}

TEST_F(StackTest, testInitializerListConstructor)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::stack<int> refStack;
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    testElementsInStack(refStack, stack);
}

TEST_F(StackTest,testCopyConstructor)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::stack<int> refStack;
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    auto stackCopy = stack;
    testElementsInStack(refStack, stack);
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    testElementsInStack(refStack, stackCopy);
}

TEST_F(StackTest,testAssignment)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::stack<int> refStack;
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    m_stack = stack;
    testElementsInStack(refStack, stack);
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    testElementsInStack(refStack, m_stack);
}

TEST_F(StackTest,testMove)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    auto stackMove = std::move(stack);
    ASSERT_TRUE(stack.empty());
    size_t stackExpectedSize = 0;
    ASSERT_EQ(stackExpectedSize, stack.size());

    std::stack<int> refStack;
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    testElementsInStack(refStack, stackMove);
}

TEST_F(StackTest,testMoveAssignment)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    
    m_stack = std::move(stack);
    ASSERT_TRUE(stack.empty());
    size_t stackExpectedSize = 0;
    ASSERT_EQ(stackExpectedSize, stack.size());

    std::stack<int> refStack;
    for (auto val = 10; val >= 1; --val)
        refStack.push(val);

    testElementsInStack(refStack, m_stack);
}

TEST_F(StackTest, testSwap)
{
    Stack<int> stack1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::stack<int> refStack1;
    for (auto val = 10; val >= 1; --val)
        refStack1.push(val);

    Stack<int> stack2 = { 15, 14, 13, 12, 11 };
    std::stack<int> refStack2;
    for (auto val = 15; val >= 11; --val)
        refStack2.push(val);

    stack2.swap(stack1);
    testElementsInStack(refStack1, stack2);
    testElementsInStack(refStack2, stack1);
}

TEST_F(StackTest, testFind)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    EXPECT_TRUE(stack.find(1));
    stack.pop();
    EXPECT_FALSE(stack.find(1));
}

TEST_F(StackTest, testClear)
{
    Stack<int> stack = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    ASSERT_FALSE(stack.empty());
    size_t stackExpectedSize = 10;
    ASSERT_EQ(stackExpectedSize, stack.size());
    stack.clear();
    ASSERT_TRUE(stack.empty());
    stackExpectedSize = 0;
    ASSERT_EQ(stackExpectedSize, stack.size());
}

/**
 * The push, pop and top functions are already
 * been tested in initializer list constructor
 * test and in testElementsInStack function so
 * not testing them explicitly anymore here.
 */
