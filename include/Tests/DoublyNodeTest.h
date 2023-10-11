/**
 * @file DoublyNodeTest.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Nodes.h"

#include <gtest/gtest.h>

using swarnendu_nodes::DoublyNode;

class DoublyNodeTest : public ::testing::Test
{
    protected:
        DoublyNode<int> m_doublyNode;
};