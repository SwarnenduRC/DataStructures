/**
 * @file DoublyNodeTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DoublyNodeTest.h"

TEST_F(DoublyNodeTest, testDefaultConstructor)
{
    ASSERT_EQ(nullptr, m_doublyNode.m_pNext);
    ASSERT_EQ(nullptr, m_doublyNode.m_pPrev.lock());
}

TEST_F(DoublyNodeTest, testParametarizedConstrucotr)
{
    DoublyNode<int> dNode(5);
    ASSERT_EQ(nullptr, dNode.m_pNext);
    ASSERT_EQ(nullptr, dNode.m_pPrev.lock());
    EXPECT_EQ(5, dNode.getData());
}

TEST_F(DoublyNodeTest, testCopyConstructor)
{
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dCopyNode = dNode;
        ASSERT_EQ(nullptr, dCopyNode.m_pNext);
        ASSERT_EQ(nullptr, dCopyNode.m_pPrev.lock());
        EXPECT_EQ(5, dCopyNode.getData());
    }
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dNodePrev(4);
        DoublyNode<int> dNodeNext(6);
        auto pPrevNode = std::make_shared<DoublyNode<int>>(dNodePrev);
        dNode.m_pPrev = pPrevNode;  //Reason being a weak pointer itself is very weak
        dNode.m_pNext = std::make_shared<DoublyNode<int>>(dNodeNext);
        ASSERT_NE(nullptr, dNode.m_pPrev.lock());
        ASSERT_NE(nullptr, dNode.m_pNext);
        ASSERT_EQ(4, dNode.m_pPrev.lock()->getData());
        ASSERT_EQ(6, dNode.m_pNext->getData());

        DoublyNode<int> dCopyNode = dNode;
        EXPECT_EQ(5, dCopyNode.getData());
        EXPECT_EQ(6, dNode.m_pNext->getData());
        EXPECT_EQ(4, dNode.m_pPrev.lock()->getData());
    }
}

TEST_F(DoublyNodeTest, testAssignment)
{
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dCopyNode;
        dCopyNode = dNode;
        ASSERT_EQ(nullptr, dCopyNode.m_pNext);
        ASSERT_EQ(nullptr, dCopyNode.m_pPrev.lock());
        EXPECT_EQ(5, dCopyNode.getData());
    }
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dNodePrev(4);
        DoublyNode<int> dNodeNext(6);
        auto pPrevNode = std::make_shared<DoublyNode<int>>(dNodePrev);
        dNode.m_pPrev = pPrevNode;  //Reason being a weak pointer itself is very weak
        dNode.m_pNext = std::make_shared<DoublyNode<int>>(dNodeNext);
        ASSERT_NE(nullptr, dNode.m_pPrev.lock());
        ASSERT_NE(nullptr, dNode.m_pNext);
        ASSERT_EQ(4, dNode.m_pPrev.lock()->getData());
        ASSERT_EQ(6, dNode.m_pNext->getData());

        DoublyNode<int> dCopyNode;
        dCopyNode = dNode;
        EXPECT_EQ(5, dCopyNode.getData());
        EXPECT_EQ(6, dCopyNode.m_pNext->getData());
        EXPECT_EQ(4, dCopyNode.m_pPrev.lock()->getData());
    }
}

TEST_F(DoublyNodeTest, testMoveConstructor)
{
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dNodePrev(4);
        DoublyNode<int> dNodeNext(6);
        auto pPrevNode = std::make_shared<DoublyNode<int>>(dNodePrev);
        dNode.m_pPrev = pPrevNode;  //Reason being a weak pointer itself is very weak
        dNode.m_pNext = std::make_shared<DoublyNode<int>>(dNodeNext);
        ASSERT_NE(nullptr, dNode.m_pPrev.lock());
        ASSERT_NE(nullptr, dNode.m_pNext);
        ASSERT_EQ(4, dNode.m_pPrev.lock()->getData());
        ASSERT_EQ(6, dNode.m_pNext->getData());

        auto dCopyNode = std::move(dNode);
        EXPECT_EQ(5, dCopyNode.getData());
        EXPECT_EQ(6, dCopyNode.m_pNext->getData());
        EXPECT_EQ(4, dCopyNode.m_pPrev.lock()->getData());
        ASSERT_EQ(nullptr, dNode.m_pPrev.lock());
        ASSERT_EQ(nullptr, dNode.m_pNext);
        ASSERT_EQ(0, dNode.getData());
    }
}

TEST_F(DoublyNodeTest, testMoveAssignment)
{
    {
        DoublyNode<int> dNode(5);
        DoublyNode<int> dNodePrev(4);
        DoublyNode<int> dNodeNext(6);
        auto pPrevNode = std::make_shared<DoublyNode<int>>(dNodePrev);
        dNode.m_pPrev = pPrevNode;  //Reason being a weak pointer itself is very weak
        dNode.m_pNext = std::make_shared<DoublyNode<int>>(dNodeNext);
        ASSERT_NE(nullptr, dNode.m_pPrev.lock());
        ASSERT_NE(nullptr, dNode.m_pNext);
        ASSERT_EQ(4, dNode.m_pPrev.lock()->getData());
        ASSERT_EQ(6, dNode.m_pNext->getData());

        auto dCopyNode = DoublyNode<int>(7);
        dCopyNode = std::move(dNode);
        EXPECT_EQ(5, dCopyNode.getData());
        EXPECT_EQ(6, dCopyNode.m_pNext->getData());
        EXPECT_EQ(4, dCopyNode.m_pPrev.lock()->getData());
        ASSERT_EQ(nullptr, dNode.m_pPrev.lock());
        ASSERT_EQ(nullptr, dNode.m_pNext);
        ASSERT_EQ(0, dNode.getData());
    }
}
