#include "BSTree.h"

#include <gtest/gtest.h>
#include <vector>

using swarnendu::BSTree;
using IntVector = std::vector<int>;

class BSTTest : public ::testing::Test
{
    public:
        IntVector getRandomNumbers(const int cnt, const int offset, const int range)
        {
            if (offset < 0 || range < 0)
                return IntVector{};

            IntVector vec;
            for (auto idx = 0; idx < cnt; ++idx)
                vec.emplace_back(offset + (rand() % range));

            return vec;
        }
    protected:
        BSTree<int> m_BST;        
};