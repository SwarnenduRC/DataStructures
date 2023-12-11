/**
 * @file Deque.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef DEQUE_H
#define DEQUE_H

#include "Queue.h"

using swarnendu::Queue;

namespace swarnendu
{
    template<typename T>
    class Deque : public Queue<T>
    {
        public:
            Deque() = default;
            ~Deque() = default;
            Deque(const std::initializer_list<T>& iList) noexcept
                : Queue<T>(iList)
            {}
            Deque(const Deque& rhs) noexcept
                : Queue<T>(rhs)
            {}
            Deque(Deque&& rhs) noexcept
                : Queue<T>(std::move(rhs))
            {}
            Deque& operator=(const Deque& rhs) noexcept
            {
                if (&rhs != this)
                {
                    Queue<T>::operator=(rhs);
                }
                return *this;
            }
            Deque& operator=(Deque&& rhs) noexcept
            {
                if (&rhs != this)
                {
                    Queue<T>::operator=(std::move(rhs));
                }
                return *this;
            }
            inline bool empty() const noexcept              { return Queue<T>::empty();   }
            inline size_t size() const noexcept             { return Queue<T>::size();    }
            inline bool find(const T& val) const noexcept   { return Queue<T>::find(val); }
            inline void pop_front() noexcept                { return Queue<T>::pop();     }
            inline void push_back(const T& val)             { return Queue<T>::push(val); }
            inline T& front() const noexcept                { return Queue<T>::front();   }
            inline T& back() const noexcept                 { return Queue<T>::back();    }
            inline void clear()                             { Queue<T>::clear();          }
            inline void swap(Deque<T>& rhs)                 { Queue<T>::swap(rhs);        }

            void push_front(const T& val)
            {
                if (!Queue<T>::m_list)
                    Queue<T>::m_list = std::make_unique<DoublyLinkedList<T>>();

                Queue<T>::m_list->push_back(val);
                Queue<T>::m_size = Queue<T>::m_list->size();
            }
            void pop_back() noexcept
            {
                if (!empty())
                {
                    Queue<T>::m_list->pop_front();
                    Queue<T>::m_size = Queue<T>::m_list->size();
                }
            }
            void assign(__SIZE_TYPE__ count, const T& val)
            {
                if (!count)
                    return;

                clear();
                for (__SIZE_TYPE__ idx = 0; idx < count; ++idx)
                    Queue<T>::push(val);
            }
            template<typename InputIt>
            void assign(InputIt first, InputIt last)
            {
                if (first == last)
                    return;

                clear();
                for (auto it = first; it != last; ++it)
                    Queue<T>::push(*it);
            }
            void assign(const std::initializer_list<T>& iList)
            {
                if (!iList.size())
                    return;

                clear();
                for (const auto& element : iList)
                    Queue<T>::push(element);
            }
            void resize(const size_t count)
            {
                if (size() == count)
                    return;

                else if (size() > count)
                {
                    while (size() != count)
                        pop_back();
                }
                else
                {
                    while (size() != count)
                        push_back(T{});
                }
            }
            void resize(const size_t count, const T& val)
            {
                if (size() == count)
                    return;

                else if (size() > count)
                {
                    while (size() != count)
                        pop_back();
                }
                else
                {
                    while (size() != count)
                        push_back(val);
                }
            }
    };
}

#endif