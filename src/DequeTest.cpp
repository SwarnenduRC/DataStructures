/**
 * @file DequeTest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DequeTest.h"

template<typename T>
void DequeTest::testDeque(std::deque<T>& refQ, Deque<T>& actualQ) const noexcept
{
    if (refQ.empty())
        return;
    
    ASSERT_EQ(refQ.size(), actualQ.size());
    EXPECT_EQ(refQ.front(), actualQ.front());
    EXPECT_EQ(refQ.back(), actualQ.back());
    refQ.pop_front();
    actualQ.pop_front();
    EXPECT_EQ(refQ.front(), actualQ.front());
    EXPECT_EQ(refQ.back(), actualQ.back());
    refQ.pop_back();
    actualQ.pop_back();
    EXPECT_EQ(refQ.front(), actualQ.front());
    EXPECT_EQ(refQ.back(), actualQ.back());
}

TEST_F(DequeTest, testDefaultConstructor)
{
    ASSERT_EQ(m_deque.size(), static_cast<size_t>(0));
    ASSERT_TRUE(m_deque.empty());
}

TEST_F(DequeTest, testParameterizedConstructor)
{
    Deque<int> deque = { 1, 2, 3, 4, 5, 6 };
    std::deque<int> refQ = { 1, 2, 3, 4, 5, 6 };
    testDeque(refQ, deque);
}

TEST_F(DequeTest, testCopy)
{
    Deque<int> deque = { 1, 2, 3, 4, 5, 6 };
    auto copyQueue = deque;
    std::deque<int> refQ = { 1, 2, 3, 4, 5, 6 };
    testDeque(refQ, copyQueue);
}

TEST_F(DequeTest, testAssignment)
{
    Deque<int> deque = { 1, 2, 3, 4, 5, 6 };
    std::deque<int> refQ = { 1, 2, 3, 4, 5, 6 };
    testDeque(refQ, deque);

    Deque<int> copyQueue = { 6, 5, 4, 3, 2, 1 };
    std::deque<int> refCopyQ = { 6, 5, 4, 3, 2, 1 };
    testDeque(refCopyQ, copyQueue);

    deque = copyQueue;
    testDeque(refCopyQ, deque);
}

TEST_F(DequeTest, testMove)
{
    Deque<int> deque = { 1, 2, 3, 4, 5, 6 };
    auto copyQueue = std::move(deque);

    ASSERT_EQ(deque.size(), static_cast<size_t>(0));
    ASSERT_TRUE(deque.empty());

    std::deque<int> refQ = { 1, 2, 3, 4, 5, 6 };
    testDeque(refQ, copyQueue);
}

TEST_F(DequeTest, testMoveAsignment)
{
    Deque<int> deque = { 1, 2, 3, 4, 5, 6 };
    Deque<int> copyQueue = { 66, 55, 44, 33, 22, 11 };
    copyQueue = std::move(deque);
    
    ASSERT_EQ(deque.size(), static_cast<size_t>(0));
    ASSERT_TRUE(deque.empty());

    std::deque<int> refCopyQ = { 1, 2, 3, 4, 5, 6 };
    testDeque(refCopyQ, copyQueue);
}

TEST_F(DequeTest, testAssignCount)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque, deque);
    deque.assign(10, 'b');
    refDeque.assign(10, 'b');
    testDeque(refDeque, deque);
}

TEST_F(DequeTest, testAssignIterator)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque, deque);
    std::string testStr(10, 'b');
    deque.assign(testStr.begin(), testStr.end());
    refDeque.assign(testStr.begin(), testStr.end());
    testDeque(refDeque, deque);
}

TEST_F(DequeTest, testAssignInitList)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque, deque);
    deque.assign({ 'b', 'c', 'd', 'f', 'g' });
    refDeque.assign({ 'b', 'c', 'd', 'f', 'g' });
    testDeque(refDeque, deque);
}

TEST_F(DequeTest, testSwap)
{
    Deque<char> deque1 = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque1 = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque1, deque1);

    Deque<char> deque2 = { 'b', 'c', 'd', 'f', 'g' };
    std::deque<char> refDeque2 = { 'b', 'c', 'd', 'f', 'g' };
    testDeque(refDeque2, deque2);

    deque1.swap(deque2);
    refDeque1.swap(refDeque2);

    testDeque(refDeque2, deque2);
    testDeque(refDeque1, deque1);
}

TEST_F(DequeTest, testResize)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque, deque);

    deque.resize(5);
    refDeque.resize(5);
    testDeque(refDeque, deque);

    deque.resize(3);
    refDeque.resize(3);
    testDeque(refDeque, deque);

    deque.resize(5);
    refDeque.resize(5);
    testDeque(refDeque, deque);
}

TEST_F(DequeTest, testResizeWithValue)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDeque(refDeque, deque);

    deque.resize(5, 'p');
    refDeque.resize(5, 'p');
    testDeque(refDeque, deque);

    deque.resize(3, 'p');
    refDeque.resize(3, 'p');
    testDeque(refDeque, deque);

    deque.resize(5, 'p');
    refDeque.resize(5, 'p');
    testDeque(refDeque, deque);
}
