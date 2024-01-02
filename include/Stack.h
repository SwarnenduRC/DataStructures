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

#include <algorithm>
#include <memory>
#include <exception>

#include "DoublyLinkedList.h"

using swarnendu::DoublyLinkedList;

namespace swarnendu
{
    template<typename T>
    class Stack
    {
        public:
            Stack() = default;
            Stack(const std::initializer_list<T>& iList) noexcept
                : m_list(nullptr)
                , m_size(0)
            {
                if (iList.size())
                {
                    for (const auto val : iList)
                        push(val);
                }
            }
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
                if (!m_list)
                    m_list = std::make_unique<DoublyLinkedList<T>>();

                m_list->push_front(val);
                m_size = m_list->size();
            }
            T& top() const
            {
                if (empty())
                    throw std::out_of_range("The stack is empty");
                
                return m_list->getHead()->m_data;
            }
            void pop()
            {
                if (empty())
                    throw std::out_of_range("The stack is empty");

                m_list->pop_front();
                m_size = m_list->size();
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
            void swap(Stack& rhs)
            {
                if (this != &rhs)
                {
                    auto temp = std::move(*this);
                    *this = std::move(rhs);
                    rhs = std::move(temp);
                }
            }
        
        private:
            std::unique_ptr<DoublyLinkedList<T>> m_list = nullptr;
            size_t m_size = 0;
    };
} // namespace swarnendu