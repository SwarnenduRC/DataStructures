#include "AVLTreeTest.h"

#include <map>

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

TEST_F(AVLTreeTest, testInsertWithSelfBalancing)
{
    size_t expectedSize = 0;
    ASSERT_EQ(expectedSize, m_tree.size());
    ASSERT_TRUE(m_tree.empty());
    
    /**
     *              106
     *             /
     *           105
     *           /
     *         103
     * 
     * The above would be the tree (left scewed) if we insert
     * elements in order 106, 105 & 103. But if AVL tree property
     * is applied then it will be a perfect BST like below
     *              105
     *             /   \
     *           103   106
     */
    m_tree.insert(106);
    expectedSize = 1;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());

    m_tree.insert(105);
    expectedSize = 2;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());

    m_tree.insert(103);
    expectedSize = 3;
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_FALSE(m_tree.empty());

    ASSERT_NE(nullptr, m_tree.getRootNode()->m_pRight);
    EXPECT_EQ(106, m_tree.getRootNode()->m_pRight->getData());
    EXPECT_EQ(103, m_tree.getRootNode()->m_pLeft->getData());
    EXPECT_EQ(105, m_tree.getRootNode()->getData());

    auto expBalFact = 0;
    auto expHeight = 2;
    EXPECT_EQ(expBalFact, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    EXPECT_EQ(expHeight, m_tree.getTreeHeight());
    EXPECT_NO_THROW(m_tree.checkBalanceFactor(m_tree.getRootNode()));
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

TEST_F(AVLTreeTest, testInitializerListConstructor)
{
    AVLTree<int> tree = { 798, 1078, 412, 548, 1025, 895 };
    size_t expectedSize = 6;
    EXPECT_EQ(expectedSize, tree.size());
    EXPECT_NO_THROW(tree.checkBalanceFactor(tree.getRootNode()));
    {
        EXPECT_TRUE(tree.find(412));
        tree.erase(412);
        --expectedSize;
        EXPECT_FALSE(tree.find(412));
        EXPECT_EQ(expectedSize, tree.size());
        EXPECT_NO_THROW(tree.checkBalanceFactor(tree.getRootNode()));
    }
    {
        auto valToErase = tree.getRootNode()->getData();
        EXPECT_TRUE(tree.find(valToErase));
        tree.erase(valToErase);
        --expectedSize;
        EXPECT_FALSE(tree.find(valToErase));
        EXPECT_EQ(expectedSize, tree.size());
        EXPECT_NO_THROW(tree.checkBalanceFactor(tree.getRootNode()));
    }
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
        m_tree.applyLeftRotation(m_tree.getRootNode(), false);
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
        m_tree.applyRightRotation(m_tree.getRootNode(), false);
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
        m_tree.applyRightRotation(m_tree.getRootNode(), false);
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
        m_tree.applyLeftRotation(m_tree.getRootNode(), false);
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

TEST_F(AVLTreeTest, testRotationsWithSelfBalancing)
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
     * Now if we apply rotations (left or right) on the root of this tree
     * with self balancing flag enabled then no matter how many rotations
     * we apply the tree will be same as shown above. So lets check that out.
     */
    {
        m_tree.applyLeftRotation(m_tree.getRootNode(), true);
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
        EXPECT_FALSE(m_tree.empty());
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    }
    {
        m_tree.applyRightRotation(m_tree.getRootNode(), true);
        EXPECT_EQ(expectedSize, m_tree.size());
        EXPECT_EQ(expectedHeight, m_tree.getRootNode()->getNodeHeight());
        EXPECT_FALSE(m_tree.empty());
        EXPECT_EQ(balanceFactor, m_tree.getNodeBalanceFactor(m_tree.getRootNode()));
    }
}

TEST_F(AVLTreeTest, testIterators)
{
    std::initializer_list<int> list = { 15, 22, 25, 28, 806 };
    std::map<int, std::string> testMap = { {25, "25"}, {28, "28"}, {22, "22"}, {806, "806"}, {15, "15"} };
    {
        auto itr = testMap.begin();
        for (const auto& val : list)
        {
            EXPECT_EQ(val, itr->first);
            ++itr;
        }
    }
    {
        std::initializer_list<int> list = { 806, 28, 25, 22, 15 };
        auto itr = testMap.rbegin();
        for (const auto& val : list)
        {
            EXPECT_EQ(val, itr->first);
            ++itr;
        }
    }
}
