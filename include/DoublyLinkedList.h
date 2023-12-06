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

#include <optional>
#include <initializer_list>
namespace swarnendu
{
    using swarnendu_nodes::DoublyNode;

    template<typename T = int>
    class DoublyLinkedList
    {
        public:
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
             * @brief Pops the first element from the list
             * 
             * @return std::optional<T> The element if pops successful otherwise std::nullopt
             */
            std::optional<T> pop_front()
            {
                std::optional<T> retVal;
                if (empty())
                    return std::nullopt;
                    
                if (size() == 1)
                {
                    retVal = std::move(m_pHead->getData());
                    clear();
                    return std::move(retVal);
                }
                else
                {
                    retVal = std::move(m_pHead->getData());
                    m_pHead->m_pNext->m_pPrev = m_pHead->m_pPrev;
                    m_pHead = m_pHead->m_pNext;
                    --m_size;
                    return std::move(retVal);
                }
            }
            /**
             * @brief Pops the last element from the list
             * 
             * @return std::optional<T> The element if pops successful otherwise std::nullopt
             */
            std::optional<T> pop_back()
            {
                if (empty())
                    return std::nullopt;

                if (size() == 1)
                {
                    auto retVal = std::move(m_pTail->getData());
                    clear();
                    return std::move(retVal);
                }
                else
                {
                    auto retVal = std::move(m_pTail->getData());
                    m_pTail->m_pPrev.lock()->m_pNext = m_pTail->m_pNext;
                    m_pTail = m_pTail->m_pPrev.lock();
                    --m_size;
                    return std::move(retVal);
                }
            }
            /**
             * @brief Pops an element from the specified position
             * 
             * @param pos The position at which the element will be poped.
             *            Please note the first postion in the list is
             *            considered as 0 (zero)
             * @return std::optional<T> The element if pops successful otherwise std::nullopt
             */
            std::optional<T> pop_at(const size_t pos)
            {
                if (empty())
                {
                    if (std::is_integral<T>::value) //Only for testing purpose
                        return 0;
                    else
                        return std::nullopt;
                }
                else if (pos > size())
                {
                    if (std::is_integral<T>::value) //Only for testing purpose
                        return 0;
                    else
                        return std::nullopt;
                }
                else
                {
                    auto pCurrNode = m_pHead;
                    for (size_t cnt = 0; cnt < pos; ++cnt)
                    {
                        if (pCurrNode)
                            pCurrNode = pCurrNode->m_pNext;
                    }
                    auto retVal = std::move(pCurrNode->getData());
                    auto pNextNode = pCurrNode->m_pNext;
                    pCurrNode->m_pPrev.lock()->m_pNext = pNextNode;
                    pNextNode->m_pPrev = pCurrNode->m_pPrev;
                    pCurrNode.reset();
                    --m_size;
                    return std::move(retVal);
                }
            }
            /**
             * @brief Erases an element from the list
             * 
             * @param val The element to be erased
             * @return std::optional<T> The element if the erase is successful otherwise std nullopt
             */
            std::optional<T> erase(const T& val)
            {
                if (empty())
                {
                    if (std::is_integral<T>::value) //Only for testing purpose
                        return 0;
                    else
                        return std::nullopt;
                }
                else
                {
                    auto [elemFound, pNode] = find(val);
                    if (!elemFound)
                        return std::nullopt;

                    //The node to be deleted is the first node
                    if (pNode && !pNode->m_pPrev.lock())
                    {
                        return pop_front();
                    }
                    //The node to be deleted is the last node
                    else if (pNode && !pNode->m_pNext)
                    {
                        return pop_back();
                    }
                    //Any node except first or last node    
                    else
                    {
                        auto retVal = std::move(pNode->getData());
                        pNode->m_pPrev.lock()->m_pNext = pNode->m_pNext;
                        pNode->m_pNext->m_pPrev = pNode->m_pPrev;
                        --m_size;
                        return std::move(retVal);
                    }
                }
            }
            /**
             * @brief Finds an element in the list
             * 
             * @param val The element to be found
             * @return std::tuple<bool, DoublyNode<T>*> Returns true and node to the element if successful
             *                                          otherwise false and nullptr
             */
            std::tuple<bool, DoublyNode<T>*> find(const T& val)
            {
                if (empty())
                    return std::make_tuple(false, nullptr);

                auto pHead = m_pHead.get();
                auto pTail = m_pTail.get();
                while (pHead && pTail)
                {
                    if (val == pHead->getData())
                        return std::make_tuple(true, pHead);
                    if (val == pTail->getData())
                        return std::make_tuple(true, pTail);

                    pHead = pHead->m_pNext.get();
                    pTail = pTail->m_pPrev.lock().get();
                }
                return std::make_tuple(false, nullptr);
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
        private:
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
