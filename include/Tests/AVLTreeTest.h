#include "AVLTree.h"

#include <gtest/gtest.h>

using swarnendu_nodes::AVL_TreeNode;
using swarnendu::AVLTree;

class AVLTreeTest : public ::testing::Test
{
    protected:
        AVLTree<int> m_tree;
};