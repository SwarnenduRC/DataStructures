/**
 * @file DoublyLinkedListTest.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DoublyLinkedList.h"

#include <gtest/gtest.h>

using swarnendu::DoublyLinkedList;
using swarnendu_nodes::DoublyNode;

class DoublyLinkedListTest : public ::testing::Test
{
    public:
        void testElementsInList(const std::vector<int>& elementsVec, DoublyNode<int>* pHead, DoublyNode<int>* pTail)
        {
            if (elementsVec.empty())
            {
                ASSERT_EQ(nullptr, pHead);
                ASSERT_EQ(nullptr, pTail);
            }
            else
            {
                for (auto itr = elementsVec.cbegin(); itr != elementsVec.cend(); ++itr)
                {
                    EXPECT_EQ(*itr, pHead->getData());
                    pHead = pHead->m_pNext.get();
                }
                ASSERT_EQ(nullptr, pHead);

                for (auto itr = elementsVec.crbegin(); itr != elementsVec.crend(); ++itr)
                {
                    EXPECT_EQ(*itr, pTail->getData());
                    pTail = pTail->m_pPrev.lock().get();
                }
                ASSERT_EQ(nullptr, pTail);
            }
        }
    protected:
        DoublyLinkedList<int> m_dList;
};