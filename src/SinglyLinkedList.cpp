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

#include <iostream>
#include <algorithm>
#include <memory>

#include "SinglyLinkedList.h"


namespace swarnendu
{
    SinglyLinkedList::~SinglyLinkedList()
    {
        if (!isEmpty())
            clearList();

        m_pHead = nullptr;
        m_pTail = nullptr;
    }

    void SinglyLinkedList::clearList()
    {
        if (!isEmpty())
        {
            SinglyNode* pCurrent = nullptr;
            while (m_pHead)
            {
                pCurrent = m_pHead;
                m_pHead = m_pHead->m_pNext;
                if (pCurrent)
                {
                    delete pCurrent;
                    --m_size;
                }
                pCurrent = nullptr;
            }
            m_size = 0;
        }
    }

    SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& rhs) noexcept
    {
        copyList(rhs);
    }

    SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& rhs) noexcept
    {
        if (this != &rhs)
        {
            if (m_pHead || m_pTail)
                clearList();

            copyList(rhs);
        }
        return *this;
    }

    SinglyLinkedList::SinglyLinkedList(SinglyLinkedList&& rhs) noexcept : 
        m_pHead(rhs.m_pHead), m_pTail(rhs.m_pTail), m_size(rhs.m_size) 
    {
        rhs.m_pHead = rhs.m_pTail = nullptr;
        rhs.m_size = 0;
    }

    SinglyLinkedList& SinglyLinkedList::operator=(SinglyLinkedList&& rhs) noexcept
    {
        if (this != &rhs)
        {
            if (m_pHead || m_pTail)
                clearList();

            std::swap(m_pHead, rhs.m_pHead);
            std::swap(m_pTail, rhs.m_pTail);
            std::swap(m_size, rhs.m_size);
        }
        return *this;
    }

    void SinglyLinkedList::copyList(const SinglyLinkedList& rhs) noexcept
    {
        if (rhs.m_pHead && rhs.m_pTail)
        {
            auto pRHSCurr = rhs.m_pHead;
            m_pHead = new SinglyNode();
            m_pHead->m_element = rhs.m_pHead->m_element;
            auto pHead = m_pHead;
            while (pRHSCurr->m_pNext)
            {
                pRHSCurr = pRHSCurr->m_pNext;
                pHead->m_pNext = new SinglyNode();
                pHead = pHead->m_pNext;
                pHead->m_element = pRHSCurr->m_element;
            }
            m_size = rhs.m_size;
            /**
             * Don't need to allocate separate memory for m_pTail
             * This has been already done by the statement pHead->m_pNext = new SinglyNode();
             * above while iterating through the source list
             */
            m_pTail = pRHSCurr;
        }
    }

    void SinglyLinkedList::insertAtFront(const int val)
    {
        if (isEmpty())
        {
            auto pNewNode = new SinglyNode();
            pNewNode->m_element = val;
            m_pHead = pNewNode;
            m_pTail = m_pHead;
        }
        else
        {
            auto pNewNode = new SinglyNode();
            pNewNode->m_element = val;
            pNewNode->m_pNext = m_pHead;
            m_pHead = pNewNode;
        }
        ++m_size;
    }

    void SinglyLinkedList::insertAtBack(const int val)
    {
        if (isEmpty())
        {
            auto pNewNode = new SinglyNode();
            pNewNode->m_element = val;
            m_pHead = pNewNode;
            m_pTail = m_pHead;
        }
        else
        {
            auto pNewNode = new SinglyNode();
            pNewNode->m_element = val;
            m_pTail->m_pNext = pNewNode;
            m_pTail = m_pTail->m_pNext;
        }
        ++m_size;
    }

    void SinglyLinkedList::insertAtPos(const size_t pos, const int val)
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Item will be inserted at the fornt" << std::endl;
            insertAtFront(val);
        }
        else if (pos == 1)
        {
            insertAtFront(val);
        }
        else if (pos > m_size)
        {
            std::cout << std::endl << "The list is smaller than the pos desired. Item will be inserted at the back" << std::endl;
            insertAtBack(val);
        }
        else
        {
            auto pCurrNode = m_pHead;
            SinglyNode* pPrevNode = nullptr;
            for (size_t cnt = 0; cnt < pos; ++cnt)
            {
                pPrevNode = pCurrNode;
                pCurrNode = pCurrNode->m_pNext;
            }

            //std::cout << std::endl << "pCurrNode->m_element = " << pCurrNode->m_element << std::endl;

            auto pNewNode = new SinglyNode();
            pNewNode->m_element = val;

            pPrevNode->m_pNext = pNewNode;
            pNewNode->m_pNext = pCurrNode;
            ++m_size;
        }
    }

    void SinglyLinkedList::insertAtMiddle(const int val)
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Item will be inserted at the fornt" << std::endl;
            insertAtFront(val);
        }
        else if (1 == m_size)
        {
            std::cout << std::endl << "The list has only one element. Item will be inserted at the fornt" << std::endl;
            insertAtFront(val);
        }
        else
        {
            insertAtPos(m_size / 2, val);
        }
    }

    bool SinglyLinkedList::deleteAtFront()
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Nothing to delete" << std::endl;
            return false;
        }
        else if (size() == 1)
        {
            clearList();
            return true;
        }
        else
        {
            auto pForntNode = m_pHead;
            m_pHead = m_pHead->m_pNext;
            if (pForntNode)
                delete pForntNode;

            pForntNode = nullptr;
            --m_size;
            return true;
        }
    }

    bool SinglyLinkedList::deleteAtBack()
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Nothing to delete" << std::endl;
            return false;
        }
        else if (size() == 1)
        {
            clearList();
            return true;
        }
        else
        {
            auto pLastNode = m_pHead;
            SinglyNode* pPrevNode = nullptr;
            while (pLastNode->m_pNext)
            {
                pPrevNode = pLastNode;
                //std::cout << std::endl << "pLastNode->m_element = " << pLastNode->m_element << std::endl;
                pLastNode = pLastNode->m_pNext;
            }
            if (pLastNode)
                delete pLastNode;
            pLastNode = nullptr;

            pPrevNode->m_pNext = nullptr;
            m_pTail = pPrevNode;
            --m_size;
            return true;
        }
    }

    bool SinglyLinkedList::deleteAtPos(const size_t pos)
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Nothing to delete" << std::endl;
            return false;
        }
        else if (size() <= pos)
        {
            std::cout << std::endl << "The list is having only " << m_size << " elements. Nothing to delete" << std::endl;
            return false;
        }
        else if ((size() - 1) == pos)
        {
            deleteAtBack();
            return true;
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
            
            if (pDelNode)
                delete pDelNode;
            pDelNode = nullptr;

            --m_size;
            return true;
        }
    }

    bool SinglyLinkedList::deleteAtMiddle()
    {
        if (isEmpty())
        {
            std::cout << std::endl << "The list is empty. Nothing to delete" << std::endl;
            return false;
        }
        else
        {
            return deleteAtPos(size() / 2);
        }
    }

    void SinglyLinkedList::displayList() noexcept
    {
        if (isEmpty())
        {
            std::cout << "The list is empty. Nothing to display" << std::endl;
        }
        else
        {
            auto pHead = m_pHead;
            std::cout << std::endl;
            while (pHead)
            {
                std::cout << pHead->m_element;
                pHead = pHead->m_pNext;
                if (pHead)
                    std::cout << " --> ";
                else
                    std::cout << " --> NULL";
            }
            std::cout << std::endl;
        }
    }

    bool SinglyLinkedList::searchList(const int val) noexcept
    {
        if (isEmpty())
            return false;

        auto pHead = m_pHead;
        while(pHead)
        {
            if (pHead->m_element == val)
                return true;

            pHead = pHead->m_pNext;
        }
        return false;
    }
}