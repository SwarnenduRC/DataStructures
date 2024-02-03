#include "AvlTreeNodeTest.h"

TEST_F(AvlTreeNodeTest, testDefaultConstructor)
{
    ASSERT_EQ(0, m_treeNode.m_data);
    auto expectedBalFact = 0;
    auto expectedHeight = 0;

    ASSERT_EQ(expectedBalFact, m_treeNode.getBalanceFactor());
    ASSERT_EQ(expectedHeight, m_treeNode.getNodeHeight());
    ASSERT_EQ(nullptr, m_treeNode.m_pLeft);
    ASSERT_EQ(nullptr, m_treeNode.m_pRight);
}

TEST_F(AvlTreeNodeTest, testParameterizedConstructor)
{
    AVL_TreeNode<int> treeNode(55);
    ASSERT_EQ(55, treeNode.m_data);
    auto expectedHeight = 1;
    auto expectedBalFact = 0;

    ASSERT_EQ(expectedBalFact, treeNode.getBalanceFactor());
    ASSERT_EQ(expectedHeight, treeNode.getNodeHeight());
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}

TEST_F(AvlTreeNodeTest, testCopyConstructor)
{
    {
        AVL_TreeNode<int> treeNode(55);
        auto expectedBalFact = 0;
        auto expectedHeight = 1;
        auto treeNodeCopy = treeNode;
        {
            ASSERT_EQ(55, treeNode.m_data);
            ASSERT_EQ(expectedBalFact, treeNode.getBalanceFactor());
            ASSERT_EQ(expectedHeight, treeNode.getNodeHeight());
            ASSERT_EQ(nullptr, treeNode.m_pLeft);
            ASSERT_EQ(nullptr, treeNode.m_pRight);
        }
        {
            ASSERT_EQ(55, treeNodeCopy.m_data);
            ASSERT_EQ(expectedBalFact, treeNode.getBalanceFactor());
            ASSERT_EQ(expectedHeight, treeNode.getNodeHeight());
            ASSERT_EQ(nullptr, treeNodeCopy.m_pLeft);
            ASSERT_EQ(nullptr, treeNodeCopy.m_pRight);
        }
    }
    {
        AVL_TreeNode<int> treeNode(55);
        treeNode.m_pRight = std::make_unique<AVL_TreeNode<int>>(56);
        treeNode.m_pLeft = std::make_unique<AVL_TreeNode<int>>(54);
        auto expectedBalFact = 0;
        auto expectedHeight = 1;

        ASSERT_EQ(55, treeNode.m_data);
        ASSERT_NE(nullptr, treeNode.m_pLeft);
        ASSERT_NE(nullptr, treeNode.m_pRight);
        
        EXPECT_EQ(56, treeNode.m_pRight->m_data);
        EXPECT_EQ(54, treeNode.m_pLeft->m_data);
        EXPECT_EQ(expectedHeight, treeNode.m_pLeft->getNodeHeight());
        EXPECT_EQ(expectedHeight, treeNode.m_pRight->getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNode.m_pLeft->getBalanceFactor());
        EXPECT_EQ(expectedBalFact, treeNode.m_pRight->getBalanceFactor());

        treeNode.calculateHeight();
        treeNode.calculateBalanceFactor();
        expectedHeight = 2;

        EXPECT_EQ(expectedHeight, treeNode.getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNode.getBalanceFactor());
        ASSERT_EQ((expectedHeight - 1), treeNode.m_pLeft->getNodeHeight());
        ASSERT_EQ((expectedHeight - 1), treeNode.m_pRight->getNodeHeight());
        ASSERT_EQ(expectedBalFact, treeNode.m_pLeft->getBalanceFactor());
        ASSERT_EQ(expectedBalFact, treeNode.m_pRight->getBalanceFactor());
        {
            auto treeNodeCopy = treeNode;
            ASSERT_EQ(55, treeNodeCopy.m_data);
            ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
            ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
            EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
            EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
            EXPECT_EQ(expectedHeight, treeNodeCopy.getNodeHeight());
            EXPECT_EQ(expectedBalFact, treeNodeCopy.getBalanceFactor());
            ASSERT_EQ((expectedHeight - 1), treeNodeCopy.m_pLeft->getNodeHeight());
            ASSERT_EQ((expectedHeight - 1), treeNodeCopy.m_pRight->getNodeHeight());
            ASSERT_EQ(expectedBalFact, treeNodeCopy.m_pLeft->getBalanceFactor());
            ASSERT_EQ(expectedBalFact, treeNodeCopy.m_pRight->getBalanceFactor());
        }
    }
}

TEST_F(AvlTreeNodeTest, testMoveConstructor)
{
    AVL_TreeNode<int> treeNode(55);
    treeNode.m_pRight = std::make_unique<AVL_TreeNode<int>>(56);
    treeNode.m_pLeft = std::make_unique<AVL_TreeNode<int>>(54);
    auto expectedBalFact = 0;
    auto expectedHeight = 2;
    treeNode.calculateHeight();
    treeNode.calculateBalanceFactor();
    {
        auto treeNodeCopy = std::move(treeNode);
        ASSERT_EQ(55, treeNodeCopy.m_data);
        ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
        ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
        EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
        EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
        EXPECT_EQ(expectedHeight, treeNodeCopy.getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNodeCopy.getBalanceFactor());
    }
    ASSERT_EQ(55, treeNode.m_data);
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}

TEST_F(AvlTreeNodeTest, testMoveAssignment)
{
    AVL_TreeNode<int> treeNode(55);
    treeNode.m_pRight = std::make_unique<AVL_TreeNode<int>>(56);
    treeNode.m_pLeft = std::make_unique<AVL_TreeNode<int>>(54);
    treeNode.calculateHeight();
    treeNode.calculateBalanceFactor();
    auto expectedBalFact = 0;
    auto expectedHeight = 2;
    {
        AVL_TreeNode<int> treeNodeCopy;
        treeNodeCopy = std::move(treeNode);
        ASSERT_EQ(55, treeNodeCopy.m_data);
        ASSERT_NE(nullptr, treeNodeCopy.m_pLeft);
        ASSERT_NE(nullptr, treeNodeCopy.m_pRight);
        EXPECT_EQ(56, treeNodeCopy.m_pRight->m_data);
        EXPECT_EQ(54, treeNodeCopy.m_pLeft->m_data);
        EXPECT_EQ(expectedHeight, treeNodeCopy.getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNodeCopy.getBalanceFactor());
        EXPECT_EQ((expectedHeight - 1), treeNodeCopy.m_pLeft->getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNodeCopy.m_pLeft->getBalanceFactor());
        EXPECT_EQ((expectedHeight - 1), treeNodeCopy.m_pRight->getNodeHeight());
        EXPECT_EQ(expectedBalFact, treeNodeCopy.m_pRight->getBalanceFactor());
    }
    ASSERT_EQ(55, treeNode.m_data);
    ASSERT_EQ(nullptr, treeNode.m_pLeft);
    ASSERT_EQ(nullptr, treeNode.m_pRight);
}

TEST_F(AvlTreeNodeTest, testUpdateBalanceFactor)
{
    AVL_TreeNode<int> treeNode(55);
    treeNode.m_pRight = std::make_unique<AVL_TreeNode<int>>(56);
    treeNode.m_pLeft = std::make_unique<AVL_TreeNode<int>>(54);
    treeNode.calculateHeight();
    treeNode.calculateBalanceFactor();
    auto expectedBalFact = 0;
    auto expectedHeight = 2;
    EXPECT_EQ(expectedBalFact, treeNode.getBalanceFactor());
    EXPECT_EQ(expectedHeight, treeNode.getNodeHeight());
    treeNode.m_pLeft->m_pLeft = std::make_unique<AVL_TreeNode<int>>(53);
    treeNode.m_pLeft->m_pLeft->calculateHeight();
    treeNode.m_pLeft->m_pLeft->calculateBalanceFactor();
    {
        auto expectedBalFact = 0;
        auto expectedHeight = 1;
        EXPECT_EQ(expectedBalFact, treeNode.m_pLeft->m_pLeft->getBalanceFactor());
        EXPECT_EQ(expectedHeight, treeNode.m_pLeft->m_pLeft->getNodeHeight());
    }
    treeNode.m_pLeft->updateHeight();
    treeNode.m_pLeft->updateBalanceFactor();
    {
        auto expectedBalFact = 1;
        auto expectedHeight = 2;
        EXPECT_EQ(expectedBalFact, treeNode.m_pLeft->getBalanceFactor());
        EXPECT_EQ(expectedHeight, treeNode.m_pLeft->getNodeHeight());
    }
    {
        auto expectedBalFact = 0;
        auto expectedHeight = 1;
        EXPECT_EQ(expectedBalFact, treeNode.m_pRight->getBalanceFactor());
        EXPECT_EQ(expectedHeight, treeNode.m_pRight->getNodeHeight());
    }
    treeNode.updateHeight();
    treeNode.updateBalanceFactor();
    {
        auto expectedBalFact = 1;
        auto expectedHeight = 3;
        EXPECT_EQ(expectedBalFact, treeNode.getBalanceFactor());
        EXPECT_EQ(expectedHeight, treeNode.getNodeHeight());
    }
}
