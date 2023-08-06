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

            void clearList();            
            void insertAtFront(const int val);
            void insertAtBack(const int val);
            void insertAtPos(const size_t pos, const int val);
            void insertAtMiddle(const int val);

            bool deleteAtFront();
            bool deleteAtBack();
            bool deleteAtPos(const size_t pos);
            bool deleteAtMiddle();

            void displayList() noexcept;
            bool isExists(const int val) noexcept;
            inline bool isEmpty() noexcept { return m_size ? false : true; }
            inline size_t size() noexcept { return m_size; }

        private:
            void copyList(const SinglyLinkedList& rhs) noexcept;
            SinglyNode* m_pHead = nullptr;
            SinglyNode* m_pTail = nullptr;
            size_t m_size = 0;
    };
}