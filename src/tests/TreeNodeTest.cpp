/**
 * @file TreeNodeTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "TreeNodeTest.h"

TEST_F(TreeNodeTest, testDefaultConstructor)
{
    ASSERT_EQ(0, m_treeNode.m_data);
    ASSERT_EQ(nullptr, m_treeNode.m_pLeft);
    ASSERT_EQ(nullptr, m_treeNode.m_pRight);
}

TEST_F(TreeNodeTest, testParameterizedConstructor)
{
    TreeNode<int> treeNode(55);
    ASSERT_EQ(55, treeNode.m_data);
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}

TEST_F(TreeNodeTest, testCopyConstructor)
{
    {
        TreeNode<int> treeNode(55);
        auto treeNodeCopy = treeNode;
        {
            ASSERT_EQ(55, treeNode.m_data);
            ASSERT_EQ(nullptr, treeNode.m_pLeft);
            ASSERT_EQ(nullptr, treeNode.m_pRight);
        }
        {
            ASSERT_EQ(55, treeNodeCopy.m_data);
            ASSERT_EQ(nullptr, treeNodeCopy.m_pLeft);
            ASSERT_EQ(nullptr, treeNodeCopy.m_pRight);
        }
    }
    {
        TreeNode<int> treeNode(55);
        treeNode.m_pRight = std::make_unique<TreeNode<int>>(56);
        treeNode.m_pLeft = std::make_unique<TreeNode<int>>(54);
        ASSERT_EQ(55, treeNode.m_data);
        ASSERT_NE(nullptr, treeNode.m_pLeft);
        ASSERT_NE(nullptr, treeNode.m_pRight);
        EXPECT_EQ(56, treeNode.m_pRight->m_data);
        EXPECT_EQ(54, treeNode.m_pLeft->m_data);
        
        {
            auto treeNodeCopy = treeNode;
            ASSERT_EQ(55, treeNodeCopy.m_data);
            ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
            ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
            EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
            EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
        }
    }
}

TEST_F(TreeNodeTest, testMoveConstructor)
{
    TreeNode<int> treeNode(55);
    treeNode.m_pRight = std::make_unique<TreeNode<int>>(56);
    treeNode.m_pLeft = std::make_unique<TreeNode<int>>(54);
    {
        auto treeNodeCopy = std::move(treeNode);
        ASSERT_EQ(55, treeNodeCopy.m_data);
        ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
        ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
        EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
        EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
    }
    ASSERT_EQ(55, treeNode.m_data);
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}

TEST_F(TreeNodeTest, testMoveAssignment)
{
    TreeNode<int> treeNode(55);
    treeNode.m_pRight = std::make_unique<TreeNode<int>>(56);
    treeNode.m_pLeft = std::make_unique<TreeNode<int>>(54);
    {
        TreeNode<int> treeNodeCopy;
        treeNodeCopy = std::move(treeNode);
        ASSERT_EQ(55, treeNodeCopy.m_data);
        ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
        ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
        EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
        EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
    }
    ASSERT_EQ(55, treeNode.m_data);
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}
