/**
 * @file BSTree.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Nodes.h"

#include <algorithm>
#include <initializer_list>
#include <vector>
#include <list>
#include <queue>
#include <stack>

namespace swarnendu
{
    using swarnendu_nodes::TreeNode;

    template<typename T>
    class BSTree
    {
        public:
            BSTree() = default;
            BSTree(const std::initializer_list<T>& initList) noexcept
                : m_pRoot(nullptr)
                , m_size(0)
                , m_height(0)
            {
                if (initList.size())
                {
                    std::vector<T> vec(initList);
                    std::sort(vec.begin(), vec.end());  //Sort it so that a balanced BST can be constructed out of it
                    m_pRoot.reset(constructBalancedBST(vec, 0, static_cast<int>(initList.size() - 1)));
                    m_size = initList.size();
                    m_height = calculateHeight(m_pRoot);
                }
            }
            ~BSTree() = default;
            BSTree(const BSTree& rhs) noexcept
                : m_pRoot(std::make_unique<TreeNode<T>>(*rhs.m_pRoot))
                , m_size(rhs.m_size)
                , m_height(rhs.m_height)
            {
            }
            BSTree& operator=(const BSTree& rhs) noexcept
            {
                if (this != &rhs)
                {
                    if (!empty())
                        clear();

                    if (!rhs.empty())
                        copy(rhs);
                }
                return *this;
            }
            BSTree(BSTree&& rhs) noexcept
                : m_pRoot(std::move_if_noexcept(rhs.m_pRoot))
                , m_size(std::move_if_noexcept(rhs.m_size))
                , m_height(std::move_if_noexcept(rhs.m_height))
            {
                rhs.m_height = 0;
                rhs.m_size = 0;
            }
            BSTree& operator=(BSTree&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    if (!rhs.empty())
                    {
                        m_pRoot = std::move_if_noexcept(rhs.m_pRoot);
                        m_size = std::move_if_noexcept(rhs.m_size);
                        m_height = std::move_if_noexcept(rhs.m_height);

                        rhs.m_height = 0;
                        rhs.m_size = 0;
                    }
                }
                return *this;
            }
            /**
             * @brief Clears the tree.
             *        It clears out the tree and set both the height
             *        and size of the tree to zero
             */
            void clear() noexcept 
            { 
                clearTree(m_pRoot);
                m_size = 0;
                m_height = 0;
            }
            /**
             * @brief Insert an element into the BST.
             *        It internally calls insertItem
             *        to insert the item for an non empty
             *        BST. 
             * 
             * @see insertItem for more details
             * 
             * @param val The element to be inserted
             * @return true If the insertion was successful,
             * @return false If the insertion was unsuccessful
             */
            [[nodiscard]] bool insert(const T& val)
            {
                if (find(val))
                    return false; //A BST can't have duplicate items

                if (!m_pRoot)   //BST is empty so this is the first element
                {
                    m_pRoot = std::make_unique<TreeNode<T>>(val);
                    m_size = 1;
                    m_height = 1;
                    return true;
                }
                else    //BST isn't empty
                {
                    if (insertItem(val, m_pRoot))
                    {
                        m_size += 1;
                        m_height = calculateHeight(m_pRoot);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            /**
             * @brief Erase an element (if present) from the BST.
             *        It internally calls eraseElement to erase the value.
             * 
             * @param val The value to be erased
             * @return true If erase is successful,
             * @return false If erase is unsuccessful
             * @see eraseElement for more details
             */
            [[nodiscard]] bool erase(const T& val)
            {
                if (!find(val))
                    return false;

                auto bErased = eraseElement(val, m_pRoot);
                if (bErased)
                {
                    m_size -= 1;
                    m_height = calculateHeight(m_pRoot);   // Recalculate the tree's height after deletion
                }
                return bErased;
            }
            /**
             * @brief   Finds an element in the BST (if present).
             *          Internally call findElement to find the element.
             * 
             * @param val The value to be searched for
             * @return TreeNode* The node pointer containing the data. nullptr
             *                   if not found
             */
            [[nodiscard]] TreeNode<T>* find(const T& val) const noexcept
            {
                if (!m_pRoot)
                    return nullptr;

                return findElement(val, m_pRoot);
            }
            /**
             * @brief Copies a given BST into the current one
             *        Internally calls copyTreePreOrder to copy
             *        over the elements in a preorder traversal
             * 
             * @see   copyTreePreOrder formore details
             * 
             * @param rhs The source tree to be copied
             */
            void copy(const BSTree& rhs)
            {
                clear();
                if (!rhs.empty())
                {
                    m_pRoot.reset(new TreeNode<T>(rhs.m_pRoot->getData()));
                    copyTreePreOrder(rhs.m_pRoot, m_pRoot);
                    m_size = rhs.size();
                    m_height = rhs.height();
                }
            }
            inline size_t size() const noexcept { return m_size; }
            inline size_t height() const noexcept { return m_height; }
            inline bool empty() const noexcept { return m_size == 0; }
            inline TreeNode<T>* getRoot() const noexcept { return m_pRoot.get(); }

        private:
            /**
             * @brief Inserts an item into a non empty BST.
             *        It is basically a preorder traversal
             *        of the BST which first checks for left
             *        subtree of the given node to insert the item
             *        then the right sub tree. The root is already 
             *        checked in insert method
             * 
             * @see   insert for more details
             * 
             * @param val The item to be inserted
             * @param pRoot The root of the tree/sub tree
             * @return true If insertion was successful,
             * @return false If insertion was unsuccessful
             */
            [[nodiscard]] bool insertItem(const T& val, std::unique_ptr<TreeNode<T>>& pRoot)
            {
                if (val < pRoot->m_data)   //The item should be at the left of the given node
                {
                    if (pRoot->m_pLeft)
                    {
                        return insertItem(val, pRoot->m_pLeft);
                    }
                    else
                    {
                        pRoot->m_pLeft = std::make_unique<TreeNode<T>>(val);
                        return true;
                    }
                }
                else if (val > pRoot->m_data)   //The item should be at the right of the given root
                {
                    if (pRoot->m_pRight)
                    {
                        return insertItem(val, pRoot->m_pRight);
                    }
                    else
                    {
                        pRoot->m_pRight = std::make_unique<TreeNode<T>>(val);
                        return true;
                    }
                }
                else    //Duplicate value so can't be inserted
                {
                    return false;
                }
            }
            /**
             * @brief It clears out either the entire tree
             *        along with its left and right sub trees.
             *        It is basically a post-order traversal
             *        which first clears out the left subtree
             *        of the given root, then the right subtree
             *        and finally the root itself. Recursive in 
             *        nature
             * 
             * @param pRoot The root of the tree/sub tree
             */
            void clearTree(std::unique_ptr<TreeNode<T>>& pRoot) noexcept
            {
                //The root of the tree is NULL already so return straightaway
                if (!pRoot)
                    return;

                //Clear the left subtree if present
                if (pRoot->m_pLeft)
                    clearTree(pRoot->m_pLeft);
                //Clear the right subtree if present
                if (pRoot->m_pRight)
                    clearTree(pRoot->m_pRight);

                //Both the left and right subtree of the given root is cleared
                //so ready to clear the root node now
                pRoot.reset();
            }
            /**
             * @brief Erases an element from the BST.
             *        It erases an element from the BST by recusively
             *        finding it in the tree against the respective
             *        root node of the given tree. Highly recusive
             *        in nature.
             * 
             * @param val   The value which is to be deleted
             * @param pRoot The respective root node of the tree/sub tree
             * @return true If the element is found and deleted successfully,
             * @return false If the element can not be deleted
             */
            [[nodiscard]] bool eraseElement(const T& val, std::unique_ptr<TreeNode<T>>& pRoot)
            {
                if (val == pRoot->m_data)   //Node to be deleted found
                {
                    //Case1: The node to be deleted is a leaf node
                    if (!pRoot->m_pLeft && !pRoot->m_pRight)
                    {
                        pRoot.reset();
                        return true;
                    }
                    //Case2: The node to be deleted has only left sub tree
                    else if (pRoot->m_pLeft && !pRoot->m_pRight)
                    {
                        auto pLeft = std::move(pRoot->m_pLeft);
                        pRoot.reset();
                        pRoot = std::move(pLeft);
                        return true;
                    }
                    //Case3: The node to be deleted has only right sub tree
                    else if (!pRoot->m_pLeft && pRoot->m_pRight)
                    {
                        auto pRight = std::move(pRoot->m_pRight);
                        pRoot.reset();
                        pRoot = std::move(pRight);
                        return true;
                    }
                    //Case4: The node to be deleted has both left and right sub trees
                    else
                    {
                        /**
                         * In this case the node to be deleted can either be replaced 
                         * by it's inorder successor or inorder predessor to maintain
                         * the property of the BST.
                         */
                        pRoot->m_data = std::move(findInorderSuccessor(pRoot->m_pRight));
                        return true;
                    }
                }
                else if (val > pRoot->m_data)   //Node resides in the right half of the root node
                {
                    return eraseElement(val, pRoot->m_pRight);
                }
                else if (val < pRoot->m_data)   //Node resides in the left half of the root node
                {
                    return eraseElement(val, pRoot->m_pLeft);
                }
                else    //Node is not found (shouldn't hit this case if been called from erase())
                {
                    return false;
                }
            }
            /**
             * @brief Find an element in a tree/sub tree and returns the node
             *        pointer which contains it (if present).
             * 
             * @param val   The value to be searched for.
             * @param pRoot The root of the tree/sub tree in which the element
             *              would be searched.
             * @return TreeNode* The node pointer containing the data. nullptr
             *                   if not found
             */
            [[nodiscard]] TreeNode<T>* findElement(const T& val, const std::unique_ptr<TreeNode<T>>& pRoot) const noexcept
            {
                if (!pRoot)
                    return nullptr;

                if (val == pRoot->m_data)
                    return pRoot.get();

                if (val < pRoot->m_data && pRoot->m_pLeft)
                    return findElement(val, pRoot->m_pLeft);
                else if (val > pRoot->m_data && pRoot->m_pRight)
                    return findElement(val, pRoot->m_pRight);
                else
                    return nullptr;
            }

            /**
             * @brief Calcualtes the height of a tree/sub-tree for the given node
             *        The height of a binary tree is calculated by height of it's
             *        left sub-tree or right sub-tree (whichever is the biggest)
             *        plus the root node itself. Recursive in nature.
             * 
             * @param pRoot The root of the tree/sub-tree for which the height would be calculated 
             * @return size_t The calculated height. Return value can not be discarded.
             */
            [[nodiscard]] size_t calculateHeight(const std::unique_ptr<TreeNode<T>>& pRoot) const noexcept
            {
                if (!pRoot)
                    return 0;

                size_t leftTreeHeight = 0;
                size_t rightTreeHeight = 0;
                if (pRoot->m_pLeft)
                    leftTreeHeight = calculateHeight(pRoot->m_pLeft);

                if (pRoot->m_pRight)
                    rightTreeHeight = calculateHeight(pRoot->m_pRight);

                auto height = 1 + std::max(leftTreeHeight, rightTreeHeight);
                return height;
            }
            /**
             * @brief Finds inorder successor of a node. Once found it
             *        it returns the value of the node and deletes it from
             *        the tree/sub tree
             * 
             * @param pRightTreeNode The node to the right of the node for
             *                       which the inorder successor is to be found.
             * @return T The inorder successor value.
             */
            T findInorderSuccessor(std::unique_ptr<TreeNode<T>>& pRightTreeNode) noexcept
            {
                if (pRightTreeNode)
                {
                    if (pRightTreeNode->m_pLeft)
                    {
                        return std::move(findInorderSuccessor(pRightTreeNode->m_pLeft));
                    }
                    else
                    {
                        auto retVal = std::move(pRightTreeNode->m_data);
                        pRightTreeNode.reset();
                        return std::move(retVal);
                    }
                }
                return T{};
            }
            /**
             * @brief Finds inorder predecessor of a node. Once found it
             *        it returns the value of the node and deletes it from
             *        the tree/sub tree
             * 
             * @param pLeftTreeRoot The node to the left of the node for
             *                       which the inorder successor is to be found.
             * @return T The inorder predecessor value.
             */
            T findInorderPredecessor(std::unique_ptr<TreeNode<T>>& pLeftTreeRoot) noexcept
            {
                if (pLeftTreeRoot)
                {
                    if (pLeftTreeRoot->m_pRight)
                    {
                        return std::move(findInorderPredecessor(pLeftTreeRoot->m_pRight));
                    }
                    else
                    {
                        auto retVal = std::move(pLeftTreeRoot->m_data);
                        pLeftTreeRoot.reset();
                        return std::move(retVal);
                    }
                }
                return T{};
            }
            /**
             * @brief Copies a BST into another in a preorder traversal fashion.
             *        Recursive in nature
             * 
             * @param pSrcRoot Root of the source tree
             * @param pDestRoot Root of the destination tree
             */
            void copyTreePreOrder(const std::unique_ptr<TreeNode<T>>& pSrcRoot, std::unique_ptr<TreeNode<T>>& pDestRoot)
            {
                if (pSrcRoot->m_pLeft)
                {
                    pDestRoot->m_pLeft = std::make_unique<TreeNode<T>>(pSrcRoot->m_pLeft->m_data);
                    copyTreePreOrder(pSrcRoot->m_pLeft, pDestRoot->m_pLeft);
                }
                if (pSrcRoot->m_pRight)
                {
                    pDestRoot->m_pRight = std::make_unique<TreeNode<T>>(pSrcRoot->m_pRight->m_data);
                    copyTreePreOrder(pSrcRoot->m_pRight, pDestRoot->m_pRight);
                }
            }
            /**
             * @brief Constructs a balanced BST out of the list/vector.
             *        Recursive in nature.
             * 
             * @param vec The list of elements (preferbly in a vector)
             * @param startIdx The starting index of the vector
             * @param endIdx The ending index of the vector
             * @return TreeNodePtr The constructed root
             */
            TreeNode<T>* constructBalancedBST(const std::vector<T>& vec, const int startIdx, const int endIdx)
            {
                if (startIdx > endIdx)
                    return nullptr;

                auto midIdx = startIdx + (endIdx - startIdx) / 2;
                auto pRoot = new TreeNode<T>(vec[midIdx]);
                pRoot->m_pLeft.reset(constructBalancedBST(vec, startIdx, (midIdx - 1)));
                pRoot->m_pRight.reset(constructBalancedBST(vec, (midIdx + 1), endIdx));                
                return pRoot;
            }

            /**
             * @brief Members
             * [m_pRoot] Root of the BST
             * [m_size] Size of the BST
             * [m_height] Height of the BST
             */
            std::unique_ptr<TreeNode<T>> m_pRoot = nullptr;
            size_t m_size = 0;
            size_t m_height = 0;
    };
    
}   //namespace swarnendu

