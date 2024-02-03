/**
 * @file SinglyNodeTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "SinglyNodeTest.h"

TEST_F(SinglyNodeTest, testDefaultConstructor)
{
    ASSERT_EQ(0, m_defaultNode.m_element);
    ASSERT_EQ(nullptr, m_defaultNode.m_pNext);
}

TEST_F(SinglyNodeTest, testParameterizedConstructor)
{
    SinglyNode node(5);
    ASSERT_EQ(5, node.m_element);
    ASSERT_EQ(nullptr, node.m_pNext);
}

TEST_F(SinglyNodeTest, testCopyConstructor)
{
    SinglyNode node(5);
    EXPECT_EQ(5, node.m_element);
    EXPECT_EQ(nullptr, node.m_pNext);

    SinglyNode copyNode(node);
    ASSERT_EQ(5, copyNode.m_element);
    ASSERT_EQ(nullptr, copyNode.m_pNext);
}

TEST_F(SinglyNodeTest, testMoveConstructor)
{
    SinglyNode node(5);
    EXPECT_EQ(5, node.m_element);
    EXPECT_EQ(nullptr, node.m_pNext);

    SinglyNode moveNode = std::move(node);
    EXPECT_EQ(5, moveNode.m_element);
    EXPECT_EQ(nullptr, moveNode.m_pNext);

    ASSERT_EQ(0, node.m_element);
    ASSERT_EQ(nullptr, node.m_pNext);
}

TEST_F(SinglyNodeTest, testAssignment)
{
    SinglyNode node(5);
    EXPECT_EQ(5, node.m_element);
    EXPECT_EQ(nullptr, node.m_pNext);

    SinglyNode copyNode;
    copyNode = node;
    EXPECT_EQ(5, copyNode.m_element);
    EXPECT_EQ(nullptr, copyNode.m_pNext);

    ASSERT_EQ(5, node.m_element);
    ASSERT_EQ(nullptr, node.m_pNext);
}

TEST_F(SinglyNodeTest, testMoveAssignment)
{
    SinglyNode node(5);
    EXPECT_EQ(5, node.m_element);
    EXPECT_EQ(nullptr, node.m_pNext);

    SinglyNode copyNode;
    copyNode = std::move(node);
    EXPECT_EQ(5, copyNode.m_element);
    EXPECT_EQ(nullptr, copyNode.m_pNext);

    ASSERT_EQ(0, node.m_element);
    ASSERT_EQ(nullptr, node.m_pNext);
}