/**
 * @file SinglyLinkedListTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SinglyLinkedListTest.h"

TEST_F(SinglyLinkedListTest, testDefaultConstructor)
{
    ASSERT_EQ(nullptr, m_sList.getHead());
    ASSERT_EQ(nullptr, m_sList.getTail());
    ASSERT_EQ(0, static_cast<int>(m_sList.size()));
}

TEST_F(SinglyLinkedListTest, testInitializerListConstructor)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(10, static_cast<int>(slist.size()));
    EXPECT_FALSE(slist.empty());
    ASSERT_NE(nullptr, slist.getHead());
    ASSERT_NE(nullptr, slist.getTail());
    EXPECT_EQ(1, slist.getHead()->m_element);
    EXPECT_EQ(10, slist.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testCopyConstructor)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        SinglyLinkedList slistCopy = slist;
        EXPECT_EQ(10, static_cast<int>(slistCopy.size()));
        EXPECT_FALSE(slistCopy.empty());
        ASSERT_NE(nullptr, slistCopy.getHead());
        ASSERT_NE(nullptr, slistCopy.getTail());
        EXPECT_EQ(slist.getHead()->m_element, slistCopy.getHead()->m_element);
        EXPECT_EQ(slist.getTail()->m_element, slistCopy.getTail()->m_element);
    }
    ASSERT_FALSE(slist.empty());
    ASSERT_NE(nullptr, slist.getHead());
    ASSERT_NE(nullptr, slist.getTail());
    EXPECT_EQ(1, slist.getHead()->m_element);
    EXPECT_EQ(10, slist.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testCopyAssignment)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        SinglyLinkedList slistCopy = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        slistCopy = slist;
        EXPECT_FALSE(slistCopy.empty());
        ASSERT_NE(nullptr, slistCopy.getHead());
        ASSERT_NE(nullptr, slistCopy.getTail());
        EXPECT_EQ(slist.getHead()->m_element, slistCopy.getHead()->m_element);
        EXPECT_EQ(slist.getTail()->m_element, slistCopy.getTail()->m_element);
    }
    ASSERT_FALSE(slist.empty());
    ASSERT_NE(nullptr, slist.getHead());
    ASSERT_NE(nullptr, slist.getTail());
    EXPECT_EQ(1, slist.getHead()->m_element);
    EXPECT_EQ(10, slist.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testMoveConstructor)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        SinglyLinkedList slistCopy = std::move(slist);
        EXPECT_EQ(10, static_cast<int>(slistCopy.size()));
        EXPECT_FALSE(slistCopy.empty());
        ASSERT_NE(nullptr, slistCopy.getHead());
        ASSERT_NE(nullptr, slistCopy.getTail());
        EXPECT_EQ(1, slistCopy.getHead()->m_element);
        EXPECT_EQ(10, slistCopy.getTail()->m_element);
    }
    ASSERT_TRUE(slist.empty());
    ASSERT_EQ(nullptr, slist.getHead());
    ASSERT_EQ(nullptr, slist.getTail());
}

TEST_F(SinglyLinkedListTest, testMoveAssignment)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        SinglyLinkedList slistCopy = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        slistCopy = std::move(slist);
        EXPECT_FALSE(slistCopy.empty());
        ASSERT_NE(nullptr, slistCopy.getHead());
        ASSERT_NE(nullptr, slistCopy.getTail());
        EXPECT_EQ(1, slistCopy.getHead()->m_element);
        EXPECT_EQ(10, slistCopy.getTail()->m_element);
    }
    ASSERT_TRUE(slist.empty());
    ASSERT_EQ(nullptr, slist.getHead());
    ASSERT_EQ(nullptr, slist.getTail());
}

TEST_F(SinglyLinkedListTest, testCopyList)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        SinglyLinkedList slistCopy = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        slistCopy.copy(slist);
        EXPECT_FALSE(slistCopy.empty());
        ASSERT_NE(nullptr, slistCopy.getHead());
        ASSERT_NE(nullptr, slistCopy.getTail());
        EXPECT_EQ(slist.size(), slistCopy.size());
        EXPECT_EQ(slist.getHead()->m_element, slistCopy.getHead()->m_element);
        EXPECT_EQ(slist.getTail()->m_element, slistCopy.getTail()->m_element);
    }
    ASSERT_FALSE(slist.empty());
    ASSERT_NE(nullptr, slist.getHead());
    ASSERT_NE(nullptr, slist.getTail());
    EXPECT_EQ(1, slist.getHead()->m_element);
    EXPECT_EQ(10, slist.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testPopFront)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        EXPECT_EQ(1, *slist.find(1));
        auto listSize = slist.size();
        EXPECT_EQ(1, slist.pop_front());
        EXPECT_EQ(--listSize, slist.size());
        EXPECT_EQ(nullptr, slist.find(1));
        EXPECT_EQ(2, *slist.find(2));
        EXPECT_EQ(2, slist.pop_front());
        EXPECT_EQ(--listSize, slist.size());
        EXPECT_EQ(nullptr, slist.find(2));
    }
    {
        SinglyLinkedList slist2 = {1};
        EXPECT_EQ(1, slist2.getHead()->m_element);
        EXPECT_EQ(1, slist2.getTail()->m_element);
        EXPECT_EQ(1, slist2.pop_front());
        EXPECT_EQ(0, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(1));
    }
    {
        SinglyLinkedList slist2 = {1, 2};
        EXPECT_EQ(1, slist2.getHead()->m_element);
        EXPECT_EQ(2, slist2.getTail()->m_element);
        EXPECT_EQ(1, slist2.pop_front());
        EXPECT_EQ(1, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(1));
        EXPECT_EQ(2, slist2.pop_front());
        EXPECT_EQ(0, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(2));
        EXPECT_TRUE(slist2.empty());
    }
}

TEST_F(SinglyLinkedListTest, testPopBack)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        EXPECT_EQ(10, *slist.find(10));
        auto listSize = slist.size();
        EXPECT_EQ(10, slist.pop_back());
        EXPECT_EQ(--listSize, slist.size());
        EXPECT_EQ(nullptr, slist.find(10));
        EXPECT_EQ(9, *slist.find(9));
        EXPECT_EQ(9, slist.pop_back());
        EXPECT_EQ(--listSize, slist.size());
        EXPECT_EQ(nullptr, slist.find(9));
    }
    {
        SinglyLinkedList slist2 = {1};
        EXPECT_EQ(1, slist2.getHead()->m_element);
        EXPECT_EQ(1, slist2.getTail()->m_element);
        EXPECT_EQ(1, slist2.pop_back());
        EXPECT_EQ(0, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(1));
    }
    {
        SinglyLinkedList slist2 = {1, 2};
        EXPECT_EQ(1, slist2.getHead()->m_element);
        EXPECT_EQ(2, slist2.getTail()->m_element);
        EXPECT_EQ(2, slist2.pop_back());
        EXPECT_EQ(1, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(2));
        EXPECT_EQ(1, slist2.pop_back());
        EXPECT_EQ(0, static_cast<int>(slist2.size()));
        EXPECT_EQ(nullptr, slist2.find(1));
        EXPECT_TRUE(slist2.empty());
    }
}

TEST_F(SinglyLinkedListTest, testPopAt)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        EXPECT_EQ(7, *slist.find(7));
        EXPECT_EQ(7, slist.pop_at(6));
        EXPECT_EQ(nullptr, slist.find(7));
        EXPECT_EQ(9, *slist.find(9));
        EXPECT_EQ(3, *slist.find(3));
    }
}

TEST_F(SinglyLinkedListTest, testPopMiddle)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        EXPECT_EQ(6, *slist.find(6));
        EXPECT_EQ(6, slist.pop_middle());
        EXPECT_EQ(nullptr, slist.find(6));
        EXPECT_EQ(9, static_cast<int>(slist.size()));
        EXPECT_EQ(9, *slist.find(9));
        EXPECT_EQ(3, *slist.find(3));
    }
}

TEST_F(SinglyLinkedListTest, testPushFront)
{
    ASSERT_TRUE(m_sList.empty());
    ASSERT_EQ(0, static_cast<int>(m_sList.size()));
    ASSERT_EQ(nullptr, m_sList.getHead());
    ASSERT_EQ(nullptr, m_sList.getTail());

    m_sList.push_front(1);
    EXPECT_EQ(1, static_cast<int>(m_sList.size()));
    EXPECT_FALSE(m_sList.empty());
    EXPECT_EQ(1, *m_sList.find(1));
    EXPECT_EQ(1, m_sList.getHead()->m_element);
    EXPECT_EQ(1, m_sList.getTail()->m_element);

    m_sList.push_front(2);
    EXPECT_EQ(2, static_cast<int>(m_sList.size()));
    EXPECT_FALSE(m_sList.empty());
    EXPECT_EQ(1, *m_sList.find(1));
    EXPECT_EQ(2, *m_sList.find(2));
    EXPECT_EQ(2, m_sList.getHead()->m_element);
    EXPECT_EQ(1, m_sList.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testPushBack)
{
    ASSERT_TRUE(m_sList.empty());
    ASSERT_EQ(0, static_cast<int>(m_sList.size()));
    ASSERT_EQ(nullptr, m_sList.getHead());
    ASSERT_EQ(nullptr, m_sList.getTail());

    m_sList.push_back(1);
    EXPECT_EQ(1, static_cast<int>(m_sList.size()));
    EXPECT_FALSE(m_sList.empty());
    EXPECT_EQ(1, *m_sList.find(1));
    EXPECT_EQ(1, m_sList.getHead()->m_element);
    EXPECT_EQ(1, m_sList.getTail()->m_element);

    m_sList.push_back(2);
    EXPECT_EQ(2, static_cast<int>(m_sList.size()));
    EXPECT_FALSE(m_sList.empty());
    EXPECT_EQ(1, *m_sList.find(1));
    EXPECT_EQ(2, *m_sList.find(2));
    EXPECT_EQ(1, m_sList.getHead()->m_element);
    EXPECT_EQ(2, m_sList.getTail()->m_element);
}

TEST_F(SinglyLinkedListTest, testPushAt)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    slist.push_at(2, 33);
    EXPECT_EQ(11, static_cast<int>(slist.size()));
    auto pListHead = slist.getHead();
    ASSERT_NE(nullptr, pListHead);
    auto cnt = 0;
    do
    {
        pListHead = pListHead->m_pNext;
        ++cnt;
    } while (cnt <= 2);
    EXPECT_EQ(33, pListHead->m_element);
    EXPECT_EQ(4, pListHead->m_pNext->m_element);
    EXPECT_EQ(1, *slist.find(1));
}

TEST_F(SinglyLinkedListTest, testPushMiddle)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    slist.push_middle(33);
    EXPECT_EQ(11, static_cast<int>(slist.size()));
    auto pListHead = slist.getHead();
    auto cnt = 0;
    do
    {
        pListHead = pListHead->m_pNext;
        ++cnt;
    } while (cnt <= 5);
    EXPECT_EQ(33, pListHead->m_element);
    EXPECT_EQ(7, pListHead->m_pNext->m_element);
    EXPECT_EQ(2, *slist.find(2));
}

TEST_F(SinglyLinkedListTest, testMakeCyclic)
{
    SinglyLinkedList slist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_FALSE(SinglyLinkedList::isCyclic(slist.getHead()));
    slist.makeCyclic();
    ASSERT_TRUE(SinglyLinkedList::isCyclic(slist.getHead()));
}

