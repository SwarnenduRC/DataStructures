/**
 * @file Queue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <exception>
#include <algorithm>
#include <memory>
#include <initializer_list>

#include "DoublyLinkedList.h"

using swarnendu::DoublyLinkedList;

namespace swarnendu
{
    template<typename T>
    class Queue
    {
        public:
            Queue() = default;
            Queue(const std::initializer_list<T>& iList) noexcept
                : m_list(nullptr)
                , m_size(0)
            {
                if (iList.size())
                {
                    for (const auto& element : iList)
                        push(element);
                }
            }
            Queue(const Queue& rhs) noexcept
                : m_list(std::make_unique<DoublyLinkedList<T>>(*rhs.m_list))
                , m_size(rhs.m_size)
            {
            }
            Queue(Queue&& rhs) noexcept
                : m_list(std::move_if_noexcept(rhs.m_list))
                , m_size(std::move_if_noexcept(rhs.m_size))
            {
                rhs.m_size = 0;
            }
            Queue& operator=(const Queue& rhs) noexcept
            {
                if (&rhs != this)
                {
                    clear();
                    m_list = std::make_unique<DoublyLinkedList<T>>(*rhs.m_list);
                    m_size = rhs.m_size;
                }
                return *this;
            }
            Queue& operator=(Queue&& rhs) noexcept
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
            virtual ~Queue() noexcept
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
            inline T& front() const
            {
                if (empty())
                    throw std::out_of_range("The queue is empty");
                
                return m_list->getTail()->m_data;
            }
            inline T& back() const
            {
                if (empty())
                    throw std::out_of_range("The queue is empty");
                    
                return m_list->getHead()->m_data;
            }
            void pop() noexcept
            {
                if (!empty())
                {
                    m_list->pop_back();
                    m_size = m_list->size();
                }
            }
            void swap(Queue<T>& rhs)
            {
                if (this != &rhs)
                {
                    auto temp = std::move(*this);
                    *this = std::move(rhs);
                    rhs = std::move(temp);
                }
            }
            inline bool empty() const noexcept { return (m_size ? false : true); }
            inline size_t size() const noexcept { return m_size; }
            inline bool find(const T& val) const noexcept { return std::get<0>(m_list->find(val)); }
            void clear()
            {
                if (!empty())
                {
                    m_list->clear();
                    m_list.reset();
                    m_size = 0;
                }
            }
        
        protected:
            std::unique_ptr<DoublyLinkedList<T>> m_list = nullptr;
            size_t m_size = 0;
    };
} // namespace swarnendu

#endif
