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

#include <iostream>

#include "Nodes.h"

namespace swarnendu
{
    using swarnendu_nodes::DoublyNode;

    template<typename T>
    class DoublyLinkedList
    {
        public:
            DoublyLinkedList() = default;
            ~DoublyLinkedList() = default;
            DoublyLinkedList(const DoublyLinkedList& rhs) noexcept
                : m_pHead(new DoublyNode<T>())
                , m_pTail(new DoublyNode<T>())
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
            void pop_front()
            {
                if (empty())
                {
                    std::cout << std::endl << std::endl << "The list is empty. Nothing to delete" << std::endl << std::endl;
                    return;
                }
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
            void pop_back()
            {
                if (empty())
                {
                    std::cout << std::endl << std::endl << "The list is empty. Nothing to delete" << std::endl << std::endl;
                    return;
                }
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
            void pop_at(const size_t pos)
            {
                if (empty())
                {
                    std::cout << std::endl << std::endl << "The list is empty. Nothing to delete" << std::endl << std::endl;
                }
                else if (pos > size())
                {
                    std::cout << std::endl << std::endl << "The list is long enough. List size = " << size() << ", pos = " << pos << std::endl << std::endl;
                }
                else
                {
                    auto pCurrNode = m_pHead;
                    for (size_t cnt = 0; cnt < pos; ++cnt)
                    {
                        if (pCurrNode)
                            pCurrNode = pCurrNode->m_pNext;
                    }
                    auto pNextNode = pCurrNode->m_pNext;
                    pCurrNode->m_pPrev->m_pNext = pNextNode;
                    pNextNode->m_pPrev = pCurrNode->m_pPrev;
                    pCurrNode.reset();
                    --m_size;
                }
            }
            void display() const noexcept
            {
                if (!empty())
                {
                    auto pHead = m_pHead;
                    std::cout << std::endl;
                    while (pHead)
                    {
                        std::cout << pHead->getData();
                        pHead = pHead->m_pNext;
                        if (pHead)
                            std::cout << " --> ";
                        else
                            std::cout << " --> NULL";
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << std::endl << std::endl << "The list is empty" << std::endl << std::endl;
                }
            }
            void displayBack() const noexcept
            {
                if (!empty())
                {
                    auto pTail = m_pTail;
                    std::cout << std::endl;
                    while (pTail)
                    {
                        std::cout << pTail->getData();
                        pTail = pTail->m_pPrev.lock();
                        if (pTail)
                            std::cout << " --> ";
                        else
                            std::cout << " --> NULL";
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << std::endl << std::endl << "The list is empty" << std::endl << std::endl;
                }
            }
            bool erase(const T& val)
            {
                if (empty())
                {
                    return false;
                }
                else
                {
                    auto [elemFound, pNode] = find(val);
                    if (!elemFound)
                        return false;

                    //The node to be deleted is the first node
                    if (pNode && !pNode->m_pPrev.lock())
                    {
                        pop_front();
                    }
                    //The node to be deleted is the last node
                    else if (pNode && !pNode->m_pNext)
                    {
                        pop_back();
                    }
                    //Any node except first or last node    
                    else
                    {
                        pNode->m_pPrev.lock()->m_pNext = pNode->m_pNext;
                        pNode->m_pNext->m_pPrev = pNode->m_pPrev;
                        pNode.reset();
                        --m_size;
                    }
                    return true;
                }
            }

            std::tuple<bool, std::shared_ptr<DoublyNode<T>>> find(const T& val)
            {
                if (empty())
                    return std::make_tuple(false, nullptr);

                auto pHead = m_pHead;
                auto pTail = m_pTail;
                while (pHead && pTail)
                {
                    if (val == pHead->getData())
                        return std::make_tuple(true, pHead);
                    if (val == pTail->getData())
                        return std::make_tuple(true, pTail);

                    pHead = pHead->m_pNext;
                    pTail = pTail->m_pPrev.lock();
                }
                return std::make_tuple(false, nullptr);
            }

            /**
             * @brief 
             * 
             * @param list 
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
            inline T getBack() const noexcept
            {
                if (!empty())
                    return m_pTail->getData();
                return T();
            }
            inline T getFront() const noexcept
            {
                if (!empty())
                    return m_pHead->getData();
                return T();
            }
        private:
            /**
             * @brief 
             * 
             */
            size_t m_size = 0;
            std::shared_ptr<DoublyNode<T>> m_pHead;
            std::shared_ptr<DoublyNode<T>> m_pTail;
    };
} // namespace swarnendu
