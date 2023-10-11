/**
 * @file DoublyLinkedListTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DoublyLinkedListTest.h"

#include <vector>

using swarnendu_nodes::DoublyNode;

TEST_F(DoublyLinkedListTest, testDefaultConstructor)
{
    ASSERT_EQ(0, static_cast<int>(m_dList.size()));
    ASSERT_TRUE(m_dList.empty());
    ASSERT_EQ(nullptr, m_dList.getHead());
    ASSERT_EQ(nullptr, m_dList.getTail());
}

TEST_F(DoublyLinkedListTest, testInitializerConstructor)
{
    DoublyLinkedList<int> dList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ASSERT_EQ(10, static_cast<int>(dList.size()));
    ASSERT_FALSE(dList.empty());
    ASSERT_NE(nullptr, dList.getHead());
    ASSERT_NE(nullptr, dList.getTail());

    std::vector<int> elementsVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testCopy)
{
    DoublyLinkedList<int> dList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> elementsVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        DoublyLinkedList<int> dListCopy = dList;
        ASSERT_EQ(10, static_cast<int>(dListCopy.size()));
        ASSERT_FALSE(dListCopy.empty());

        testElementsInList(elementsVec, dListCopy.getHead(), dListCopy.getTail());
    }
    ASSERT_EQ(10, static_cast<int>(dList.size()));
    ASSERT_FALSE(dList.empty());
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testAssignment)
{
    DoublyLinkedList<int> dList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> elementsVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    {
        DoublyLinkedList<int> dListSecond = {11, 12, 13, 14, 15};
        std::vector<int> elementsVec = {11, 12, 13, 14, 15};
        dList = dListSecond;
        EXPECT_EQ(elementsVec.size(), dList.size());
        testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    }
}

TEST_F(DoublyLinkedListTest, testMoveConstructor)
{
    DoublyLinkedList<int> dList = {11, 12, 13, 14, 15};
    std::vector<int> elementsVec = {11, 12, 13, 14, 15};
    {
        DoublyLinkedList<int> dListMoved = std::move(dList);

        ASSERT_EQ(5, static_cast<int>(dListMoved.size()));
        ASSERT_FALSE(dListMoved.empty());
        testElementsInList(elementsVec, dListMoved.getHead(), dListMoved.getTail());
    }
    ASSERT_EQ(0, static_cast<int>(dList.size()));
    ASSERT_TRUE(dList.empty());
    ASSERT_EQ(nullptr, dList.getHead());
    ASSERT_EQ(nullptr, dList.getTail());
}

TEST_F(DoublyLinkedListTest, testMoveAssignment)
{
    DoublyLinkedList<int> dList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> elementsVec = {11, 12, 13, 14, 15};
    {
        DoublyLinkedList<int> dListSecond = {11, 12, 13, 14, 15};
        dList = std::move(dListSecond);
        ASSERT_EQ(0, static_cast<int>(dListSecond.size()));
        ASSERT_TRUE(dListSecond.empty());
        ASSERT_EQ(nullptr, dListSecond.getHead());
        ASSERT_EQ(nullptr, dListSecond.getTail());
    }
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testPushFront)     //Push back is already tested via initializer list constructor test
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    dList.push_front(11);
    std::vector<int> elementsVecNew = {11, 12, 13, 14, 15};
    EXPECT_EQ(elementsVecNew.size(), dList.size());
    testElementsInList(elementsVecNew, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testPushAt)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    dList.push_at(21, 2);
    std::vector<int> elementsVecNew = {12, 13, 21, 14, 15};
    EXPECT_EQ(elementsVecNew.size(), dList.size());
    testElementsInList(elementsVecNew, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testPopFront)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    EXPECT_EQ(dList.pop_front(), 12);
    std::vector<int> elementsVecNew = {13, 14, 15};
    EXPECT_EQ(elementsVecNew.size(), dList.size());
    testElementsInList(elementsVecNew, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testPopBack)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    EXPECT_EQ(dList.pop_back(), 15);
    elementsVec.pop_back();
    EXPECT_EQ(elementsVec.size(), dList.size());
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testPopAt)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    EXPECT_EQ(dList.pop_at(2), 14);
    std::vector<int> elementsVecNew = {12, 13, 15};
    EXPECT_EQ(elementsVecNew.size(), dList.size());
    testElementsInList(elementsVecNew, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testErase)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    EXPECT_EQ(dList.erase(13), 13);
    std::vector<int> elementsVecNew = {12, 14, 15};
    EXPECT_EQ(elementsVecNew.size(), dList.size());
    testElementsInList(elementsVecNew, dList.getHead(), dList.getTail());
}

TEST_F(DoublyLinkedListTest, testFind)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    {
        auto [found, element] = dList.find(13);
        EXPECT_TRUE(found);
        EXPECT_EQ(13, element->getData());
    }
    EXPECT_EQ(dList.erase(13), 13);
    {
        auto [found, element] = dList.find(13);
        EXPECT_FALSE(found);
        EXPECT_EQ(nullptr, element);
    }
}

TEST_F(DoublyLinkedListTest, testClear)
{
    DoublyLinkedList<int> dList = {12, 13, 14, 15};
    std::vector<int> elementsVec = {12, 13, 14, 15};
    testElementsInList(elementsVec, dList.getHead(), dList.getTail());
    dList.clear();
    ASSERT_EQ(0, static_cast<int>(dList.size()));
    ASSERT_TRUE(dList.empty());
    ASSERT_EQ(nullptr, dList.getHead());
    ASSERT_EQ(nullptr, dList.getTail());
}

