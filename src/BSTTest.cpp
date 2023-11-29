#include "BSTTest.h"

#include <stack>

using swarnendu_nodes::TreeNode;

IntVector BSTTest::getRandomNumbers(const int cnt, const int offset, const int range)
{
    if (offset < 0 || range < 0)
        return IntVector{};

    IntVector vec;
    for (auto idx = 0; idx < cnt; ++idx)
        vec.emplace_back(offset + (rand() % range));

    return vec;
}

//Pre order means root->left->right
IntVector BSTTest::getElementsPreOrder() const noexcept
{
    if (!m_BST.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode<int>*> nodeStack;
    auto pRootNode = m_BST.getRoot();
    nodeStack.push(pRootNode);
    while (!nodeStack.empty())
    {
        auto pCurrentNode = nodeStack.top();
        nodeStack.pop();
        if (pCurrentNode)
        {
            retVec.emplace_back(pCurrentNode->getData());
            //Now push the right node first so that it gets processed after left node
            nodeStack.push(pCurrentNode->m_pRight.get());
            //Now push the left child
            nodeStack.push(pCurrentNode->m_pLeft.get());
        }
    }
    return retVec;
}

//In order means left->root->right
IntVector BSTTest::getElementsInOrder() const noexcept
{
    if (!m_BST.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode<int>*> nodeStack;
    auto pCurrNode = m_BST.getRoot();
    while (pCurrNode || !nodeStack.empty())
    {
        //Keep going through the left sub tree 
        if (pCurrNode)
        {
            nodeStack.push(pCurrNode);  //Push the current node before moving to it's left sub tree
            pCurrNode = pCurrNode->m_pLeft.get();
            continue;
        }
        pCurrNode = nodeStack.top();    //No more left node, so process the current one i.e; root of the sub tree
        nodeStack.pop();
        retVec.emplace_back(pCurrNode->getData());
        pCurrNode = pCurrNode->m_pRight.get();  //Now move to the right sub tree of the root.
    }
    return retVec;
}

//Post order means left->right->root
IntVector BSTTest::getElementsPostOrder() const noexcept
{
    if (!m_BST.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode<int>*> nodeStack;
    auto pCurrNode = m_BST.getRoot();
    TreeNode<int>* pLastVisitedNode = nullptr;
    while (pCurrNode || !nodeStack.empty())
    {
        if (pCurrNode)
        {
            nodeStack.push(pCurrNode);      //First push the root node of the tree
            pCurrNode = pCurrNode->m_pLeft.get();   //Then keep traversing to its left sub trees till we reach the leaf node
            continue;
        }
        //Now start backtracking
        auto pProcessNode = nodeStack.top();
        if (pProcessNode->m_pRight && pProcessNode->m_pRight.get() != pLastVisitedNode) //While backtracking check if it has any right sub tree and it is not visited already
        {
            pCurrNode = pProcessNode->m_pRight.get();
            continue;
        }
        else
        {
            retVec.emplace_back(pProcessNode->getData());   //No right node or even if it has one but already visited, process it
            pLastVisitedNode = nodeStack.top(); //Mark it as last/latest visited as this node might be the right child of the next node in the stack
            nodeStack.pop();
        }
    }
    return retVec;
}

TEST_F(BSTTest, testDefaultConstructor)
{
    size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_BST.getRoot());
    ASSERT_EQ(expectedVal, m_BST.size());
    ASSERT_EQ(expectedVal, m_BST.height());

    EXPECT_EQ(true, m_BST.insert(2));
    ASSERT_NE(nullptr, m_BST.getRoot());
    EXPECT_EQ(2, m_BST.getRoot()->getData());
    EXPECT_EQ(expectedVal + 1, m_BST.size());
    EXPECT_EQ(expectedVal + 1, m_BST.height());
}

TEST_F(BSTTest, testInsertItems)
{
    constexpr size_t expectedSize = 3;
    constexpr size_t expectedHeight = 2;
    EXPECT_EQ(true, m_BST.insert(2));
    EXPECT_EQ(true, m_BST.insert(3));
    EXPECT_EQ(true, m_BST.insert(1));

    ASSERT_NE(nullptr, m_BST.getRoot());
    EXPECT_EQ(expectedSize, m_BST.size());
    EXPECT_EQ(expectedHeight, m_BST.height());

    //Test the tree by traversing in pre order
    {
        auto items = getElementsPreOrder();
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(2, items[0]);
        EXPECT_EQ(1, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing in order
    {
        auto items = getElementsInOrder();
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(1, items[0]);
        EXPECT_EQ(2, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing post order
    {
        auto items = getElementsPostOrder();
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(1, items[0]);
        EXPECT_EQ(3, items[1]);
        EXPECT_EQ(2, items[2]);
    }
}

TEST_F(BSTTest, testInsertItemsBalanced)
{
    /*
        The purpose of this test case is to insert
        items in the ranges of 1 to 9 in a balanced
        way so that it makes a balanced BST like below
                5
               / \
              3   7
             / \ / \
            2  4 6  8
           /         \
          1           9

        The pre-order traversal of this tree would
        give us an array of 5 3 2 1 4 7 6 8 9, whereas
        an in order traversal would give us 1 2 3 4 5 6 7 8 9,
        and the post order would yields 1 2 4 3 6 9 8 7 5
     */

    constexpr size_t expectedHeight = 4;
    constexpr size_t expectedSize = 9;
    IntVector treeItems = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    IntVector treeItemsPreOrder = { 5, 3, 2, 1, 4, 7, 6, 8, 9 };
    IntVector treeItemsInOrder = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    IntVector treeItemsPostOrder = { 1, 2, 4, 3, 6, 9, 8, 7, 5 };

    for (const auto item : treeItems)
        EXPECT_TRUE(m_BST.insert(item));

    EXPECT_EQ(expectedHeight, m_BST.height());
    EXPECT_EQ(expectedSize, m_BST.size());

    auto preOrderList = getElementsPreOrder();
    for (size_t idx = 0; idx < treeItemsPreOrder.size(); ++idx)
        EXPECT_EQ(treeItemsPreOrder[idx], preOrderList[idx]);

    auto inOrderList = getElementsInOrder();
    for (size_t idx = 0; idx < treeItemsInOrder.size(); ++idx)
        EXPECT_EQ(treeItemsInOrder[idx], inOrderList[idx]);

    auto postOrderList = getElementsPostOrder();
    for (size_t idx = 0; idx < treeItemsPostOrder.size(); ++idx)
        EXPECT_EQ(treeItemsPostOrder[idx], postOrderList[idx]);
}
