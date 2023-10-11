#include "Queue.h"

#include <gtest/gtest.h>
#include <queue>

using swarnendu::Queue;

class QueueTest : public ::testing::Test
{
    public:
        void testQueue(std::queue<int>& refQ, Queue<int>& actualQ)
        {
            if (refQ.empty())
                return;
            
            ASSERT_EQ(refQ.size(), actualQ.size());
            EXPECT_EQ(refQ.front(), actualQ.front());
            EXPECT_EQ(refQ.back(), actualQ.back());
            refQ.pop();
            actualQ.pop();
            EXPECT_EQ(refQ.front(), actualQ.front());
            EXPECT_EQ(refQ.back(), actualQ.back());
            refQ.push(55);
            actualQ.push(55);
            EXPECT_EQ(refQ.front(), actualQ.front());
            EXPECT_EQ(refQ.back(), actualQ.back());
        }
    protected:
        Queue<int> m_queue;
};