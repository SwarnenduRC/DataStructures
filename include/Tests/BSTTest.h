#include "BSTree.h"

#include <gtest/gtest.h>
#include <vector>

using swarnendu::BSTree;
using IntVector = std::vector<int>;

class BSTTest : public ::testing::Test
{
    public:
        IntVector getRandomNumbers(const int cnt, const int offset, const int range);
        IntVector getElementsPreOrder() const noexcept;
        IntVector getElementsInOrder() const noexcept;
        IntVector getElementsPostOrder() const noexcept;
    protected:
        BSTree<int> m_BST;        
};