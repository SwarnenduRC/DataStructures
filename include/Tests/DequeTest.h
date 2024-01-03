/**
 * @file DequeTest.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Deque.h"

#include <gtest/gtest.h>
#include <deque>

using swarnendu::Deque;

class DequeTest : public ::testing::Test
{
    public:
        template<typename T>
        void testDeque(std::deque<T>& refQ, Deque<T>& actualQ) const noexcept;

        template<typename T>
        void testDequeViaIteration(std::deque<T>& refQ, Deque<T>& actualQ) const noexcept;
        
    protected:
        Deque<int> m_deque;
};