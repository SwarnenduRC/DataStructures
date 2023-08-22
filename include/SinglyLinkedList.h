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

namespace swarnendu
{
    using swarnendu_nodes::SinglyNode;

    class SinglyLinkedList
    {
        public:
            SinglyLinkedList() = default;
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

            bool pop_front();
            bool pop_back();
            bool pop_at(const size_t pos);
            bool pop_middle();

            void display() noexcept;
            bool find(const int val) noexcept;
            inline bool empty() noexcept { return m_size ? false : true; }
            inline size_t size() noexcept { return m_size; }

        private:
            void copyList(const SinglyLinkedList& rhs) noexcept;
            SinglyNode* m_pHead = nullptr;
            SinglyNode* m_pTail = nullptr;
            size_t m_size = 0;
    };
} // namespace swarnendu