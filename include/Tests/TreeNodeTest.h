/**
 * @file TreeNodeTest.h
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

using swarnendu_nodes::TreeNode;

class TreeNodeTest : public ::testing::Test
{
    protected:
        TreeNode<int> m_treeNode;
};