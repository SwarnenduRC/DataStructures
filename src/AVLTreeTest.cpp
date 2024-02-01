#include "AVLTreeTest.h"

TEST_F(AVLTreeTest, testDefaultConstructor)
{
    size_t expectedSize = 0;
    ASSERT_EQ(expectedSize, m_tree.size());
    ASSERT_TRUE(m_tree.empty());
}

TEST_F(AVLTreeTest, testInsert)
{
    size_t expectedSize = 0;
    ASSERT_EQ(expectedSize, m_tree.size());
    ASSERT_TRUE(m_tree.empty());
    
    m_tree.insert(105);
    expectedSize = 1;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());

    m_tree.insert(103);
    expectedSize = 2;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());

    m_tree.insert(106);
    expectedSize = 3;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
}

TEST_F(AVLTreeTest, testErase)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);
    size_t expectedSize = 3;
    auto expectedNodeHeight = 2;
    auto expectedBalFact = 0;

    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
    EXPECT_TRUE(m_tree.find(103));
    EXPECT_TRUE(m_tree.find(106));
    EXPECT_TRUE(m_tree.find(105));
    EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
    EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));

    {
        m_tree.erase(105);
        expectedSize = 2;
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        EXPECT_FALSE(m_tree.find(105));
        EXPECT_TRUE(m_tree.find(103));
        EXPECT_TRUE(m_tree.find(106));

        expectedBalFact = 1;
        EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
        EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    }
    {
        m_tree.erase(106);
        expectedSize = 1;
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        EXPECT_FALSE(m_tree.find(105));
        EXPECT_TRUE(m_tree.find(103));
        EXPECT_FALSE(m_tree.find(106));

        expectedBalFact = 0;
        expectedNodeHeight = 1;
        EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
        EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    }
    {
        m_tree.erase(103);
        expectedSize = 0;
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_TRUE(m_tree.empty());
        EXPECT_FALSE(m_tree.find(105));
        EXPECT_FALSE(m_tree.find(103));
        EXPECT_FALSE(m_tree.find(106));
    }
}

TEST_F(AVLTreeTest, testFind)
{
    size_t expectedSize = 0;
    ASSERT_EQ(expectedSize, m_tree.size());
    ASSERT_TRUE(m_tree.empty());

    {
        EXPECT_FALSE(m_tree.find(105));
        m_tree.insert(105);
        EXPECT_TRUE(m_tree.find(105));
        m_tree.insert(103);
        EXPECT_TRUE(m_tree.find(103));
        m_tree.insert(106);
        EXPECT_TRUE(m_tree.find(106));
        m_tree.insert(16);
        EXPECT_TRUE(m_tree.find(16));
    }
}

TEST_F(AVLTreeTest, testClear)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);
    m_tree.insert(16);

    size_t expectedSize = 4;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
    m_tree.clear();
    expectedSize = 0;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_TRUE(m_tree.empty());
}

TEST_F(AVLTreeTest, testCopy)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);

    size_t expectedSize = 3;
    {
        auto copyTree = m_tree;
        
        EXPECT_EQ(expectedSize, copyTree.size());
        EXPECT_FALSE(copyTree.empty());
        EXPECT_TRUE(copyTree.find(103));
        EXPECT_TRUE(copyTree.find(106));
        EXPECT_TRUE(copyTree.find(105));

        auto expectedNodeHeight = 2;
        auto expectedBalFact = 0;
        EXPECT_EQ(expectedNodeHeight, copyTree.getTreeHeight());
        EXPECT_EQ(expectedBalFact, copyTree.getNodeBalanceFactor(copyTree.getRootNode()));
    }
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
    EXPECT_TRUE(m_tree.find(103));
    EXPECT_TRUE(m_tree.find(106));
    EXPECT_TRUE(m_tree.find(105));

    auto expectedNodeHeight = 2;
    auto expectedBalFact = 0;
    EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
    EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
}

TEST_F(AVLTreeTest, testMove)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);

    size_t expectedSize = 3;
    {
        auto copyTree = std::move_if_noexcept(m_tree);
        
        EXPECT_EQ(expectedSize, copyTree.size());
        EXPECT_FALSE(copyTree.empty());
        EXPECT_TRUE(copyTree.find(103));
        EXPECT_TRUE(copyTree.find(106));
        EXPECT_TRUE(copyTree.find(105));

        auto expectedNodeHeight = 2;
        auto expectedBalFact = 0;
        EXPECT_EQ(expectedNodeHeight, copyTree.getTreeHeight());
        EXPECT_EQ(expectedBalFact, copyTree.getNodeBalanceFactor(copyTree.getRootNode()));
    }
    expectedSize = 0;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_TRUE(m_tree.empty());
}

TEST_F(AVLTreeTest, testCopyAssignment)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);

    size_t expectedSize = 3;
    {
        AVLTree<int> copyTree;
        copyTree = m_tree;
        
        EXPECT_EQ(expectedSize, copyTree.size());
        EXPECT_FALSE(copyTree.empty());
        EXPECT_TRUE(copyTree.find(103));
        EXPECT_TRUE(copyTree.find(106));
        EXPECT_TRUE(copyTree.find(105));

        auto expectedNodeHeight = 2;
        auto expectedBalFact = 0;
        EXPECT_EQ(expectedNodeHeight, copyTree.getTreeHeight());
        EXPECT_EQ(expectedBalFact, copyTree.getNodeBalanceFactor(copyTree.getRootNode()));
    }
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
    EXPECT_TRUE(m_tree.find(103));
    EXPECT_TRUE(m_tree.find(106));
    EXPECT_TRUE(m_tree.find(105));

    auto expectedNodeHeight = 2;
    auto expectedBalFact = 0;
    EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
    EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
}

TEST_F(AVLTreeTest, testMoveAssignment)
{
    size_t expectedSize = 3;
    {
        AVLTree<int> copyTree;
        copyTree.insert(105);
        copyTree.insert(103);
        copyTree.insert(106);

        m_tree = std::move(copyTree);
    }
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());
    EXPECT_TRUE(m_tree.find(103));
    EXPECT_TRUE(m_tree.find(106));
    EXPECT_TRUE(m_tree.find(105));

    auto expectedNodeHeight = 2;
    auto expectedBalFact = 0;
    EXPECT_EQ(expectedNodeHeight, m_tree.getTreeHeight());
    EXPECT_EQ(expectedBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
}

TEST_F(AVLTreeTest, testRotations)
{
    m_tree.insert(105);
    m_tree.insert(103);
    m_tree.insert(106);
    /**
     *              105
     *             /   \
     *           103   106
     * 
     */
    size_t expectedSize = 3;
    auto balanceFactor = 0;
    auto expectedHeight = 2;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
    EXPECT_FALSE(m_tree.empty());
    EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    
    /**
     *              106
     *             /
     *           105
     *           /
     *         103
     */
    {
        m_tree.applyLeftRotation(m_tree.getRootNode());
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        
        EXPECT_EQ(106, m_tree.getRootNode()->getData());
        EXPECT_EQ(105, m_tree.getRootNode()->m_pLeft->getData());
        EXPECT_EQ(103, m_tree.getRootNode()->m_pLeft->m_pLeft->getData());
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pRight);
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pLeft->m_pRight);
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pLeft->m_pLeft->m_pRight);
        
        balanceFactor = 2;
        expectedHeight = 3;
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
    }
    /**
     *              105
     *             /   \
     *           103   106
     * 
     */
    {
        m_tree.applyRightRotation(m_tree.getRootNode());
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        
        EXPECT_EQ(105, m_tree.getRootNode()->getData());
        ASSERT_NE(nullptr, m_tree.getRootNode()->m_pRight);
        ASSERT_NE(nullptr, m_tree.getRootNode()->m_pLeft);
        EXPECT_EQ(106, m_tree.getRootNode()->m_pRight->getData());
        EXPECT_EQ(103, m_tree.getRootNode()->m_pLeft->getData());
        
        balanceFactor = 0;
        expectedHeight = 2;
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
    }
    /**
     *                103
     *                  \
     *                  105
     *                    \
     *                    106
     * 
     */
    {
        m_tree.applyRightRotation(m_tree.getRootNode());
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        EXPECT_EQ(103, m_tree.getRootNode()->getData());
        EXPECT_EQ(105, m_tree.getRootNode()->m_pRight->getData());
        EXPECT_EQ(106, m_tree.getRootNode()->m_pRight->m_pRight->getData());
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pLeft);
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pRight->m_pLeft);
        EXPECT_EQ(nullptr, m_tree.getRootNode()->m_pRight->m_pRight->m_pLeft);

        balanceFactor = -2;
        expectedHeight = 3;
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
    }
    /**
     *              105
     *             /   \
     *           103   106
     * 
     */
    {
        m_tree.applyLeftRotation(m_tree.getRootNode());
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_FALSE(m_tree.empty());
        
        EXPECT_EQ(105, m_tree.getRootNode()->getData());
        ASSERT_NE(nullptr, m_tree.getRootNode()->m_pRight);
        ASSERT_NE(nullptr, m_tree.getRootNode()->m_pLeft);
        EXPECT_EQ(106, m_tree.getRootNode()->m_pRight->getData());
        EXPECT_EQ(103, m_tree.getRootNode()->m_pLeft->getData());
        
        balanceFactor = 0;
        expectedHeight = 2;
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
    }
}
