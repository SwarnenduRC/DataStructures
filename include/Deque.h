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
            /**
             * @brief Custom iterator structure for deque.
             *        It is a custom iterator which will enable the
             *        traversal of the deque much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             * 
             */
            struct iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = T;
                using pointer = value_type*;
                using reference = value_type&;

                iterator(const DoublyLinkedList<T>::iterator& itr) : m_itr(itr) {}
                iterator() = default;
                ~iterator() = default;
                iterator(const iterator&) = default;
                iterator& operator=(const iterator&) = default;
                iterator(iterator&&) = default;
                iterator& operator=(iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return iterator 
                 */
                iterator operator++(const int) noexcept
                {
                    iterator temp = *this;
                    m_itr++;
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return iterator& 
                 */
                iterator& operator++() noexcept
                {
                    ++m_itr;
                    return *this;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return iterator 
                 */
                iterator operator--(const int) noexcept
                {
                    iterator temp = *this;
                    m_itr--;
                    return temp;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return iterator& 
                 */
                iterator& operator--() noexcept
                {
                    --m_itr;
                    return *this;
                }
                bool operator==(const iterator& rhs) const noexcept
                {
                    return (m_itr == rhs.m_itr);
                }
                bool operator!=(const iterator& rhs) const noexcept
                {
                    return (m_itr != rhs.m_itr);
                }
                reference operator*() const noexcept  { auto& val = *m_itr; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itr.m_itrPtr; }
                
                private:
                    DoublyLinkedList<T>::iterator m_itr;
            };
            /**
             * @brief Custom reverse iterator structure for deque.
             *        It is a custom iterator which will enable the
             *        traversal of the deque much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             * 
             */
            struct reverse_iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = T;
                using pointer = value_type*;
                using reference = value_type&;

                reverse_iterator(const DoublyLinkedList<T>::iterator& itr) : m_itr(itr) {}
                reverse_iterator() = default;
                ~reverse_iterator() = default;
                reverse_iterator(const reverse_iterator&) = default;
                reverse_iterator& operator=(const reverse_iterator&) = default;
                reverse_iterator(reverse_iterator&&) = default;
                reverse_iterator& operator=(reverse_iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return reverse_iterator 
                 */
                reverse_iterator operator++(const int) noexcept
                {
                    reverse_iterator temp = *this;
                    m_itr++;
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return reverse_iterator& 
                 */
                reverse_iterator& operator++() noexcept
                {
                    ++m_itr;
                    return *this;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return reverse_iterator 
                 */
                reverse_iterator operator--(const int) noexcept
                {
                    reverse_iterator temp = *this;
                    m_itr--;
                    return temp;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return reverse_iterator& 
                 */
                reverse_iterator& operator--() noexcept
                {
                    --m_itr;
                    return *this;
                }
                bool operator==(const reverse_iterator& rhs) const noexcept
                {
                    return (m_itr == rhs.m_itr);
                }
                bool operator!=(const reverse_iterator& rhs) const noexcept
                {
                    return (m_itr != rhs.m_itr);
                }
                reference operator*() const noexcept  { auto& val = *m_itr; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itr.m_itrPtr; }
                
                private:
                    DoublyLinkedList<T>::iterator m_itr;
            };
            /**
             * @brief Custom constant iterator structure for deque.
             *        It is a custom iterator which will enable the
             *        traversal of the deque much hassle free and hides
             *        the internal pointer logic from the user thus user
             *        can use this directly for any supported standard
             *        algo as well as range based for loops.
             * 
             */
            struct const_iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = const T;
                using pointer = const value_type*;
                using reference = const value_type&;

                const_iterator(const DoublyLinkedList<T>::const_iterator& itr) : m_itr(itr) {}
                const_iterator() = default;
                ~const_iterator() = default;
                const_iterator(const const_iterator&) = default;
                const_iterator& operator=(const const_iterator&) = default;
                const_iterator(const_iterator&&) = default;
                const_iterator& operator=(const_iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return const_iterator 
                 */
                const_iterator operator++(const int) noexcept
                {
                    const_iterator temp = *this;
                    m_itr++;
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return const_iterator& 
                 */
                const_iterator& operator++() noexcept
                {
                    ++m_itr;
                    return *this;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return const_iterator 
                 */
                const_iterator operator--(const int) noexcept
                {
                    const_iterator temp = *this;
                    m_itr--;
                    return temp;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return const_iterator& 
                 */
                const_iterator& operator--() noexcept
                {
                    --m_itr;
                    return *this;
                }
                bool operator==(const const_iterator& rhs) const noexcept
                {
                    return (m_itr == rhs.m_itr);
                }
                bool operator!=(const const_iterator& rhs) const noexcept
                {
                    return (m_itr != rhs.m_itr);
                }
                reference operator*() const noexcept  { auto& val = *m_itr; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itr.m_itrPtr; }
                
                private:
                    DoublyLinkedList<T>::const_iterator m_itr;
            };
            struct const_reverse_iterator
            {
                /**
                 * @brief Some pre conditions which defines the
                 *        types and nature of this iterator
                 * 
                 */
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = const T;
                using pointer = const value_type*;
                using reference = const value_type&;

                const_reverse_iterator(const DoublyLinkedList<T>::const_iterator& itr) : m_itr(itr) {}
                const_reverse_iterator() = default;
                ~const_reverse_iterator() = default;
                const_reverse_iterator(const const_reverse_iterator&) = default;
                const_reverse_iterator& operator=(const const_reverse_iterator&) = default;
                const_reverse_iterator(const_reverse_iterator&&) = default;
                const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

                /**
                 * @brief Post increment operator
                 * 
                 * @return const_reverse_iterator 
                 */
                const_reverse_iterator operator++(const int) noexcept
                {
                    const_reverse_iterator temp = *this;
                    m_itr++;
                    return temp;
                }
                /**
                 * @brief Pre increment operator
                 * 
                 * @return const_reverse_iterator& 
                 */
                const_reverse_iterator& operator++() noexcept
                {
                    ++m_itr;
                    return *this;
                }
                /**
                 * @brief Post decrement operator
                 * 
                 * @return const_reverse_iterator 
                 */
                const_reverse_iterator operator--(const int) noexcept
                {
                    const_reverse_iterator temp = *this;
                    m_itr--;
                    return temp;
                }
                /**
                 * @brief Pre decrement operator
                 * 
                 * @return const_reverse_iterator& 
                 */
                const_reverse_iterator& operator--() noexcept
                {
                    --m_itr;
                    return *this;
                }
                bool operator==(const const_reverse_iterator& rhs) const noexcept
                {
                    return (m_itr == rhs.m_itr);
                }
                bool operator!=(const const_reverse_iterator& rhs) const noexcept
                {
                    return (m_itr != rhs.m_itr);
                }
                reference operator*() const noexcept  { auto& val = *m_itr; return val; }
                DoublyNode<T>* operator->()  const noexcept  { return m_itr.m_itrPtr; }
                
                private:
                    DoublyLinkedList<T>::const_iterator m_itr;
            };

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
            bool operator==(const Deque& rhs) const noexcept
            {
                return *Queue<T>::m_list == *rhs.Queue<T>::m_list;
            }
            bool operator!=(const Deque& rhs) const noexcept
            {
                return !(*Queue<T>::m_list == *rhs.Queue<T>::m_list);
            }
            inline bool empty()                 const noexcept              { return Queue<T>::empty();   }
            inline size_t size()                const noexcept              { return Queue<T>::size();    }
            inline bool find(const T& val)      const noexcept              { return Queue<T>::find(val); }
            inline void pop_front()             noexcept                    { return Queue<T>::pop();     }
            inline void push_back(const T& val)             				{ return Queue<T>::push(val); }
			inline T& front()                   const noexcept              { return Queue<T>::front();   }
            inline T& back()                    const noexcept              { return Queue<T>::back();    }
            inline void clear()                             				{ Queue<T>::clear();          }
            inline void swap(Deque<T>& rhs)                 				{ Queue<T>::swap(rhs);        }

            /**
             * @brief Various begin and end functions to get the iterators
             *        The direction which the list operates/traverses is
             *        opposite to the direction of deque traverses thus
             *        it is list's rbegin to deque's begin and so on
             */
            inline iterator begin()                    const noexcept { return iterator(Queue<T>::m_list->rbegin());               }
            inline iterator end()                      const noexcept { return iterator(Queue<T>::m_list->rend());                 }
            inline reverse_iterator rbegin()           const noexcept { return reverse_iterator(Queue<T>::m_list->begin());        }
            inline reverse_iterator rend()             const noexcept { return reverse_iterator(Queue<T>::m_list->end());          }
            inline const_iterator cbegin()             const noexcept { return const_iterator(Queue<T>::m_list->crbegin());        }
            inline const_iterator cend()               const noexcept { return const_iterator(Queue<T>::m_list->crend());          }
            inline const_reverse_iterator crbegin()    const noexcept { return const_reverse_iterator(Queue<T>::m_list->cbegin()); }
            inline const_reverse_iterator crend()      const noexcept { return const_reverse_iterator(Queue<T>::m_list->cend());   }

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