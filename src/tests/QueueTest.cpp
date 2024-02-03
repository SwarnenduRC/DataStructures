#include "QueueTest.h"

TEST_F(QueueTest, testDefaultConstructor)
{
    ASSERT_EQ(m_queue.size(), static_cast<size_t>(0));
    ASSERT_TRUE(m_queue.empty());
    EXPECT_THROW(m_queue.back(), std::out_of_range);
    EXPECT_THROW(m_queue.front(), std::out_of_range);
}

TEST_F(QueueTest, testParameterizedConstructor)
{
    Queue<int> queue = {1, 2, 3, 4, 5, 6};
    std::queue<int> refQ;
    for (auto val = 1; val <= 6; ++val)
        refQ.push(val);

    testQueue(refQ, queue);
}

TEST_F(QueueTest, testCopy)
{
    Queue<int> queue = {1, 2, 3, 4, 5, 6};
    auto copyQueue = queue;
    std::queue<int> refQ;
    for (auto val = 1; val <= 6; ++val)
        refQ.push(val);

    testQueue(refQ, copyQueue);
}

TEST_F(QueueTest, testAssignment)
{
    Queue<int> queue = {1, 2, 3, 4, 5, 6};
    std::queue<int> refQ;
    for (auto val = 1; val <= 6; ++val)
        refQ.push(val);

    Queue<int> copyQueue = {6, 5, 4, 3, 2, 1};
    copyQueue = queue;
    std::queue<int> refCopyQ;
    for (auto val = 1; val <= 6; ++val)
        refCopyQ.push(val);

    testQueue(refCopyQ, queue);
    testQueue(refQ, copyQueue);
}

TEST_F(QueueTest, testMove)
{
    Queue<int> queue = {1, 2, 3, 4, 5, 6};
    auto copyQueue = std::move(queue);

    ASSERT_EQ(queue.size(), static_cast<size_t>(0));
    ASSERT_TRUE(queue.empty());
    EXPECT_THROW(queue.back(), std::out_of_range);
    EXPECT_THROW(queue.front(), std::out_of_range);

    std::queue<int> refQ;
    for (auto val = 1; val <= 6; ++val)
        refQ.push(val);

    testQueue(refQ, copyQueue);
}

TEST_F(QueueTest, testMoveAsignment)
{
    Queue<int> queue = {1, 2, 3, 4, 5, 6};
    Queue<int> copyQueue = {66, 55, 44, 33, 22, 11};
    copyQueue = std::move(queue);
    
    ASSERT_EQ(queue.size(), static_cast<size_t>(0));
    ASSERT_TRUE(queue.empty());
    EXPECT_THROW(queue.back(), std::out_of_range);
    EXPECT_THROW(queue.front(), std::out_of_range);

    std::queue<int> refQ;
    for (auto val = 1; val <= 6; ++val)
        refQ.push(val);

    testQueue(refQ, copyQueue);
}

TEST_F(QueueTest, testSwapAndFind)
{
    Queue<int> queue1 = { 1, 2, 3, 4, 5, 6 };
    Queue<int> queue2 = { 61, 62, 63, 64, 65, 66 };

    EXPECT_TRUE(queue1.find(3));
    EXPECT_TRUE(queue2.find(63));
    EXPECT_FALSE(queue1.find(63));
    EXPECT_FALSE(queue2.find(3));

    queue1.swap(queue2);

    EXPECT_TRUE(queue2.find(3));
    EXPECT_TRUE(queue1.find(63));
    EXPECT_FALSE(queue2.find(63));
    EXPECT_FALSE(queue1.find(3));

    std::queue<int> refQ1;
    for (auto val = 1; val <= 6; ++val)
        refQ1.push(val);

    testQueue(refQ1, queue2);

    std::queue<int> refQ2;
    for (auto val = 61; val <= 66; ++val)
        refQ2.push(val);

    testQueue(refQ2, queue1);
}

TEST_F(QueueTest, testComparisonOperators)
{
    {
        Queue<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Queue<int> queue2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        EXPECT_TRUE(queue1 == queue2);
        EXPECT_FALSE(queue1 != queue2);
    }
    {
        Queue<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Queue<int> queue2 = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        EXPECT_FALSE(queue1 == queue2);
        EXPECT_TRUE(queue1 != queue2);
    }
    {
        Queue<int> queue1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        Queue<int> queue2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2 };
        EXPECT_FALSE(queue1 == queue2);
        EXPECT_TRUE(queue1 != queue2);
    }
}

/**
 * front, back, clear, pop etc methods
 * are tested through either testQueue
 * functions or via various constructor
 * and assignment tests thus not testing
 * here explictly.
 */

