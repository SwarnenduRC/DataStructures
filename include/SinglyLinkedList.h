/**
 * @file SinglyLinkedList.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Nodes.h"

#include <initializer_list>

namespace swarnendu
{
    using swarnendu_nodes::SinglyNode;

    class SinglyLinkedList
    {
        public:
            SinglyLinkedList() = default;
            SinglyLinkedList(const std::initializer_list<int>& list);
            ~SinglyLinkedList();
            SinglyLinkedList(const SinglyLinkedList& rhs) noexcept;
            SinglyLinkedList(SinglyLinkedList&& rhs) noexcept;
            SinglyLinkedList& operator=(const SinglyLinkedList& rhs) noexcept;
            SinglyLinkedList& operator=(SinglyLinkedList&& rhs) noexcept;

            void clear();            
            void push_front(const int val);
            void push_back(const int val);
            void push_at(const size_t pos, const int val);
            void push_middle(const int val);

            int pop_front();
            int pop_back();
            int pop_at(const size_t pos);
            int pop_middle();

            void copy(const SinglyLinkedList& rhs);
            int* find(const int val) const noexcept;
            inline bool empty() const noexcept { return m_size ? false : true; }
            inline size_t size() const noexcept { return m_size; }
            inline SinglyNode* getHead() const noexcept { return m_pHead; }
            inline SinglyNode* getTail() const noexcept { return m_pTail; }

        private:
            SinglyNode* m_pHead = nullptr;
            SinglyNode* m_pTail = nullptr;
            size_t m_size = 0;
    };
} // namespace swarnendu