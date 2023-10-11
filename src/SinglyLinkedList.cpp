/**
 * @file SinglyLinkedList.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SinglyLinkedList.h"

#include <algorithm>
#include <memory>
#include <functional>
namespace swarnendu
{
    SinglyLinkedList::SinglyLinkedList(const std::initializer_list<int>& list)
        : m_pHead(nullptr)
        , m_pTail(nullptr)
        , m_size(0)
    {
        if (list.size() != 0)
        {
            for (const auto element : list)
                push_back(element);
        }
    }
    SinglyLinkedList::~SinglyLinkedList()
    {        
        /**
         * @brief At the very begining of the insertion
         * i.e.; either in push_back or push_front, we only 
         * allocate memory for m_pHead and rest all
         * passing and realigning pointers. So deleting
         * only the head node would clear up the memory
         * entirely by calling the destructor of SinglyNode
         * in a recursive fashion.
         */
        if (m_pHead)
            delete m_pHead;

        m_pHead = nullptr;
        m_pTail = nullptr;
        m_size = 0;
    }

    void SinglyLinkedList::clear()
    {
        if (!empty())
        {
            /**
             * Deleting only the head pointer will
             * recursively the entire list as the 
             * destructor of SinglyNode will get called
             */
            if (m_pHead)
                delete m_pHead;

            m_size = 0;
            m_pHead = nullptr;
            m_pTail = nullptr;
        }
    }

    SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& rhs) noexcept
        : m_pHead(new SinglyNode(*rhs.m_pHead))
        , m_pTail(rhs.m_pTail)
        , m_size(rhs.m_size)
    {
    }

    SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& rhs) noexcept
    {
        if (this != &rhs)
        {
            if (m_pHead || m_pTail)
                clear();
            copy(rhs);
        }
        return *this;
    }

    SinglyLinkedList::SinglyLinkedList(SinglyLinkedList&& rhs) noexcept 
        : m_pHead(std::move_if_noexcept(rhs.m_pHead))
        , m_pTail(nullptr)
        , m_size(std::move_if_noexcept(rhs.m_size))
    {
        rhs.m_size = 0;
        rhs.m_pHead = nullptr;
        rhs.m_pTail = nullptr;
        
        auto pHead = m_pHead;        
        while(pHead->m_pNext)
            pHead = pHead->m_pNext;
        m_pTail = pHead;
    }

    SinglyLinkedList& SinglyLinkedList::operator=(SinglyLinkedList&& rhs) noexcept
    {
        if (this != &rhs)
        {
            if (m_pHead || m_pTail)
                clear();

            m_pHead = std::move_if_noexcept(rhs.m_pHead);            
            
            auto pHead = m_pHead;
            while(pHead->m_pNext)
                pHead = pHead->m_pNext;
            m_pTail = pHead;

            m_size = std::move_if_noexcept(rhs.m_size);
            rhs.m_size = 0;
            rhs.m_pHead = nullptr;
            rhs.m_pTail = nullptr;
        }
        return *this;
    }

    void SinglyLinkedList::copy(const SinglyLinkedList& rhs)
    {
        if (this != &rhs)
        {
            clear();
            if (rhs.m_pHead)
            {
                auto pRHSHead = rhs.m_pHead;
                while (pRHSHead)
                {
                    push_back(pRHSHead->m_element);
                    pRHSHead = pRHSHead->m_pNext;
                }
            }
        }
    }

    void SinglyLinkedList::push_front(const int val)
    {
        if (empty())
        {
            m_pHead = new SinglyNode(val);
            m_pTail = m_pHead;
        }
        else
        {
            auto pNewNode = new SinglyNode(val);
            pNewNode->m_pNext = m_pHead;
            m_pHead = pNewNode;
        }
        ++m_size;
    }

    void SinglyLinkedList::push_back(const int val)
    {
        if (empty())
        {
            m_pHead = new SinglyNode(val);
            m_pTail = m_pHead;
        }
        else
        {
            m_pTail->m_pNext = new SinglyNode(val);
            m_pTail = m_pTail->m_pNext;
        }
        ++m_size;
    }

    void SinglyLinkedList::push_at(const size_t pos, const int val)
    {
        if (empty())
        {
            push_front(val);
        }
        else if (pos == 0)
        {
            push_front(val);
        }
        else if (pos > m_size)
        {
            push_back(val);
        }
        else
        {
            auto pNextNode = m_pHead->m_pNext;
            auto pPrevNode = m_pHead;
            for (size_t cnt = 0; cnt < pos; ++cnt)
            {
               pPrevNode = pNextNode;
               pNextNode = pNextNode->m_pNext;
            }

            auto pNewNode = new SinglyNode(val);
            pNewNode->m_pNext = pNextNode;
            pPrevNode->m_pNext = pNewNode;
            ++m_size;
        }
    }

    void SinglyLinkedList::push_middle(const int val)
    {
        if (empty())
        {
            push_front(val);
        }
        else if (1 == m_size)
        {
            push_front(val);
        }
        else
        {
            push_at(((m_size / 2) + (m_size % 2)), val);
        }
    }

    int SinglyLinkedList::pop_front()
    {
        if (empty())
        {
            return INT_MIN;
        }
        else if (size() == 1)
        {
            auto retVal = m_pHead->m_element;
            clear();
            return retVal;
        }
        else
        {
            auto pForntNode = m_pHead;
            auto retVal = m_pHead->m_element;
            m_pHead = m_pHead->m_pNext;
            if (pForntNode->m_pNext)
            {
                //Break the link of the previous head node before deletion
                pForntNode->m_pNext = nullptr;
                delete pForntNode;
            }

            pForntNode = nullptr;
            --m_size;
            return retVal;
        }
    }

    int SinglyLinkedList::pop_back()
    {
        if (empty())
        {
            return INT_MIN;
        }
        else if (size() == 1)
        {
            auto retVal = m_pTail->m_element;
            clear();
            return retVal;
        }
        else
        {
            auto retVal = m_pTail->m_element;
            auto pLastNode = m_pHead;
            SinglyNode* pPrevNode = nullptr;
            while (pLastNode->m_pNext)
            {
                pPrevNode = pLastNode;
                pLastNode = pLastNode->m_pNext;
            }
            if (pLastNode)
                delete pLastNode;
            pLastNode = nullptr;

            pPrevNode->m_pNext = nullptr;
            m_pTail = pPrevNode;
            --m_size;
            return retVal;
        }
    }

    int SinglyLinkedList::pop_at(const size_t pos)
    {
        if (empty())
        {
            return INT_MIN;
        }
        else if (size() <= pos)
        {
            return INT_MIN;
        }
        else if ((size() - 1) == pos)
        {
            return pop_back();
        }
        else
        {
            auto pDelNode = m_pHead;
            SinglyNode* pPrevNode = nullptr;
            for (size_t cnt = 0; cnt < pos; ++cnt)
            {
                pPrevNode = pDelNode;
                pDelNode = pDelNode->m_pNext;
            }
            pPrevNode->m_pNext = pDelNode->m_pNext;
            
            auto retVal = INT_MIN;
            if (pDelNode)
            {
                retVal = pDelNode->m_element;
                pDelNode->m_pNext = nullptr; //Break the link so that deleting it doesn't invoke entire list recusively.
                delete pDelNode;
            }
            pDelNode = nullptr;

            --m_size;
            return retVal;
        }
    }

    int SinglyLinkedList::pop_middle()
    {
        if (empty())
        {
            return INT_MIN;
        }
        else
        {
            return pop_at(size() / 2);
        }
    }

    int* SinglyLinkedList::find(const int val) const noexcept
    {
        if (empty())
            return nullptr;

        auto pHead = m_pHead;
        while(pHead)
        {
            if (pHead->m_element == val)
                return &pHead->m_element;

            pHead = pHead->m_pNext;
        }
        return nullptr;
    }
}