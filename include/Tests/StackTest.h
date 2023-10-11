/**
 * @file StackTest.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Stack.h"

#include <gtest/gtest.h>
#include <stack>

using swarnendu::Stack;

class StackTest : public ::testing::Test
{
    public:
        void testElementsInStack(std::stack<int>& refStack, Stack<int>& stack)
        {
            if(refStack.empty())
                return;

            ASSERT_FALSE(stack.empty());
            ASSERT_EQ(refStack.size(), stack.size());
            while (!refStack.empty())
            {
                EXPECT_EQ(refStack.top(), stack.top());
                refStack.pop();
                stack.pop();
            }
            ASSERT_TRUE(stack.empty());
        }

    protected:
        Stack<int> m_stack;
};