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

template<typename T>
void DequeTest::testDequeViaIteration(std::deque<T>& refQ, Deque<T>& actualQ) const noexcept
{
    {
        auto qItr = actualQ.begin();
        auto refqItr = refQ.begin();
        while (qItr != actualQ.end() && refqItr != refQ.end())
        {
            EXPECT_EQ(*qItr, *refqItr);
            ++qItr;
            ++refqItr;
        }
        ASSERT_EQ(qItr, actualQ.end());
        ASSERT_EQ(refqItr, refQ.end());
    }
    {
        auto qItr = actualQ.rbegin();
        auto refqItr = refQ.rbegin();
        while (qItr != actualQ.rend() && refqItr != refQ.rend())
        {
            EXPECT_EQ(*qItr, *refqItr);
            ++qItr;
            ++refqItr;
        }
        ASSERT_EQ(qItr, actualQ.rend());
        ASSERT_EQ(refqItr, refQ.rend());
    }
    {
        auto qItr = actualQ.cbegin();
        auto refqItr = refQ.cbegin();
        while (qItr != actualQ.cend() && refqItr != refQ.cend())
        {
            EXPECT_EQ(*qItr, *refqItr);
            ++qItr;
            ++refqItr;
        }
        ASSERT_EQ(qItr, actualQ.cend());
        ASSERT_EQ(refqItr, refQ.cend());
    }
    {
        auto qItr = actualQ.crbegin();
        auto refqItr = refQ.crbegin();
        while (qItr != actualQ.crend() && refqItr != refQ.crend())
        {
            EXPECT_EQ(*qItr, *refqItr);
            ++qItr;
            ++refqItr;
        }
        ASSERT_EQ(qItr, actualQ.crend());
        ASSERT_EQ(refqItr, refQ.crend());
    }
    {
        auto refqItr = refQ.rbegin();
        for (auto itr = actualQ.rbegin(); itr != actualQ.rend() && refqItr != refQ.rend(); ++itr, ++refqItr)
            EXPECT_EQ(*itr, *refqItr);
    }
    {
        auto refqItr = refQ.begin();
        for (auto itr = actualQ.begin(); itr != actualQ.end() && refqItr != refQ.end(); ++itr, ++refqItr)
            EXPECT_EQ(*itr, *refqItr);
    }
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

TEST_F(DequeTest, testComparisonOperators)
{
    {
        Deque<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Deque<int> queue2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        EXPECT_TRUE(queue1 == queue2);
        EXPECT_FALSE(queue1 != queue2);
    }
    {
        Deque<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Deque<int> queue2 = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        EXPECT_FALSE(queue1 == queue2);
        EXPECT_TRUE(queue1 != queue2);
    }
    {
        Deque<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Deque<int> queue2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2 };
        EXPECT_FALSE(queue1 == queue2);
        EXPECT_TRUE(queue1 != queue2);
    }
}

TEST_F(DequeTest, testIterators)
{
    Deque<char> deque = { 'a', 'e', 'i', 'o', 'u' };
    std::deque<char> refDeque = { 'a', 'e', 'i', 'o', 'u' };
    testDequeViaIteration(refDeque, deque);

    deque.resize(5, 'p');
    refDeque.resize(5, 'p');
    testDequeViaIteration(refDeque, deque);

    deque.resize(3, 'p');
    refDeque.resize(3, 'p');
    testDequeViaIteration(refDeque, deque);

    deque.resize(5, 'p');
    refDeque.resize(5, 'p');
    testDequeViaIteration(refDeque, deque);
}
