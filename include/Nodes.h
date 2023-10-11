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
#ifndef NODES_H
#define NODES_H 1

#include <cstdint>
#include <cstddef>
#include <memory>
#include <type_traits>

namespace swarnendu_nodes
{
    struct SinglyNode
    {
        int m_element = 0;
        SinglyNode* m_pNext = nullptr;

        SinglyNode() = default;
        explicit SinglyNode(const int val) noexcept
            : m_element(val)
            , m_pNext(nullptr)
        {}
        ~SinglyNode() noexcept
        {
            m_element = 0;
            if (m_pNext)
                delete m_pNext;
            m_pNext = nullptr;
        }
        SinglyNode(const SinglyNode& rhs) noexcept
            : m_element(rhs.m_element)
            , m_pNext(nullptr)
        {
            if (rhs.m_pNext)
                m_pNext = new SinglyNode(*rhs.m_pNext);
        }
        SinglyNode& operator=(const SinglyNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                if (m_pNext)
                    delete m_pNext;
                m_pNext = nullptr;
                m_element = rhs.m_element;
                if (rhs.m_pNext)
                    m_pNext = new SinglyNode(*rhs.m_pNext);
            }
            return *this;
        }
        SinglyNode(SinglyNode&& rhs) noexcept
            : m_element(std::move_if_noexcept(rhs.m_element))
            , m_pNext(std::move_if_noexcept(rhs.m_pNext))
        {
            rhs.m_element = 0;
            rhs.m_pNext = nullptr;
        }
        SinglyNode& operator=(SinglyNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                if (m_pNext)
                    delete m_pNext;
                
                m_pNext = std::move_if_noexcept(rhs.m_pNext);
                m_element = std::move_if_noexcept(rhs.m_element);
                rhs.m_element = 0;
                rhs.m_pNext = nullptr;
            }
            return *this;
        }
    };
    template<typename T = int>
    struct DoublyNode
    {
        T m_data;
        std::shared_ptr<DoublyNode<T> > m_pNext;
        std::weak_ptr<DoublyNode<T> > m_pPrev;

        explicit DoublyNode(const T& val) noexcept 
            : m_data(val)
            , m_pNext(nullptr) 
        {}
        DoublyNode() = default;
        DoublyNode(const DoublyNode& rhs) noexcept
            : m_data(rhs.m_data)
            , m_pNext(nullptr)
            , m_pPrev(rhs.m_pPrev)
        {
            if (rhs.m_pNext)
                m_pNext = std::make_shared<DoublyNode<T>>(*rhs.m_pNext);
        }
        DoublyNode(DoublyNode&& rhs) noexcept
            : m_data(std::move_if_noexcept(rhs.m_data))
            , m_pNext(nullptr)
            , m_pPrev(rhs.m_pPrev)
        {
            if (rhs.m_pNext)
                m_pNext = std::move_if_noexcept(rhs.m_pNext);

            rhs.m_pPrev.reset();
            if (std::is_integral<T>::value)     //Only for testing purpose
                rhs.setData(0);
        }
        DoublyNode& operator=(const DoublyNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;                
                if (rhs.m_pNext)
                    m_pNext.reset(new DoublyNode<T>(*rhs.m_pNext));
                else
                    m_pNext.reset();
                m_pPrev = rhs.m_pPrev;
            }
            return *this;
        }
        DoublyNode& operator=(DoublyNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                
                if (rhs.m_pNext)
                    m_pNext = std::move_if_noexcept(rhs.m_pNext);
                else
                    m_pNext.reset();

                m_pPrev = rhs.m_pPrev;
                rhs.m_pPrev.reset();
                if (std::is_integral<T>::value)     //Only for testing purpose
                    rhs.setData(0);
            }
            return *this;
        }
        ~DoublyNode() = default;

        inline T getData() const noexcept { return m_data; }
        inline void setData(const T& val) noexcept { m_data = val; }
    };

    template<typename T = int>
    struct TreeNode
    {
        T m_data;
        std::unique_ptr<TreeNode> m_pLeft;
        std::unique_ptr<TreeNode> m_pRight;

        TreeNode() = default;
        ~TreeNode() = default;
        explicit TreeNode(const T& data) noexcept 
            : m_data(data)
            , m_pLeft(nullptr)
            , m_pRight(nullptr) 
        {}
        TreeNode(const TreeNode& rhs) noexcept
            : m_data(rhs.m_data)
            , m_pLeft(nullptr)
            , m_pRight(nullptr)
        {
            if (rhs.m_pLeft)
                m_pLeft.reset(new TreeNode<T>(*rhs.m_pLeft));

            if (rhs.m_pRight)
                m_pRight.reset(new TreeNode<T>(*rhs.m_pRight));
        }
        TreeNode(TreeNode&& rhs) noexcept
            : m_data(std::move_if_noexcept(rhs.m_data))
            , m_pLeft(nullptr)
            , m_pRight(nullptr)
        {
            if (rhs.m_pLeft)
                m_pLeft = std::move_if_noexcept(rhs.m_pLeft);

            if (rhs.m_pRight)
                m_pRight = std::move_if_noexcept(rhs.m_pRight);
        }
        TreeNode& operator=(const TreeNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                if (rhs.m_pLeft)
                    m_pLeft.reset(new TreeNode<T>(*rhs.m_pLeft));
                else
                    m_pLeft.reset();

                if (rhs.m_pRight)
                    m_pRight.reset(new TreeNode<T>(*rhs.m_pRight));
                else
                    m_pRight.reset();
            }
            return *this;
        }
        TreeNode& operator=(TreeNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = std::move_if_noexcept(rhs.m_data);
                m_pLeft.reset();
                m_pRight.reset();
                if (rhs.m_pLeft)m_pLeft.reset();
                    m_pLeft = std::move_if_noexcept(rhs.m_pLeft);

                if (rhs.m_pRight)
                    m_pRight = std::move_if_noexcept(rhs.m_pRight);
            }
            return *this;
        }
    };
} // namespace swarnendu_nodes

#endif