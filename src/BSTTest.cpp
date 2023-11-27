#include "BSTTest.h"

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


