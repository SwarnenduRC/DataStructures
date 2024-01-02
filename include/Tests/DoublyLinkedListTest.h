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
#include <list>

using swarnendu::DoublyLinkedList;
using swarnendu_nodes::DoublyNode;

class DoublyLinkedListTest : public ::testing::Test
{
    public:
        void testElementsInList(const std::list<int>& refList, DoublyLinkedList<int>& list)
        {
            if (refList.empty())
                ASSERT_TRUE(list.empty());
            
            else
            {
                auto refItr = refList.begin();
                auto itr = list.begin();
                for (; refItr != refList.end() && itr != list.end(); ++refItr, ++itr)
                    EXPECT_EQ(*refItr, *itr);

                auto rRefItr = refList.rbegin();
                auto rItr = list.rbegin();
                for (; rRefItr != refList.rend() && rItr != list.rend(); ++rItr, ++rRefItr)
                    EXPECT_EQ(*rRefItr, *rItr);
            }
        }
        void testElementsInList(const std::list<char>& refList, DoublyLinkedList<char>& list)
        {
            if (refList.empty())
                ASSERT_TRUE(list.empty());
            
            else
            {
                auto refItr = refList.begin();
                auto itr = list.begin();
                for (; refItr != refList.end() && itr != list.end(); ++refItr, ++itr)
                    EXPECT_EQ(*refItr, *itr);

                auto rRefItr = refList.rbegin();
                auto rItr = list.rbegin();
                for (; rRefItr != refList.rend() && rItr != list.rend(); ++rItr, ++rRefItr)
                    EXPECT_EQ(*rRefItr, *rItr);
            }
        }
    protected:
        DoublyLinkedList<int> m_dList;
};