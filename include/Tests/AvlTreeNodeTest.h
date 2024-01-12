#include "Nodes.h"

#include <gtest/gtest.h>

using swarnendu_nodes::AVL_TreeNode;

class AvlTreeNodeTest : public ::testing::Test
{
    protected:
        AVL_TreeNode<int> m_treeNode;
};