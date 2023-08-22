/**
 * @file Nodes.h
 * @author Swarnendu Roy Chowdhury (swarnendu.rc@gmail.com)
 * @brief The header file which holds various node types
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdint>
#include <cstddef>
#include <memory>

namespace swarnendu_nodes
{
    struct SinglyNode
    {
        int m_element;
        SinglyNode* m_pNext = nullptr;
    };
    template<typename T>
    struct DoublyNode
    {
        T m_data;
        std::shared_ptr<DoublyNode<T>> m_pNext;
        std::shared_ptr<DoublyNode<T>> m_pPrev;

        DoublyNode(const T& val) noexcept : m_data(val), m_pNext(nullptr), m_pPrev(nullptr) {}
        DoublyNode() = default;
        DoublyNode(const DoublyNode& rhs) noexcept 
            : m_data(rhs.m_data)
            , m_pNext(new DoublyNode<T>(*rhs.m_pNext))
            , m_pPrev(new DoublyNode<T>(*rhs.m_pPrev))
        {
        }
        DoublyNode(DoublyNode&& rhs) noexcept
            : m_data(std::move(rhs.m_data))
            , m_pNext(new DoublyNode<T>(*rhs.m_pNext))
            , m_pPrev(new DoublyNode<T>(*rhs.m_pPrev))
        {
            rhs.m_pNext.reset();
            rhs.m_pPrev.reset();
        }
        DoublyNode& operator=(const DoublyNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                m_pNext.reset(new DoublyNode<T>(*rhs.m_pNext));
                m_pPrev.reset(new DoublyNode<T>(*rhs.m_pPrev));
            }
            return *this;
        }
        DoublyNode& operator=(DoublyNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                m_pNext.reset(new DoublyNode<T>(*rhs.m_pNext));
                m_pPrev.reset(new DoublyNode<T>(*rhs.m_pPrev));
                rhs.m_pNext.reset();
                rhs.m_pPrev.reset();
            }
            return *this;
        }
        ~DoublyNode() = default;

        inline T getData() const noexcept { return m_data; }
        inline void setData(const T& val) noexcept { m_data = val; }
    };
} // namespace swarnendu