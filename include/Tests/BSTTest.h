#include "BSTree.h"

#include <gtest/gtest.h>
#include <vector>

using swarnendu::BSTree;
using IntVector = std::vector<int>;

class BSTTest : public ::testing::Test
{
    public:
        IntVector getRandomNumbers(const int cnt, const int offset, const int range);
        IntVector getElementsPreOrder(const BSTree<int>& tree) const noexcept;
        IntVector getElementsInOrder(const BSTree<int>& tree) const noexcept;
        IntVector getElementsPostOrder(const BSTree<int>& tree) const noexcept;
        IntVector getLeftView(const BSTree<int>& tree) const noexcept;
        IntVector getRightView(const BSTree<int>& tree) const noexcept;
        std::map<int, int> getTopView(const BSTree<int>& tree) const noexcept;
        void testBalancedBST(const BSTree<int>& tree) const noexcept;
        void testTree(const BSTree<int>& tree) const noexcept;
    protected:
        BSTree<int> m_BST;        
};