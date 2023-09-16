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
        std::weak_ptr<DoublyNode<T>> m_pPrev;

        explicit DoublyNode(const T& val) noexcept : m_data(val), m_pNext(nullptr) {}
        DoublyNode() = default;
        DoublyNode(const DoublyNode& rhs) noexcept
            : m_data(rhs.m_data)
            , m_pNext(new DoublyNode<T>(*rhs.m_pNext))
            , m_pPrev(rhs.m_pPrev)
        {
        }
        DoublyNode(DoublyNode&& rhs) noexcept
            : m_data(std::move_if_noexcept(rhs.m_data))
            , m_pNext(std::move_if_noexcept(rhs.m_pNext))
            , m_pPrev(rhs.m_pPrev)
        {
            rhs.m_pPrev.reset();
        }
        DoublyNode& operator=(const DoublyNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                m_pNext.reset(new DoublyNode<T>(*rhs.m_pNext));
                m_pPrev = rhs.m_pPrev;
            }
            return *this;
        }
        DoublyNode& operator=(DoublyNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                m_pNext.reset(new DoublyNode<T>(*rhs.m_pNext));
                m_pPrev = rhs.m_pPrev;
                rhs.m_pNext.reset();
                rhs.m_pPrev.reset();
            }
            return *this;
        }
        ~DoublyNode() = default;

        inline T getData() const noexcept { return m_data; }
        inline void setData(const T& val) noexcept { m_data = val; }
    };

    template<typename T>
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
            , m_pLeft(new TreeNode<T>(*rhs.m_pLeft))
            , m_pRight(new TreeNode<T>(*rhs.m_pRight))
        {}
        TreeNode(TreeNode&& rhs) noexcept
            : m_data(std::move_if_noexcept(rhs.m_data))
            , m_pLeft(std::move_if_noexcept(rhs.m_pLeft))
            , m_pRight(std::move_if_noexcept(rhs.m_pRight))
        {}
        TreeNode& operator=(const TreeNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = rhs.m_data;
                m_pLeft.reset(new TreeNode<T>(*rhs.m_pLeft));
                m_pRight.reset(new TreeNode<T>(*rhs.m_pRight));
            }
            return *this;
        }
        TreeNode& operator=(TreeNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                m_data = std::move_if_noexcept(m_data);
                m_pLeft.reset();
                m_pRight.reset();
                m_pLeft = std::move_if_noexcept(rhs.m_pLeft);
                m_pRight = std::move_if_noexcept(rhs.m_pRight);
            }
            return *this;
        }
    };
} // namespace swarnendu