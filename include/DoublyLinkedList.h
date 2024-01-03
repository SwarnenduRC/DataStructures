/**
 * @file DoublyLinkedList.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Nodes.h"

#include <initializer_list>
#include <algorithm>
namespace swarnendu
{
    using swarnendu_nodes::DoublyNode;

    template<typename T>
    class DoublyLinkedList
    {
        public:
            /**
             * @brief Custom iterator structure for Doubly linked list.
             *        It is a custom iterator which will enable the
             *        traversal of the list much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             * 
             */
            struct iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = T;
                using pointer = value_type*;
                using reference = value_type&;

                /**
                 * @brief Constructors and Destructor
                 * 
                 */
                iterator() = default;
                iterator(DoublyNode<T>* pHead, const bool reversed)
                    : m_itrPtr(pHead)
                    , m_bReversed(reversed)
                {}
                ~iterator() = default;
                iterator(const iterator&) = default;
                iterator& operator=(const iterator&) = default;
                iterator(iterator&&) = default;
                iterator& operator=(iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return iterator 
                 */
                iterator operator++(const int) noexcept
                {
                    iterator temp = *this;
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                        else
                            m_itrPtr = m_itrPtr->m_pNext.get();
                    }
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return iterator& 
                 */
                iterator& operator++() noexcept
                {
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                        else
                            m_itrPtr = m_itrPtr->m_pNext.get();
                    }
                    return *this;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return iterator 
                 */
                iterator operator--(const int) noexcept
                {
                    iterator temp = *this;
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pNext.get();
                        else
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                    }
                    return temp;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return iterator& 
                 */
                iterator& operator--() noexcept
                {
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pNext.get();
                        else
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                    }
                    return *this;
                }
                bool operator==(const iterator& rhs) const noexcept
                {
                    return ((m_itrPtr == rhs.m_itrPtr) && (m_bReversed == rhs.m_bReversed));
                }
                bool operator!=(const iterator& rhs) const noexcept
                {
                    return ((m_itrPtr != rhs.m_itrPtr) || (m_bReversed != rhs.m_bReversed));
                }
                reference operator*() const noexcept  { auto& val = m_itrPtr->m_data; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itrPtr; }
                /**
                 * @brief 
                 * 
                 */
                DoublyNode<T>* m_itrPtr = nullptr;
                bool m_bReversed = false;
            };
            /**
             * @brief Custom iterator structure for Doubly linked list.
             *        It is a custom iterator which will enable the
             *        traversal of the list much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             * 
             */
            struct const_iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this const_iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = const T;
                using pointer = const value_type*;
                using reference = const value_type&;

                /**
                 * @brief Constructors and Destructor
                 * 
                 */
                const_iterator() = default;
                const_iterator(DoublyNode<T>* pHead, const bool reversed)
                    : m_itrPtr(pHead)
                    , m_bReversed(reversed)
                {}
                ~const_iterator() = default;
                const_iterator(const const_iterator&) = default;
                const_iterator& operator=(const const_iterator&) = default;
                const_iterator(const_iterator&&) = default;
                const_iterator& operator=(const_iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return const_iterator 
                 */
                const_iterator operator++(const int) noexcept
                {
                    const_iterator temp = *this;
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                        else
                            m_itrPtr = m_itrPtr->m_pNext.get();
                    }
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return const_iterator& 
                 */
                const_iterator& operator++() noexcept
                {
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                        else
                            m_itrPtr = m_itrPtr->m_pNext.get();
                    }
                    return *this;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return const_iterator 
                 */
                const_iterator operator--(const int) noexcept
                {
                    const_iterator temp = *this;
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pNext.get();
                        else
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                    }
                    return temp;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return const_iterator& 
                 */
                const_iterator& operator--() noexcept
                {
                    if (m_itrPtr)
                    {
                        if (m_bReversed)
                            m_itrPtr = m_itrPtr->m_pNext.get();
                        else
                            m_itrPtr = m_itrPtr->m_pPrev.lock().get();
                    }
                    return *this;
                }
                bool operator==(const const_iterator& rhs) const noexcept
                {
                    return ((m_itrPtr == rhs.m_itrPtr) && (m_bReversed == rhs.m_bReversed));
                }
                bool operator!=(const const_iterator& rhs) const noexcept
                {
                    return ((m_itrPtr != rhs.m_itrPtr) || (m_bReversed != rhs.m_bReversed));
                }
                reference operator*() const noexcept  { auto& val = m_itrPtr->m_data; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itrPtr; }
                /**
                 * @brief 
                 * 
                 */
                DoublyNode<T>* m_itrPtr = nullptr;
                bool m_bReversed = false;
            };

            /* Constructors and Destructors*/
            DoublyLinkedList() = default;
            ~DoublyLinkedList() = default;
            DoublyLinkedList(const std::initializer_list<T>& iList) noexcept
                : m_size(0)
                , m_pHead(nullptr)
                , m_pTail(nullptr)
            {
                if (iList.size() != 0)
                {
                    for (const auto& element : iList)
                        push_back(element);
                }
            }
            DoublyLinkedList(const DoublyLinkedList& rhs) noexcept
                : m_size(0)
                , m_pHead(nullptr)
                , m_pTail(nullptr)
            {
                if (!rhs.empty())
                {
                    auto pSrcHead = rhs.m_pHead;
                    //If we simply copy over the head and tail pointers
                    //from the source then the linking between head and tail
                    //proving to be very difficult so rather run a push back
                    //which automatically does the linking
                    while (pSrcHead)
                    {
                        push_back(pSrcHead->getData());
                        pSrcHead = pSrcHead->m_pNext;
                    }
                }
            }
            DoublyLinkedList(DoublyLinkedList&& rhs) noexcept
                : m_size(std::move_if_noexcept(rhs.m_size))
                , m_pHead(std::move_if_noexcept(rhs.m_pHead))
                , m_pTail(std::move_if_noexcept(rhs.m_pTail))
            {
                rhs.clear();
            }
            DoublyLinkedList& operator=(const DoublyLinkedList& rhs) noexcept
            {
                if (this != &rhs)
                {
                    if (!empty())
                        clear();

                    if (!rhs.empty())
                    {
                        auto pSrcHead = rhs.m_pHead;
                        while (pSrcHead)
                        {
                            push_back(pSrcHead->getData());
                            pSrcHead = pSrcHead->m_pNext;
                        }
                    }
                }
                return *this;
            }
            DoublyLinkedList& operator=(DoublyLinkedList&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    if (!empty())
                        clear();
                    
                    m_size = std::move_if_noexcept(rhs.m_size);
                    m_pHead = std::move_if_noexcept(rhs.m_pHead);
                    m_pTail = std::move_if_noexcept(rhs.m_pTail);                    
                    rhs.clear();
                }
                return *this;
            }

            inline bool empty() const noexcept { return (m_size == 0); }
            inline size_t size() const noexcept { return m_size; }

            bool operator==(const DoublyLinkedList& rhs) const noexcept
            {
                if (empty() && rhs.empty())
                    return true;
                else if (empty() && !rhs.empty())
                    return false;
                else if (!empty() && rhs.empty())
                    return false;
                else if (size() != rhs.size())
                    return false;
                else
                {
                    auto thisItr = begin();
                    auto rhsItr = rhs.begin();
                    while (thisItr != end() && rhsItr != rhs.end())
                    {
                        if (*thisItr != *rhsItr)
                            return false;

                        ++thisItr;
                        ++rhsItr;
                    }
                    if (thisItr != end() || rhsItr != rhs.end())
                        return false;
                    return true;
                }
            }

            bool operator!=(const DoublyLinkedList& rhs) const noexcept { return !(*this == rhs); }

            /**
             * @brief Pushes an element at the front to the list
             *        If the list is empty then it just creates
             *        two shared pointers for head and tail pointing
             *        to the same value to be inserted. otherwise
             *        it readjusts the nodes accordingly
             * 
             * @param val Value to be inserted in the list
             */
            void push_front(const T& val)
            {
                if (!empty())
                {
                    auto pNewNode = std::make_shared<DoublyNode<T>>(val);
                    if (size() == 1)
                    {
                        m_pTail->m_pPrev = m_pHead;
                        m_pTail = m_pHead;
                    }
                    pNewNode->m_pNext = m_pHead;
                    m_pHead->m_pPrev = pNewNode;
                    m_pHead = pNewNode;
                }
                else
                {
                    m_pHead = std::make_shared<DoublyNode<T>>(val);
                    m_pTail = std::make_shared<DoublyNode<T>>(val);
                }
                ++m_size;
            }

            /**
             * @brief Pushes an element at the back to the list
             *        If the list is empty then it just creates
             *        two shared pointers for head and tail pointing
             *        to the same value to be inserted. otherwise
             *        it readjusts the nodes accordingly
             * 
             * @param val Value to be inserted in the list
             */
            void push_back(const T& val)
            {
                if (!empty())
                {
                    auto pNewNode = std::make_shared<DoublyNode<T>>(val);
                    pNewNode->m_pPrev = m_pTail;
                    m_pTail->m_pNext = pNewNode;
                    m_pTail = pNewNode;
                    if (size() == 1)
                    {
                        m_pHead->m_pNext = pNewNode;
                        m_pTail->m_pPrev = m_pHead;
                    }
                }
                else
                {
                    m_pHead = std::make_shared<DoublyNode<T>>(val);
                    m_pTail = std::make_shared<DoublyNode<T>>(val);
                }
                ++m_size;
            }
            /**
             * @brief Pops the first element from the list
             * 
             */
            void pop_front()
            {
                if (!empty())
                {
                    if (size() == 1)
                    {
                        clear();
                    }
                    else
                    {
                        m_pHead->m_pNext->m_pPrev = m_pHead->m_pPrev;
                        m_pHead = m_pHead->m_pNext;
                        --m_size;
                    }
                }
            }
            /**
             * @brief Pops the last element from the list
             * 
             */
            void pop_back()
            {
                if (!empty())
                {
                    if (size() == 1)
                    {
                        clear();
                    }
                    else
                    {
                        m_pTail->m_pPrev.lock()->m_pNext = m_pTail->m_pNext;
                        m_pTail = m_pTail->m_pPrev.lock();
                        --m_size;
                    }
                }
            }
            /**
             * @brief Pops an element from the specified position
             * 
             * @param pos The position at which the element will be poped.
             *            Please note the first postion in the list is
             *            considered as 0 (zero)
             */
            void pop_at(const size_t pos)
            {
                if (!empty())
                {
                    auto pCurrNode = m_pHead;
                    for (size_t cnt = 0; cnt < pos; ++cnt)
                    {
                        if (pCurrNode)
                            pCurrNode = pCurrNode->m_pNext;
                    }
                    auto pNextNode = pCurrNode->m_pNext;
                    pCurrNode->m_pPrev.lock()->m_pNext = pNextNode;
                    pNextNode->m_pPrev = pCurrNode->m_pPrev;
                    pCurrNode.reset();
                    --m_size;
                }
            }
            /**
             * @brief Erases an element from the list
             * 
             * @param pos Const iterator pointing to the element to be erased
             * @return iterator An iterator pointing to the next element
             *         of the element to be erased, or end otherwise
             */
            iterator erase(const_iterator pos)
            {
                if (pos == cend() || !pos->m_pNext)
                    return end();

                auto posCopy = pos++;
                iterator retVal(pos.m_itrPtr, false);
                erase(*posCopy);
                return retVal;
            }
            /**
             * @brief Erases the elements lies between a range
             * 
             * @param first The starting postion
             * @param last The ending position
             * @return iterator iterator An iterator pointing to the last element
             *         of the element to be erased, or end otherwise
             */
            iterator erase(const_iterator first, const_iterator last)
            {
                if (first == last && last == cend())
                    return end();
                if (!last->m_pNext)
                    return end();

                auto lastCopy = last++;
                iterator retVal(last.m_itrPtr, false);
                const_iterator firstCopy;
                while (first != lastCopy)
                {
                    //Take a copy of first before incrementing
                    //because after erasing the iterator going
                    //to be invalidated so get the next one in
                    //line before we proceed for deletion
                    firstCopy = first++;
                    erase(*firstCopy);
                }
                erase(*lastCopy);
                return retVal;
            }
            /**
             * @brief Inserts an element into the list
             * 
             * @param pos Constant Iterator position before which the lement would be inserted
             * @param val The value to be inserted
             * @return iterator The iterator pointing to the new element
             */
            iterator insert(const_iterator pos, const T& val)
            {
                if (pos == cbegin())
                {
                    push_front(val);
                    return begin();
                }
                else if (pos == cend())
                {
                    push_at(val, size() - 1);
                    return iterator(m_pTail->m_pPrev.lock().get(), false);
                }
                else
                {
                    auto pNewNode = std::make_shared<DoublyNode<T>>(val);
                    auto pNewNodesNext = pos.m_itrPtr->m_pPrev.lock()->m_pNext;
                    pNewNode->m_pPrev = pos.m_itrPtr->m_pPrev;
                    pNewNode->m_pPrev.lock()->m_pNext = pNewNode;
                    pNewNode->m_pNext = std::move(pNewNodesNext);
                    pos.m_itrPtr->m_pPrev = pNewNode;
                    ++m_size;
                    return iterator(pos.m_itrPtr->m_pPrev.lock().get(), false);
                }
            }
            /**
             * @brief Inserts an element multiple times
             * 
             * @param pos Constant Iterator position before which the lement would be inserted
             * @param count The no of times the element needs to be inserted
             * @param val The value
             * @return iterator The iterator pointing to the new element first inserted
             */
            iterator insert(const_iterator pos, const size_t count, const T& val)
            {
                if (count == 0)
                    return iterator(pos.m_itrPtr, false);

                auto retVal = insert(pos, val);
                for (size_t counter = 0; counter < count - 1; ++counter)
                    insert(pos, val);

                return retVal;
            }
            /**
             * @brief Inserts elements into the list
             * 
             * @param pos Constant Iterator position before which the lements would be inserted
             * @param iList The initializer list which contains the elements to be inserted
             * @return iterator iterator The iterator pointing to the new element first inserted
             */
            iterator insert(const_iterator pos, const std::initializer_list<T>& iList)
            {
                if (std::empty(iList))
                    return iterator(pos.m_itrPtr, false);

                auto start = iList.begin();
                auto retVal = insert(pos, *start);
                while (++start != iList.end())
                    insert(pos, *start);

                return retVal;
            }
            /**
             * @brief Finds an element in the list
             * 
             * @param val The element to be found
             * @return TRUE if the item is there in the list, FALSE otherwise
             */
            bool find(const T& val) const noexcept
            {
                if (empty())
                    return false;

                auto itr = cbegin();
                auto revItr = crbegin();
                for (; itr != crend() && revItr != crend(); ++itr, ++revItr)
                {
                    if (itr->getData() == val || revItr->getData() == val)
                        return true;;
                }
                return false;
            }
            /**
             * @brief Clears the entire list
             * 
             */
            void clear()
            {
                if (!empty())
                {
                    std::shared_ptr<DoublyNode<T>> pCurrNode;
                    while (m_pHead)
                    {
                        pCurrNode = m_pHead;
                        m_pHead = m_pHead->m_pNext;
                        if (pCurrNode)
                            pCurrNode.reset();
                    }
                    if (m_pHead)
                        m_pHead.reset();

                    if (m_pTail)
                        m_pTail.reset();

                    m_size = 0;
                }
            }
            /**
             * @brief Resizes the list to the given count
             * 
             * @param count The count to which the list should be resized.
             *              Resizes the container to contain count elements, 
             *              does nothing if count == size().
             *              If the current size is greater than count, 
             *              the container is reduced to its first count elements.
             *              If the current size is less than count, additional 
             *              default-inserted elements are appended.
             */
            void resize(size_t count)
            {
                if (size() == count)
                    return;

                size_t diff = 0;
                if (count > size())
                {
                    diff = count - size();
                    while (diff > 0)
                    {
                        push_back(T());
                        --diff;
                    }
                }
                else
                {
                    diff = size() - count;
                    while (diff > 0)
                    {
                        pop_back();
                        --diff;
                    }
                }
            }
            /**
             * @brief Resizes the list to the given count
             * 
             * @param count The count to which the list should be resized.
             *              Resizes the container to contain count elements, 
             *              does nothing if count == size().
             *              If the current size is greater than count, 
             *              the container is reduced to its first count elements.
             *              If the current size is less than count, additional 
             *              copies of val are appended.
             * 
             * @param val   The value to be appended
             */
            void resize(size_t count, const T& val)
            {
                if (size() == count)
                    return;

                size_t diff = 0;
                if (count > size())
                {
                    diff = count - size();
                    while (diff > 0)
                    {
                        push_back(val);
                        --diff;
                    }
                }
                else
                {
                    diff = size() - count;
                    while (diff > 0)
                    {
                        pop_back();
                        --diff;
                    }
                }
            }
            /**
             * @brief Revrses the list. Shouldn't throw any exception
             * 
             */
            void reverse() noexcept
            {
                if (empty())
                    return;

                auto pCurrNode = m_pHead;
                std::shared_ptr<DoublyNode<T>> pPrev;
                while (pCurrNode)
                {
                    pPrev = pCurrNode->m_pPrev.lock();
                    pCurrNode->m_pPrev = pCurrNode->m_pNext;
                    pCurrNode->m_pNext = pPrev;
                    pCurrNode = pCurrNode->m_pPrev.lock();
                }
                std::swap(m_pHead, m_pTail);
            }
            /**
             * @brief Gets the Tail of the list
             * 
             * @return DoublyNode<T>* The last node of the list if not empty otherwise NULL
             */
            inline DoublyNode<T>* getTail() const noexcept
            {
                if (!empty())
                    return m_pTail.get();

                return nullptr;
            }
            /**
             * @brief Get the Head of the list
             * 
             * @return DoublyNode<T>* The first node of the list if not empty otherwise NULL
             */
            inline DoublyNode<T>* getHead() const noexcept
            {
                if (!empty())
                    return m_pHead.get();
                
                return nullptr;
            }
            /**
             * @brief Various begin and end functions
             * 
             * @return iterator 
             */
            iterator begin()            const { return iterator(m_pHead.get(), false);          }
            iterator end()              const { return iterator();                              }
            iterator rbegin()           const { return iterator(m_pTail.get(), true);           }
            iterator rend()             const { return iterator(nullptr, true);                 }

            const_iterator cbegin()     const { return const_iterator(m_pHead.get(), false);    }
            const_iterator cend()       const { return const_iterator();                        }
            const_iterator crbegin()    const { return const_iterator(m_pTail.get(), true);     }
            const_iterator crend()      const { return const_iterator(nullptr, true);           }
        
        private:
            const_iterator findInternal(const T& val) noexcept
            {
                if (empty())
                    return const_iterator();

                auto itr = cbegin();
                auto revItr = crbegin();
                for (; itr != cend() && revItr != crend(); ++itr, ++revItr)
                {
                    if (*itr == val)
                        return itr;
                    else if (*revItr == val)
                        return revItr;
                }
                return const_iterator();
            }
            /**
             * @brief Erases an element form the list
             * 
             * @param val The value to be erased
             */
            void erase(const T& val)
            {
                if (!empty())
                {
                    auto itr = findInternal(val);
                    if (itr == cend() || itr == crend())
                        return;

                    //The node to be deleted is the first node
                    if (!itr->m_pPrev.lock())
                    {
                        return pop_front();
                    }
                    //The node to be deleted is the last node
                    else if (!itr->m_pNext)
                    {
                        return pop_back();
                    }
                    //Any node except first or last node    
                    else
                    {
                        itr->m_pPrev.lock()->m_pNext = itr->m_pNext;
                        itr->m_pNext->m_pPrev = itr->m_pPrev;
                        --m_size;
                    }
                }
            }
            /**
             * @brief Pushes an element at the specified position
             * 
             * @param val The element to be pushed
             * @param pos The position at which the element will be pushed.
             *            Please note the first postion in the list is
             *            considered as 0 (zero)
             */
            void push_at(const T& val, const size_t pos)
            {
                if (empty() || pos == 1)
                {
                    push_front(val);
                }
                else if (pos >= size())
                {
                    push_back(val);
                }
                else
                {
                    auto pCurrNode = m_pHead;
                    for (size_t cnt = 0; cnt < pos; ++cnt)
                    {
                        if (pCurrNode)
                            pCurrNode = pCurrNode->m_pNext;
                    }
                    auto pNewNode = std::make_shared<DoublyNode<T>>(val);
                    pNewNode->m_pPrev = pCurrNode->m_pPrev;
                    pNewNode->m_pPrev.lock()->m_pNext = pNewNode;
                    pNewNode->m_pNext = pCurrNode;
                    pCurrNode->m_pPrev = pNewNode;
                    ++m_size;
                }
            }
            /**
             * @brief 
             * 
             */
            size_t m_size = 0;
            std::shared_ptr<DoublyNode<T>> m_pHead = nullptr;
            std::shared_ptr<DoublyNode<T>> m_pTail = nullptr;
    };
} // namespace swarnendu

#endif
