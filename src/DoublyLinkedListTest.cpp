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

#include <algorithm>

TEST_F(DoublyLinkedListTest, testDefaultConstructor)
{
    ASSERT_EQ(0, static_cast<int>(m_dList.size()));
    ASSERT_TRUE(m_dList.empty());
    ASSERT_EQ(nullptr, m_dList.getHead());
    ASSERT_EQ(nullptr, m_dList.getTail());
}

TEST_F(DoublyLinkedListTest, testInitializerConstructor)
{
    DoublyLinkedList<int> dList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    ASSERT_EQ(10, static_cast<int>(dList.size()));
    ASSERT_FALSE(dList.empty());
    ASSERT_NE(nullptr, dList.getHead());
    ASSERT_NE(nullptr, dList.getTail());

    std::list<int> refList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testCopy)
{
    DoublyLinkedList<int> dList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> refList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        DoublyLinkedList<int> dListCopy = dList;
        ASSERT_EQ(10, static_cast<int>(dListCopy.size()));
        ASSERT_FALSE(dListCopy.empty());

        testElementsInList(refList, dListCopy);
    }
    ASSERT_EQ(10, static_cast<int>(dList.size()));
    ASSERT_FALSE(dList.empty());
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testAssignment)
{
    DoublyLinkedList<int> dList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> refList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    testElementsInList(refList, dList);
    {
        DoublyLinkedList<int> dListSecond = { 11, 12, 13, 14, 15 };
        std::list<int> refList = { 11, 12, 13, 14, 15 };
        dList = dListSecond;
        EXPECT_EQ(refList.size(), dList.size());
        testElementsInList(refList, dList);
    }
}

TEST_F(DoublyLinkedListTest, testMoveConstructor)
{
    DoublyLinkedList<int> dList = { 11, 12, 13, 14, 15 };
    std::list<int> refList = { 11, 12, 13, 14, 15 };
    {
        DoublyLinkedList<int> dListMoved = std::move(dList);

        ASSERT_EQ(5, static_cast<int>(dListMoved.size()));
        ASSERT_FALSE(dListMoved.empty());
        testElementsInList(refList, dListMoved);
    }
    ASSERT_EQ(0, static_cast<int>(dList.size()));
    ASSERT_TRUE(dList.empty());
    ASSERT_EQ(nullptr, dList.getHead());
    ASSERT_EQ(nullptr, dList.getTail());
}

TEST_F(DoublyLinkedListTest, testMoveAssignment)
{
    DoublyLinkedList<int> dList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> refList = { 11, 12, 13, 14, 15 };
    {
        DoublyLinkedList<int> dListSecond = {11, 12, 13, 14, 15};
        dList = std::move(dListSecond);
        ASSERT_EQ(0, static_cast<int>(dListSecond.size()));
        ASSERT_TRUE(dListSecond.empty());
        ASSERT_EQ(nullptr, dListSecond.getHead());
        ASSERT_EQ(nullptr, dListSecond.getTail());
    }
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testPushFront)     //Push back is already tested via initializer list constructor test
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15} ;
    std::list<int> refList = { 12, 13, 14, 15 };
    testElementsInList(refList, dList);
    dList.push_front(11);
    std::list<int> refListNew = { 11, 12, 13, 14, 15 };
    EXPECT_EQ(refListNew.size(), dList.size());
    testElementsInList(refListNew, dList);
}

TEST_F(DoublyLinkedListTest, testPopFront)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    std::list<int> refList = { 12, 13, 14, 15 };
    testElementsInList(refList, dList);
    dList.pop_front();
    refList.pop_front();
    EXPECT_EQ(refList.size(), dList.size());
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testPopBack)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    std::list<int> refList = { 12, 13, 14, 15 };
    testElementsInList(refList, dList);
    dList.pop_back();
    refList.pop_back();
    EXPECT_EQ(refList.size(), dList.size());
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testPopAt)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    std::list<int> refList = { 12, 13, 14, 15 };
    testElementsInList(refList, dList);
    dList.pop_at(2);
    std::list<int> refListNew = { 12, 13, 15 };
    EXPECT_EQ(refListNew.size(), dList.size());
    testElementsInList(refListNew, dList);
}

TEST_F(DoublyLinkedListTest, testErase1)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    EXPECT_EQ(dList.end(), dList.erase(dList.cend()));
    EXPECT_TRUE(dList.find(12));
    auto itr = dList.erase(dList.cbegin());
    EXPECT_EQ(13, *itr);
    EXPECT_FALSE(dList.find(12));
}

TEST_F(DoublyLinkedListTest, testErase2)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    auto itr = dList.cbegin();
    ++itr;
    EXPECT_TRUE(dList.find(13));
    auto retItr = dList.erase(itr);
    EXPECT_EQ(14, *retItr);
    EXPECT_FALSE(dList.find(13));
}

TEST_F(DoublyLinkedListTest, testErase3)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    auto first = dList.cbegin();
    auto last = dList.cbegin();
    ++first;
    ++last;
    ++last;
    EXPECT_TRUE(dList.find(13));
    EXPECT_TRUE(dList.find(14));
    auto retItr = dList.erase(first, last);
    EXPECT_EQ(15, *retItr);
    EXPECT_FALSE(dList.find(13));
    EXPECT_FALSE(dList.find(14));
}

TEST_F(DoublyLinkedListTest, testInsert1)
{
    {
        DoublyLinkedList<int> dList = { 12, 14, 15, 16 };
        std::list<int> refList = { 12, 14, 15, 16 };
        auto pos = dList.cbegin();
        auto refPos = refList.cbegin();
        ++pos;
        ++refPos;
        EXPECT_FALSE(dList.find(13));
        auto newItr = dList.insert(pos, 13);
        auto newRefItr = refList.insert(refPos, 13);
        EXPECT_EQ(13, *newItr);
        EXPECT_EQ(13, *newRefItr);
        ++newItr;
        ++newRefItr;
        EXPECT_EQ(14, *newItr);
        EXPECT_EQ(14, *newRefItr);
        --newItr; --newItr;
        --newRefItr; --newRefItr;
        EXPECT_EQ(12, *newItr);
        EXPECT_EQ(12, *newRefItr);
        EXPECT_TRUE(dList.find(13));
        testElementsInList(refList, dList);
    }
    {
        DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
        std::list<int> refList = { 12, 13, 14, 15 };
        EXPECT_FALSE(dList.find(11));
        auto pos = dList.cbegin();
        auto refPos = refList.cbegin();
        auto newItr = dList.insert(pos, 11);
        auto newItrRef = refList.insert(refPos, 11);
        EXPECT_EQ(11, *newItr);
        EXPECT_EQ(11, *newItrRef);
        EXPECT_TRUE(dList.find(11));
        testElementsInList(refList, dList);
        EXPECT_EQ(dList.end(), --newItr);
        EXPECT_EQ(refList.end(), --newItrRef);
    }
    {
        DoublyLinkedList<int> dList = { 11, 12, 13, 15 };
        EXPECT_FALSE(dList.find(14));
        auto pos = dList.crbegin();
        auto newItr = dList.insert(pos, 14);
        EXPECT_EQ(14, *newItr);
        EXPECT_TRUE(dList.find(14));
        std::list<int> refList = { 11, 12, 13, 14, 15 };
        testElementsInList(refList, dList);
        EXPECT_EQ(15, *++newItr);
    }
}

TEST_F(DoublyLinkedListTest, testInsert2)
{
    DoublyLinkedList<int> dList = { 11, 12, 13, 15 };
    std::list<int> refList = { 11, 12, 13, 15 };
    auto pos = dList.cbegin();
    auto refPos = refList.cbegin();
    while (*pos != 13 && *refPos != 13)
    {
        ++pos;
        ++refPos;
    }
    auto retItrRef = refList.insert(refPos, 3, 21);
    auto retItr = dList.insert(pos, 3, 21);
    EXPECT_EQ(21, *retItr);
    EXPECT_EQ(21, *retItrRef);
    testElementsInList(refList, dList);
}

TEST_F(DoublyLinkedListTest, testInsert3)
{
    DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
    std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
    std::initializer_list<char> iList = { ' ', 'R', 'O', 'Y', ' ' };
    auto pos = list.cbegin();
    auto refPos = refList.cbegin();
    while (*pos != 'C')
        ++pos;    
    refPos = std::next(refPos, 7);
    EXPECT_EQ(*pos, *refPos);
    list.insert(pos, iList);
    refList.insert(refPos, iList);
    testElementsInList(refList, list);
}

TEST_F(DoublyLinkedListTest, testResize1)
{
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(7);
        refList.resize(7);
        testElementsInList(refList, list);
    }
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(27);
        refList.resize(27);
        testElementsInList(refList, list);
    }
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(list.size());
        refList.resize(refList.size());
        testElementsInList(refList, list);
    }
}

TEST_F(DoublyLinkedListTest, testResize2)
{
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(7, 'B');
        refList.resize(7, 'B');
        testElementsInList(refList, list);
    }
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(27, 'B');
        refList.resize(27, 'B');
        testElementsInList(refList, list);
    }
    {
        DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
        list.resize(list.size(), 'B');
        refList.resize(refList.size(), 'B');
        testElementsInList(refList, list);
    }
}

TEST_F(DoublyLinkedListTest, testClear)
{
    DoublyLinkedList<int> dList = { 12, 13, 14, 15 };
    std::list<int> refList = { 12, 13, 14, 15 };
    testElementsInList(refList, dList);
    dList.clear();
    ASSERT_EQ(0, static_cast<int>(dList.size()));
    ASSERT_TRUE(dList.empty());
    ASSERT_EQ(nullptr, dList.getHead());
    ASSERT_EQ(nullptr, dList.getTail());
}

TEST_F(DoublyLinkedListTest, testReverse)
{
    DoublyLinkedList<char> list = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
    std::list<char> refList = { 'K', 'R', 'I', 'T', 'I', 'K', 'A', 'C', 'H', 'O', 'W', 'D', 'H', 'U', 'R', 'Y' };
    testElementsInList(refList, list);
    refList.reverse();
    list.reverse();
    testElementsInList(refList, list);
}

TEST_F(DoublyLinkedListTest, testComparisonOperators)
{
    {
        DoublyLinkedList<int> dList1 = { 12, 13, 14, 15 };
        DoublyLinkedList<int> dList2 = { 12, 13, 14, 15 };
        EXPECT_TRUE(dList1 == dList2);
        EXPECT_FALSE(dList1 != dList2);
    }
    {
        DoublyLinkedList<int> dList1;
        DoublyLinkedList<int> dList2;
        EXPECT_TRUE(dList1 == dList2);
        EXPECT_FALSE(dList1 != dList2);
    }
    {
        DoublyLinkedList<int> dList1 = { 12, 13, 14, 15 };
        DoublyLinkedList<int> dList2 = { 2, 13, 14, 15 };
        EXPECT_FALSE(dList1 == dList2);
        EXPECT_TRUE(dList1 != dList2);
    }
    {
        DoublyLinkedList<int> dList1 = { 12, 13, 14, 15 };
        DoublyLinkedList<int> dList2 = { 15, 13, 14, 12 };
        EXPECT_FALSE(dList1 == dList2);
        EXPECT_TRUE(dList1 != dList2);
    }
    {
        DoublyLinkedList<int> dList1 = { 12, 13, 14, 15 };
        DoublyLinkedList<int> dList2 = { 12, 13, 14 };
        EXPECT_FALSE(dList1 == dList2);
        EXPECT_TRUE(dList1 != dList2);
    }
}

TEST_F(DoublyLinkedListTest, testForwadIterator)
{
    DoublyLinkedList<int> dList = { 12, 15, 13, 14 };
    std::list<int> refList = { 12, 15, 13, 14 };
    {
        auto itr = DoublyLinkedList<int>::iterator();
        EXPECT_TRUE(dList.end() == itr);
    }
    {
        auto itr = m_dList.begin();
        EXPECT_TRUE(dList.end() == itr);
    }
    {
        auto itr = dList.begin();
        EXPECT_TRUE(itr != dList.end());
        EXPECT_EQ(*itr, 12);
    }
    {
        auto refItr = refList.begin();
        auto itr = dList.begin();
        for (; itr != dList.end() && refItr != refList.end(); ++itr, ++refItr)
            EXPECT_EQ(*itr, *refItr);
    }
    {
        auto refItr = refList.begin();
        for (auto& itr : dList)
        {
            EXPECT_EQ(itr, *refItr);
            ++refItr;
        }
    }
    {
        auto refItr = refList.begin();
        std::for_each(dList.begin(), dList.end(), [&](const int val){ EXPECT_EQ(val, *refItr); ++refItr; });
    }
}

TEST_F(DoublyLinkedListTest, testReverseIterator)
{
    DoublyLinkedList<int> dList = { 12, 15, 13, 14 };
    std::list<int> refList = { 12, 15, 13, 14 };
    {
        auto itr = m_dList.rbegin();
        EXPECT_TRUE(m_dList.rend() == itr);
    }
    {
        auto itr = dList.rbegin();
        EXPECT_TRUE(itr != dList.rend());
        EXPECT_EQ(*itr, 14);
    }
    {
        auto refItr = refList.rbegin();
        for (auto itr = dList.rbegin(); itr != dList.rend() && refItr != refList.rend(); ++itr, ++refItr)
            EXPECT_EQ(*itr, *refItr);
    }
    {
        auto refItr = refList.rbegin();
        std::for_each(dList.rbegin(), dList.rend(), [&](const int val){ EXPECT_EQ(val, *refItr); ++refItr; });
    }
}

TEST_F(DoublyLinkedListTest, testConstForwardIterator)
{
    DoublyLinkedList<int> dList = { 12, 15, 13, 14 };
    std::list<int> refList = { 12, 15, 13, 14 };
    {
        auto itr = DoublyLinkedList<int>::const_iterator();
        EXPECT_TRUE(dList.cend() == itr);
    }
    {
        auto itr = m_dList.cbegin();
        EXPECT_TRUE(dList.cend() == itr);
    }
    {
        auto itr = dList.cbegin();
        EXPECT_TRUE(itr != dList.cend());
        EXPECT_EQ(*itr, 12);
    }
    {
        auto refItr = refList.cbegin();
        for (auto itr = dList.cbegin(); itr != dList.cend() && refItr != refList.cend(); ++itr, ++refItr)
            EXPECT_EQ(*itr, *refItr);
    }
    {
        auto refItr = refList.cbegin();
        std::for_each(dList.cbegin(), dList.cend(), [&](const int val){ EXPECT_EQ(val, *refItr); ++refItr; });
    }
}

TEST_F(DoublyLinkedListTest, testReverseConstantIterator)
{
    DoublyLinkedList<int> dList = { 12, 15, 13, 14 };
    std::list<int> refList = { 12, 15, 13, 14 };
    {
        auto itr = m_dList.crbegin();
        EXPECT_TRUE(m_dList.crend() == itr);
    }
    {
        auto itr = dList.crbegin();
        EXPECT_TRUE(itr != dList.crend());
        EXPECT_EQ(*itr, 14);
    }
    {
        auto refItr = refList.crbegin();
        for (auto itr = dList.crbegin(); itr != dList.crend() && refItr != refList.crend(); ++itr, ++refItr)
            EXPECT_EQ(*itr, *refItr);
    }
    {
        auto refItr = refList.crbegin();
        std::for_each(dList.crbegin(), dList.crend(), [&](const int val){ EXPECT_EQ(val, *refItr); ++refItr; });
    }
}

