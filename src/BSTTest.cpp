#include "BSTTest.h"
#include "Queue.h"
#include "Stack.h"

using swarnendu_nodes::TreeNode;
using swarnendu::Queue;
using swarnendu::Stack;

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
IntVector BSTTest::getElementsPreOrder(const BSTree<int>& tree) const noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode<int>*> nodeStack;
    auto pRootNode = tree.getRoot();
    nodeStack.push(pRootNode);
    while (!nodeStack.empty())
    {
        auto pCurrentNode = nodeStack.top();
        nodeStack.pop();
        if (pCurrentNode)
        {
            retVec.emplace_back(pCurrentNode->getData());
            //Now push the right node first so that it gets processed after left node
            if (pCurrentNode->m_pRight)
                nodeStack.push(pCurrentNode->m_pRight.get());
            //Now push the left child
            if (pCurrentNode->m_pLeft)
                nodeStack.push(pCurrentNode->m_pLeft.get());
        }
    }
    return retVec;
}

//In order means left->root->right
IntVector BSTTest::getElementsInOrder(const BSTree<int>& tree) const noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    Stack<TreeNode<int>*> nodeStack;
    auto pCurrNode = tree.getRoot();
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
IntVector BSTTest::getElementsPostOrder(const BSTree<int>& tree) const noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    Stack<TreeNode<int>*> nodeStack;
    auto pCurrNode = tree.getRoot();
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

void BSTTest::testBalancedBST(const BSTree<int>& tree) const noexcept
{
    /*
        The purpose of this test function is to test
        items in the ranges of 1 to 9 in a balanced
        BST like below
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
    IntVector treeItemsPreOrder = { 5, 3, 2, 1, 4, 7, 6, 8, 9 };
    IntVector treeItemsInOrder = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    IntVector treeItemsPostOrder = { 1, 2, 4, 3, 6, 9, 8, 7, 5 };

    EXPECT_EQ(expectedHeight, tree.height());
    EXPECT_EQ(expectedSize, tree.size());

    auto preOrderList = getElementsPreOrder(tree);
    for (size_t idx = 0; idx < treeItemsPreOrder.size(); ++idx)
        EXPECT_EQ(treeItemsPreOrder[idx], preOrderList[idx]);

    auto inOrderList = getElementsInOrder(tree);
    for (size_t idx = 0; idx < treeItemsInOrder.size(); ++idx)
        EXPECT_EQ(treeItemsInOrder[idx], inOrderList[idx]);

    auto postOrderList = getElementsPostOrder(tree);
    for (size_t idx = 0; idx < treeItemsPostOrder.size(); ++idx)
        EXPECT_EQ(treeItemsPostOrder[idx], postOrderList[idx]);
}

IntVector BSTTest::getLeftView(const BSTree<int>& tree) const noexcept
{
    if (tree.empty())
        return IntVector{};

    /*
        The main logic behing getting the left view of a BST is
        nothing but a level order traversal of the tree. The initial
        level starts at 0 and we increment this for both it's left
        and right subtrees. During the recursion (here backtracking)
        we check whether the child node in consideration is at the same
        level or at higher level. If it is at higher level than the
        last visited level we take it in otherwise we just go for it's
        children down the line further.
    */
    Queue<std::pair<TreeNode<int>*, int>> nodeQueue = { std::make_pair(tree.getRoot(), 0) };
    auto currentLevel = -1; //As we start from level 0 for the root node
    IntVector retVec;
    while (!nodeQueue.empty())
    {
        auto level = nodeQueue.front().second;
        auto pNode = nodeQueue.front().first;
        if (level > currentLevel)   //Is the level of the node in consideration is greater than the current level
        {
            currentLevel = level;   //Update the level with the new level
            retVec.emplace_back(pNode->getData());
        }
        if (pNode->m_pLeft) //As we are using queue (FIFO) thuis push left first then right.
            nodeQueue.push(std::make_pair(pNode->m_pLeft.get(), level + 1));
        if (pNode->m_pRight)
            nodeQueue.push(std::make_pair(pNode->m_pRight.get(), level + 1));

        nodeQueue.pop();
    }
    return retVec;
}

IntVector BSTTest::getRightView(const BSTree<int>& tree) const noexcept
{
    if (tree.empty())
        return IntVector{};

    /*
        The main logic behing getting the right view of a BST is
        nothing but a level order traversal of the tree. The initial
        level starts at 0 and we increment this for both it's left
        and right subtrees. During the recursion (here backtracking)
        we check whether the child node in consideration is at the same
        level or at higher level. If it is at higher level than the
        current level we take it in otherwise we just go for it's
        children down the line further.
    */
    Queue<std::pair<TreeNode<int>*, int>> nodeQueue = { std::make_pair(tree.getRoot(), 0) };
    auto currentLevel = -1;
    IntVector retVec;
    while (!nodeQueue.empty())
    {
        auto level = nodeQueue.front().second;
        auto pNode = nodeQueue.front().first;
        if (level > currentLevel)
        {
            currentLevel = level;
            retVec.emplace_back(pNode->getData());
        }
        if (pNode->m_pRight)
            nodeQueue.push(std::make_pair(pNode->m_pRight.get(), level + 1));

        if (pNode->m_pLeft)
            nodeQueue.push(std::make_pair(pNode->m_pLeft.get(), level + 1));

        nodeQueue.pop();
    }
    return retVec;
}

std::map<int, int> BSTTest::getTopView(const BSTree<int>& tree) const noexcept
{
    if (tree.empty())
        return std::map<int, int>{};

    /*
        This is basically a level order traversal of the BST.
        For the left sub tree we decrement the level by 1
        and for the right sub tree we increment it by 1 so
        that there is no conflict while searching in the map
        for left and right sub tree at the same level
    */
    Queue<std::pair<TreeNode<int>*, int>> nodeQueue = { std::make_pair(tree.getRoot(), 0) };
    std::map<int, int> mapLevelAndNodes;
    while (!nodeQueue.empty())
    {
        auto pCurrNode = nodeQueue.front().first;
        auto currLevel = nodeQueue.front().second;
        nodeQueue.pop();

        if (mapLevelAndNodes.find(currLevel) == mapLevelAndNodes.end())
            mapLevelAndNodes[currLevel] = pCurrNode->getData();

        if (pCurrNode->m_pLeft)
            nodeQueue.push(std::make_pair(pCurrNode->m_pLeft.get(), currLevel - 1));
        if (pCurrNode->m_pRight)
            nodeQueue.push(std::make_pair(pCurrNode->m_pRight.get(), currLevel + 1));
    }
    return mapLevelAndNodes;
}

void BSTTest::testTree(const BSTree<int>& tree) const noexcept
{
    constexpr size_t expectedHeight = 4;
    constexpr size_t expectedSize = 9;
    EXPECT_EQ(expectedHeight, tree.height());
    EXPECT_EQ(expectedSize, tree.size());

    //The in-order traversal of a balanced BST always
    //should give the tree elements in a sorted order (guranteed)
    /*
        A balanced BST constructed from the elements ranges 1:9
        either form a BST like below
                5
               / \
              3   7
             / \ / \
            2  4 6  8
           /         \
          1           9

        or another like below one which also a balanced BST
                        5
                       / \
                      2    7
                     / \  / \
                    1   3 6  8
                         \    \
                          4    9

        So pre-order or post-order traversal which are performed
        in testBalancedBST method may give different results than
        expected thus in-order is only used here for determining
    */
    IntVector treeItemsInOrder = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto inOrderList = getElementsInOrder(tree);
    for (size_t idx = 0; idx < treeItemsInOrder.size(); ++idx)
        EXPECT_EQ(treeItemsInOrder[idx], inOrderList[idx]);

    /*
        The left view of the tree should be an array like below
        5 2 1 4 whereas right view would be 5 7 8 9
    */
    IntVector leftViewExpected = { 5, 2, 1, 4 };
    auto leftViewActual = getLeftView(tree);
    for (size_t idx = 0; idx < leftViewExpected.size(); ++idx)
        EXPECT_EQ(leftViewActual[idx], leftViewExpected[idx]);

    IntVector rightViewExpected = { 5, 7, 8, 9 };
    auto rightViewActual = getRightView(tree);
    for (size_t idx = 0; idx < rightViewExpected.size(); ++idx)
        EXPECT_EQ(rightViewActual[idx], rightViewExpected[idx]);

    /*
        Top view of this tree should give us an array
        like 1 2 5 7 8 9 or 9 8 7 5 2 1 depending
        upon which sub tree is looked at first from the
        top or root
    */
    IntVector topViewExpected = { 1, 2, 5, 7, 8, 9 };
    auto topViewActual = getTopView(tree);
    auto idx = 0;
    for (const auto item : topViewActual)
    {
        EXPECT_EQ(item.second, topViewExpected[idx]);
        ++idx;
    }
}

TEST_F(BSTTest, testDefaultConstructor)
{
    constexpr size_t expectedVal = 0;
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
        auto items = getElementsPreOrder(m_BST);
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(2, items[0]);
        EXPECT_EQ(1, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing in order
    {
        auto items = getElementsInOrder(m_BST);
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(1, items[0]);
        EXPECT_EQ(2, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing post order
    {
        auto items = getElementsPostOrder(m_BST);
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

    IntVector treeItems = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    for (const auto item : treeItems)
        EXPECT_TRUE(m_BST.insert(item));

    testBalancedBST(m_BST);

    /*
        If we atke a left view of the tree then it would give us an array
        like 5 3 2 1 nad right view as 5, 7, 8, 9
    */
    IntVector leftView = { 5, 3, 2, 1 };
    auto leftViewActual = getLeftView(m_BST);
    for (size_t idx = 0; idx < leftView.size(); ++idx)
        EXPECT_EQ(leftView[idx], leftViewActual[idx]);

    IntVector rightView = { 5, 7, 8, 9};
    auto rightViewActual = getRightView(m_BST);
    for (size_t idx = 0; idx < rightView.size(); ++idx)
        EXPECT_EQ(rightView[idx], rightViewActual[idx]);

    /*
        Top view of this tree should give us an array
        like 1 2 3 5 7 8 9 or 9 8 7 5 3 2 1 depending
        upon which sub tree is looked at first from the
        top or root
    */
    IntVector topViewExpected = { 1, 2, 3, 5, 7, 8, 9 };
    auto topViewActual = getTopView(m_BST);
    auto idx = 0;
    for (const auto item : topViewActual)
    {
        EXPECT_EQ(item.second, topViewExpected[idx]);
        ++idx;
    }
}

TEST_F(BSTTest, testInitializerListConstructor)
{
    /*
        The purpose of this test case is to test
        initializer list constructor of the BST
        class which builds a balanced BST tree
        by calling internally constructBalancedBST
        method
    */
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);
}

TEST_F(BSTTest, testCopyConstructor)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    auto copyTree = tree;
    testTree(copyTree);
    testTree(tree);
}

TEST_F(BSTTest, testAssignment)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);
    
    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_BST.getRoot());
    ASSERT_EQ(expectedVal, m_BST.size());
    ASSERT_EQ(expectedVal, m_BST.height());

    m_BST = tree;
    testTree(m_BST);
}

TEST_F(BSTTest, testMoveConstructor)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);

    auto copyTree = std::move(tree);
    testTree(copyTree);

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());
}

TEST_F(BSTTest, testMoveAssignment)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_BST.getRoot());
    ASSERT_EQ(expectedVal, m_BST.size());
    ASSERT_EQ(expectedVal, m_BST.height());

    m_BST = std::move(tree);
    testTree(m_BST);

    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());
}

TEST_F(BSTTest, testClearTree)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);

    tree.clear();

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());

}

TEST_F(BSTTest, testCopyTree)
{
    {
        std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
        BSTree<int> tree(iList);

        constexpr size_t expectedVal = 0;
        ASSERT_EQ(nullptr, m_BST.getRoot());
        ASSERT_EQ(expectedVal, m_BST.size());
        ASSERT_EQ(expectedVal, m_BST.height());

        m_BST.copy(tree);

        testTree(tree);
    }
    testTree(m_BST);
}

TEST_F(BSTTest, testErase)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree<int> tree(iList);
    testTree(tree);

    constexpr size_t originalSize = 9;

    EXPECT_NE(tree.find(5), nullptr);
    EXPECT_EQ(originalSize, tree.size());

    EXPECT_TRUE(tree.erase(5));

    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_EQ(originalSize - 1, tree.size());
}
