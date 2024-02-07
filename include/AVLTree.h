#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "Nodes.h"
#include "DoublyLinkedList.h"

using swarnendu_nodes::AVL_TreeNode;

namespace swarnendu
{
    template<typename T>
    class AVLTree
    {
        public:
            using TNode = AVL_TreeNode<T>;
            using TNodePtr = std::unique_ptr<TNode>;
            using DList = swarnendu::DoublyLinkedList<TNode*>;

            /**
             * @brief Custom iterator structure for AVL tree.
             *        It is a custom iterator which will enable the
             *        traversal of the AVL tree much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             *
             */
            struct iterator
            {
                public:
                    /**
                     * @brief Some pre conditions which defines the
                     *        types and nature of this iterator
                     *
                     */
                    using iterator_category = std::bidirectional_iterator_tag;
                    using value_type = T;
                    using pointer = TNode*;
                    using reference = value_type&;
                    using const_pointer = const TNode*;
                    using const_reference = const value_type&;

                    iterator(pointer pNode)
                    {
                        if (pNode)
                        {
                            pouplateList(pNode);
                            m_listItr = m_list.begin();
                        }
                    }
                    iterator() = default;
                    ~iterator() = default;
                    iterator(const iterator&) = default;
                    iterator& operator=(const iterator&) = default;
                    iterator(iterator&&) = default;
                    iterator& operator=(iterator&&) = default;

                    /**
                     * @brief Post increment operator
                     *
                     * @return iterator Incremented iterator
                     */
                    iterator operator++(const int) noexcept
                    {
                        iterator temp = *this;
                        m_listItr++;
                        return temp;
                    }
                    /**
                     * @brief Pre increment operator
                     *
                     * @return iterator Incremented iterator
                     */
                    iterator& operator++() noexcept
                    {
                        ++m_listItr;
                        return *this;
                    }
                    /**
                     * @brief Post decrement operator
                     *
                     * @return iterator Decremented operator
                     */
                    iterator operator--(const int) noexcept
                    {
                        iterator temp = *this;
                        m_listItr--;
                        return temp;
                    }
                    /**
                     * @brief Pre decrement operator
                     *
                     * @return iterator Decremented operator
                     */
                    iterator& operator--() noexcept
                    {
                        --m_listItr;
                        return *this;
                    }
                    /**
                     * @brief Comparison operator
                     *        Compares two ietrators for equality
                     *
                     * @param rhs The righ side object
                     * @return true If the two iterators are equal, otherwise
                     * @return false 
                     */
                    bool operator==(const iterator& rhs) const noexcept
                    {
                        return (m_listItr == rhs.m_listItr);
                    }
                    /**
                     * @brief Comparison operator
                     *        Compares two ietrators for equality
                     *
                     * @param rhs The righ side object
                     * @return true If the two iterators are not equal, otherwise
                     * @return false 
                     */
                    bool operator!=(const iterator& rhs) const noexcept
                    {
                        return (m_listItr != rhs.m_listItr);
                    }
                    reference operator*() const noexcept  { auto& val = m_listItr->getData()->m_data; return val; }
                    pointer operator->()  const noexcept  { return m_listItr->getData(); }

                protected:
                    /**
                     * @brief Populates the doubly linked list
                     *        This method is the most crucial method
                     *        for the iterator class to work effectively.
                     *        Recursive in nature.
                     *
                     * @param pNode Root node of the tree
                     */
                    void pouplateList(pointer pNode)
                    {
                        /**
                         * @brief The enitre iterator functionalities class for the AVL tree
                         * rests with this method. Following is the shorthand description how
                         * this iterator class iterates over the AVL tree
                         *
                         * First point to be remembered is that an inorder traversal of a BST
                         * gives us the elements of that tree in a sorted (ascending) order. So
                         * when an user asks for an iterator and performs increment or decrement
                         * operation on that s/he basically performs an inorder traversal on that
                         * tree.
                         *
                         * In this iterator class we take the root node (or any node of its subtrees')
                         * in the begin/find function of the tree and we fill our doubly linked list
                         * structure before hand by doing an inorder traversal on that root node. Once
                         * the list is filled we just take an iterator on that list and we increment and/or
                         * decrement that to traverse through the elements of the tree. Another catch here
                         * is that we take the pointer to the values in the tree so that any changes in the
                         * tree value gets reflected in the list as well.
                         */
                        if (pNode)
                        {
                            if (pNode->m_pLeft)
                                pouplateList(pNode->m_pLeft.get());

                            m_list.push_back(pNode);

                            if (pNode->m_pRight)
                                pouplateList(pNode->m_pRight.get());
                        }
                    }
                    /**
                     * @brief
                     *
                     */
                public:
                    DList m_list;
                protected:
                    DList::iterator m_listItr;
                    pointer m_pNode = nullptr;
            };

            inline iterator begin() noexcept
            {
                m_selfItr = iterator(m_pRoot.get());
                return m_selfItr;
            }
            inline iterator end() const noexcept { return iterator(); }

            AVLTree() = default;
            ~AVLTree() = default;
            AVLTree(const std::initializer_list<T>& iList) noexcept
                : m_pRoot(nullptr)
                , m_size(0)
            {
                if (iList.size())
                {
                    for (const auto& item : iList)
                        insert(item);
                }
            }
            AVLTree(const AVLTree& rhs) noexcept
                : m_pRoot(std::make_unique<TNode>(*rhs.m_pRoot))
                , m_size(rhs.m_size)
            {}
            AVLTree(AVLTree&& rhs) noexcept
                : m_pRoot(std::move_if_noexcept(rhs.m_pRoot))
                , m_size(rhs.m_size)
            {
                rhs.m_size = 0;
            }
            AVLTree& operator=(const AVLTree& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    m_pRoot.reset(new TNode(*rhs.m_pRoot.get()));
                    m_size = rhs.m_size;
                }
                return *this;
            }
            AVLTree& operator=(AVLTree&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    m_pRoot = std::move_if_noexcept(rhs.m_pRoot);
                    m_size = rhs.m_size;
                    rhs.m_size = 0;
                }
                return *this;
            }
            /**
             * @brief Checks if the tree is empty or not
             * 
             * @return true If the tree is empty,
             * @return false If the tree is not empty
             */
            inline bool empty() const noexcept { return m_size == 0; }
            /**
             * @brief Returns the size of the tree, i.e.; total nodes in the tree
             * 
             * @return size_t The size of the tree
             */
            inline size_t size() const noexcept { return m_size; }
            /**
             * @brief Checks if the given value is present in the tree or not
             * 
             * @param val The value to be searched for
             * @return true If the value is there in the tree, 
             * @return false otherwise
             */
            inline bool find(const T& val) const noexcept
            {
                if (!empty())
                    return find(val, m_pRoot);
                else
                    return false;
            }
            /**
             * @brief Inserts an element into the tree.
             *        It inserts an element into the tree,
             *        Does nothing if the element to be inserted
             *        is a duplicate one. Recursive in nature.
             * 
             * @param val The value to be inserted
             */
            inline void insert(const T& val)
            {
                if (find(val))  //Duplicate value, just return
                    return;
                
                if (empty())    //The tree is empty so welcome the first member of the family
                {
                    m_pRoot = std::make_unique<TNode>(val);
                    updateIteratorCacheForInsert(m_pRoot->getData(), false, m_pRoot.get());
                }
                /**
                 * @brief The tree is not empty and the value to be inserted
                 *        should be at the right side of the root node
                 */
                else if (val > m_pRoot->getData())
                {
                    if (m_pRoot->m_pRight)  //Root node has right child/children so check with them
                    {
                        insert(val, m_pRoot->m_pRight);
                    }
                    else
                    {
                        m_pRoot->m_pRight = std::make_unique<TNode>(val);   //Root welcomes its first right child. Mazeltov :-)
                        updateIteratorCacheForInsert(m_pRoot->getData(), true, m_pRoot->m_pRight.get());
                    }
                }
                /**
                 * @brief The tree is not empty and the value to be inserted
                 *        should be at the left side of the root node
                 */
                else if (val < m_pRoot->getData())
                {
                    if (m_pRoot->m_pLeft)   //Root node has left child/children so check with them
                    {
                        insert(val, m_pRoot->m_pLeft);
                    }
                    else
                    {
                        m_pRoot->m_pLeft = std::make_unique<TNode>(val);    //Root welcomes its first left child. Mazeltov :-)
                        updateIteratorCacheForInsert(m_pRoot->getData(), false, m_pRoot->m_pLeft.get());
                    }
                }
                // If you are hitting this else condition you need some serious introspection MAN!!
                else
                {
                    return;
                }
                m_pRoot->updateHeight();
                m_pRoot->updateBalanceFactor();
                ++m_size;
                balanceNodeTree(m_pRoot);
            }
            /**
             * @brief Erases an element from the tree
             *        It erases an element from the tree
             *        if it is there. Does nothing if the
             *        element is not there in the tree but
             *        shows superficial respect to honor the
             *        client's request. Recursive in nature.
             * 
             * @param val The value to be erased
             */
            inline void erase(const T& val) noexcept
            {
                if (empty() || !find(val))
                    return;

                auto updateOnly = false;
                eraseElement(val, m_pRoot, updateOnly);
            }
            /**
             * @brief Clears the tree in its entireity
             * 
             */
            inline void clear()
            {
                if (empty())    //The tree is empty so nothing to be done
                    return;

                clearTree(m_pRoot);     //Clear the tree
                m_size = 0;
            }
            /**
             * @brief The following methods are only for debugging purposes and need
             *        to be moved to private scope once the development is done
             */
            inline int getTreeHeight() const noexcept { return m_pRoot->getNodeHeight(); }
            inline int getNodeBalanceFactor(const TNodePtr& pNode) const noexcept { return pNode->getBalanceFactor(); }
            inline TNodePtr& getRootNode() noexcept { return m_pRoot; }
            inline void applyLeftRotation(TNodePtr& pNode, const bool selfBalance) noexcept
            {
                pNode = std::move(rotateLeft(pNode));
                if (selfBalance)
                    balanceNodeTree(pNode);
            }
            inline void applyRightRotation(TNodePtr& pNode, const bool selfBalance) noexcept
            {
                pNode = std::move(rotateRight(pNode));
                if (selfBalance)
                    balanceNodeTree(pNode);
            }
            void checkBalanceFactor(const TNodePtr& pNode) const
            {
                if (pNode->m_pLeft)
                {
                    checkBalanceFactor(pNode->m_pLeft);
                }
                if (pNode->m_pRight)
                {
                    checkBalanceFactor(pNode->m_pRight);
                }
                auto balFact = pNode->getBalanceFactor();
                if (balFact < -1 || balFact > 1)
                    throw std::logic_error("The tree is not balanced");
            }
        
        private:
            /**
             * @brief Rotates a given node to left
             *        It left rotates a given node
             *        with respect to its children
             * 
             * @param pNode The node to be rotated
             * @return TNodePtr The new node after rotation applied
             */
            inline TNodePtr rotateLeft(TNodePtr& pNode) noexcept
            {
                auto pRightChild = std::move(pNode->m_pRight);
                auto pRightChildsLeft = std::move(pRightChild->m_pLeft);
                pNode->calculateHeight();
                pNode->calculateBalanceFactor();
                pRightChild->m_pLeft = std::move(pNode);
                pRightChild->m_pLeft->m_pRight = std::move(pRightChildsLeft);
                pRightChild->updateHeight();
                pRightChild->updateBalanceFactor();
                return std::move(pRightChild);
            }
            /**
             * @brief Rotates a given node to right
             *        It right rotates a given node
             *        with respect to its children
             * 
             * @param pNode The node to be rotated
             * @return TNodePtr The new node after rotation applied
             */
            inline TNodePtr rotateRight(TNodePtr& pNode) noexcept
            {
                auto pLeftChild = std::move(pNode->m_pLeft);
                auto pLeftChildsRight = std::move(pLeftChild->m_pRight);
                pNode->calculateHeight();
                pNode->calculateBalanceFactor();
                pLeftChild->m_pRight = std::move(pNode);
                pLeftChild->m_pRight->m_pLeft = std::move(pLeftChildsRight);
                pLeftChild->updateHeight();
                pLeftChild->updateBalanceFactor();
                return std::move(pLeftChild);
            }
            /**
             * @brief Inserts an element into the tree pointed by the node given
             *        It insertes a value into the tree considering the given
             *        node in the parameter is the root node for that tree.
             *        Rescursive in nature.
             * @param val The value to be inserted.
             * @param pRoot The root node of the tree
             */
            inline void insert(const T& val, TNodePtr& pRoot)
            {
                if (val > pRoot->getData())     // The value should be at the right side of this node
                {
                    //The root node has right child so call it recursively now with the right child as new root node
                    if (pRoot->m_pRight)
                    {
                        insert(val, pRoot->m_pRight);
                    }
                    else
                    {
                        pRoot->m_pRight = std::make_unique<TNode>(val);
                        pRoot->calculateHeight();
                        pRoot->calculateBalanceFactor();
                        balanceNodeTree(pRoot);

                        updateIteratorCacheForInsert(pRoot->getData(), true, pRoot->m_pRight.get());
                        return;
                    }
                }
                else if (val < pRoot->getData())    //The value should be at the left side of this node
                {
                    //The root node has left child so call it recursively now with the left child as new root node
                    if (pRoot->m_pLeft)
                    {
                        insert(val, pRoot->m_pLeft);
                    }
                    else
                    {
                        pRoot->m_pLeft = std::make_unique<TNode>(val);
                        // Calculate the height and bal factor of the
                        // newly inserted node so while it would be 
                        // unwinding recursion, each of the parent node
                        // gets updated by their's children without
                        // recalculating them in an expotential O(N^K) fashion
                        pRoot->calculateHeight();
                        pRoot->calculateBalanceFactor();
                        balanceNodeTree(pRoot);

                        updateIteratorCacheForInsert(pRoot->getData(), false, pRoot->m_pLeft.get());
                        return;
                    }
                }
                else
                {
                    return;     //Duplicate values are not allowed
                }
                // Keep updating the height and balnce factor for each node
                // while unwinding recursion. But only update it, don't calculate
                // as calculation would lead to an expotential O(N^K)
                pRoot->updateHeight();
                pRoot->updateBalanceFactor();
                balanceNodeTree(pRoot);
            }
            /**
             * @brief Clears the tree pointed by the given node
             *        Recursive in nature.
             * 
             * @param pRoot The root node of the tree to be cleared off
             */
            inline void clearTree(TNodePtr& pRoot)
            {
                if (!pRoot)
                    return;
                
                if (pRoot->m_pLeft)
                    clearTree(pRoot->m_pLeft);    //Clear the left sub tree

                if (pRoot->m_pRight)
                    clearTree(pRoot->m_pRight);   //Clear the right subtree

                pRoot.reset();  //Both the left and right subtrees are cleared so good to reset the root
                m_size = 0;     //Set the size to zero
            }
            /**
             * @brief Finds an element in the tree pointed by the passed node
             *        Recursive in nature.
             * 
             * @param val The element to be searched for
             * @param pNode The root node of the tree
             * @return true If the element can be traced, 
             * @return false otherwise
             */
            inline bool find(const T& val, const TNodePtr& pNode) const noexcept
            {
                if (val == pNode->getData())
                {
                    return true;
                }
                else if (val > pNode->getData())
                {
                    if (pNode->m_pRight)
                        return find(val, pNode->m_pRight);
                    else
                        return false;
                }
                else if (val < pNode->getData())
                {
                    if (pNode->m_pLeft)
                        return find(val, pNode->m_pLeft);
                    else
                        return false;
                }
                else
                {
                    return false;
                }
            }
            /**
             * @brief Finds inorder successor of a node. Once found it
             *        it returns the value of the node and deletes it from
             *        the tree/sub tree
             * 
             * @param pRightTreeNode The node to the right of the node for
             *                       which the inorder successor is to be found.
             * @param updateOnly A pervasive indicatior to indicate if the height
             *                   and the bal factor of the parent node to be updated
             *                   only or re calculated entirely while unwinding stack
             *                   frame.
             * @return T The inorder successor value.
             */
            T findInorderSuccessor(TNodePtr& pRightTreeNode, bool& updateOnly) noexcept
            {
                T retVal = {};
                if (pRightTreeNode)
                {
                    if (pRightTreeNode->m_pLeft)
                    {
                        retVal = std::move(findInorderSuccessor(pRightTreeNode->m_pLeft, updateOnly));
                        if (updateOnly)
                        {
                            pRightTreeNode->updateHeight();
                            pRightTreeNode->updateBalanceFactor();
                        }
                        else
                        {
                            pRightTreeNode->calculateHeight();
                            pRightTreeNode->calculateBalanceFactor();
                            updateOnly = true;
                        }
                    }
                    else
                    {
                        auto retVal = std::move(pRightTreeNode->m_data);
                        pRightTreeNode.reset();
                        return std::move(retVal);
                    }
                }
                return retVal;
            }
            /**
             * @brief Finds inorder predecessor of a node. Once found it
             *        it returns the value of the node and deletes it from
             *        the tree/sub tree
             * 
             * @param pLeftTreeRoot The node to the left of the node for
             *                       which the inorder successor is to be found.
             * @param updateOnly A pervasive indicatior to indicate if the height
             *                   and the bal factor of the parent node to be updated
             *                   only or re calculated entirely while unwinding stack
             *                   frame.
             * @return T The inorder successor value.
             */
            T findInorderPredecessor(TNodePtr& pLeftTreeRoot, bool& updateOnly) noexcept
            {
                T retVal;
                if (pLeftTreeRoot)
                {
                    if (pLeftTreeRoot->m_pRight)
                    {
                        retVal = std::move(findInorderPredecessor(pLeftTreeRoot->m_pRight));
                        if (updateOnly)
                        {
                            pLeftTreeRoot->updateHeight();
                            pLeftTreeRoot->updateBalanceFactor();
                        }
                        else
                        {
                            pLeftTreeRoot->calculateHeight();
                            pLeftTreeRoot->calculateBalanceFactor();
                            updateOnly = true;
                        }
                    }
                    else
                    {
                        auto retVal = std::move(pLeftTreeRoot->m_data);
                        pLeftTreeRoot.reset();
                        return std::move(retVal);
                    }
                }
                return retVal;
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
             * @param updateOnly A pervasive indicatior to indicate if the height
             *                   and the bal factor of the parent node to be updated
             *                   only or re calculated entirely while unwinding stack
             *                   frame.
             */
            inline void eraseElement(const T& val, TNodePtr& pRoot, bool& updateOnly)
            {
                if (val == pRoot->m_data)   //Node to be deleted found
                {
                    //Case1: The node to be deleted is a leaf node
                    if (!pRoot->m_pLeft && !pRoot->m_pRight)
                    {
                        pRoot.reset();
                        --m_size;
                    }
                    //Case2: The node to be deleted has only left sub tree
                    else if (pRoot->m_pLeft && !pRoot->m_pRight)
                    {
                        auto pLeft = std::move(pRoot->m_pLeft);
                        pRoot.reset();
                        pRoot = std::move(pLeft);
                        --m_size;
                    }
                    //Case3: The node to be deleted has only right sub tree
                    else if (!pRoot->m_pLeft && pRoot->m_pRight)
                    {
                        auto pRight = std::move(pRoot->m_pRight);
                        pRoot.reset();
                        pRoot = std::move(pRight);
                        --m_size;
                    }
                    //Case4: The node to be deleted has both left and right sub trees
                    else
                    {
                        /**
                         * In this case the node to be deleted can either be replaced 
                         * by it's inorder successor or inorder predessor to maintain
                         * the property of the BST.
                         */
                        auto updateOnly = false;
                        pRoot->m_data = std::move(findInorderSuccessor(pRoot->m_pRight, updateOnly));
                        --m_size;
                    }
                }
                else if (val > pRoot->m_data)   //Node resides in the right half of the root node
                {
                    eraseElement(val, pRoot->m_pRight, updateOnly);
                }
                else if (val < pRoot->m_data)   //Node resides in the left half of the root node
                {
                    eraseElement(val, pRoot->m_pLeft, updateOnly);
                }
                else    //Node is not found (shouldn't hit this case if been called from erase())
                {
                    return;
                }
                if (pRoot)
                {
                    if (updateOnly)
                    {
                        pRoot->updateHeight();
                        pRoot->updateBalanceFactor();
                    }
                    else
                    {
                        pRoot->calculateHeight();
                        pRoot->calculateBalanceFactor();
                        updateOnly = true;
                    }
                    balanceNodeTree(pRoot);
                }
            }
            /**
             * @brief Balances the node or the tree itself
             *        It balances a given node or tree (if
             *        the node is itself the root of the tree)
             * 
             * @param pNode The node for which balancing is to be done
             */
            inline void balanceNodeTree(TNodePtr& pNode) noexcept
            {
                auto balFact = pNode->getBalanceFactor();
                while (balFact < -1 || balFact > 1)
                {
                    if (balFact < -1)
                        pNode = std::move(rotateLeft(pNode));
                    else if (balFact > 1)
                        pNode = std::move(rotateRight(pNode));
                    
                    balFact = pNode->getBalanceFactor();
                }
            }
            /**
             * @brief Updates the cache used by the iterators
             *
             * @param val The value to be inserted into the cache
             * @param greater Whether the value lies in the right side of its parent node
             * @param pNode The parent node of the new value
             */
            void updateIteratorCacheForInsert(const T& val, const bool greater, TNode* pNode)
            {
               auto listItr = m_selfItr.m_list.cbegin();
                if (listItr != m_selfItr.m_list.cend())
                {
                    auto tobeLastElement = false;
                    do
                    {
                        if (val == listItr->getData()->getData())
                        {
                            if (greater)
                            {
                                ++listItr;
                                if (listItr == m_selfItr.m_list.cend())
                                    tobeLastElement = true;
                            }
                            break;
                        }
                        else
                        {
                            ++listItr;
                        }
                    } while (listItr != m_selfItr.m_list.cend());

                    if (tobeLastElement)
                    {
                        m_selfItr.m_list.push_back(pNode);
                    }
                    else if (listItr != m_selfItr.m_list.cend())
                    {
                        m_selfItr.m_list.insert(listItr, pNode);
                    }
                }
                else
                {
                    m_selfItr.m_list.push_back(pNode);
                }
            }
            /**
             * @brief 
             * 
             */
            TNodePtr m_pRoot;
            size_t m_size = 0;

            iterator m_selfItr;
    };
}   // namespace swarnendu

#endif // _AVL_TREE_H_
