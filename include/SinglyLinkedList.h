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
            /**
             * @brief Makes the list cyclic
             *        This function makes the linked ist
             *        a cyclic one by making next of m_pTail
             *        pointing back to m_pHead
             */
            void makeCyclic();
            /**
             * @brief Reverses a linked list
             *        Reverses a linked list in O(N) time
             */
            void reverse();

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

            /**
             * @brief Detects whether the given linked list is cyclic in nature or not
             *        A static function to detect whether the given linked list is
             *        cyclic in nature or not. It uses two pointers solution or 
             *        Floyd's cycle finding algorithm, also known as "tortoise and hare"
             *        algorithm
             * 
             * @param pHead The head of the linked list
             * @return true If the list is cyclic, 
             * @return false otherwise
             */
            static bool isCyclic(SinglyNode* pHead);

            /**
             * @brief Checks if there is an intersection between the two linked lists
             *        A static function to check if the linked lists in question are
             *        intersected or not. Throws a std runtime exception if one of the
             *        given list cyclic in nature
             * 
             * @param pHead1 The head pointer of the first list
             * @param pHead2 The head pointer of the second list
             * @return true If the lists are inter connected, 
             * @return false otherwise
             */
            static bool areListsIntersected(SinglyNode* pHead1, SinglyNode* pHead2);

        private:
            SinglyNode* m_pHead = nullptr;
            SinglyNode* m_pTail = nullptr;
            size_t m_size = 0;
    };
} // namespace swarnendu