/**
 * @file Stack.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <algorithm>
#include <memory>

#include "DoublyLinkedList.h"

using swarnendu::DoublyLinkedList;

namespace swarnendu
{
    template<typename T>
    class Stack
    {
        public:
            Stack() noexcept
                : m_list(new DoublyLinkedList<T>())
                , m_size(m_list->size())
            {}
            Stack(const Stack& rhs) noexcept
                : m_list(std::make_unique<DoublyLinkedList<T>>(*rhs.m_list))
                , m_size(rhs.m_size)
            {
            }
            Stack(Stack&& rhs) noexcept
                : m_list(std::move_if_noexcept(rhs.m_list))
                , m_size(std::move_if_noexcept(rhs.m_size))
            {
                rhs.m_size = 0;
            }
            Stack& operator=(const Stack& rhs) noexcept
            {
                if (&rhs != this)
                {
                    clear();
                    m_list.reset(new DoublyLinkedList<T>(*rhs.m_list));
                    m_size = rhs.m_size;
                }
                return *this;
            }
            Stack& operator=(Stack&& rhs) noexcept
            {
                if (&rhs != this)
                {
                    clear();
                    m_list = std::move_if_noexcept(rhs.m_list);
                    m_size = std::move_if_noexcept(rhs.m_size);
                    rhs.m_size = 0;
                }
                return *this;
            }
            ~Stack() noexcept
            {
                if (m_list)
                    clear();
            }
            void push(const T& val)
            {
                m_list->push_back(val);
                m_size = m_list->size();
            }
            inline T top() const noexcept
            {
                if (!empty())
                    return m_list->getFront();
                return T();
            }
            void pop()
            {
                if (!empty())
                {
                    m_list->pop_front();
                    m_size = m_list->size();
                }
            }
            inline bool empty() const noexcept { return (m_size ? false : true); }
            inline size_t size() const noexcept { return m_size; }
            inline bool find(const T& val) const noexcept { return m_list->find(val); }
            void clear()
            {
                if (!empty())
                {
                    m_list->clear();
                    m_list.reset();
                    m_size = 0;
                }
            }
            void display() const noexcept
            {
                if (!empty())
                    m_list->display();
                else
                    std::cout << std::endl << std::endl << "It is an empty stack" << std::endl << std::endl;
            }
        
        private:
            std::unique_ptr<DoublyLinkedList<T>> m_list;
            size_t m_size;
    };
} // namespace swarnendu