/**
 * @file DynamicArray.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <memory>
#include <array>
#include <exception>

namespace swarnendu
{
    template<typename T>
    class DyArray
    {
        public:
            DyArray() noexcept : m_pDataPtr(nullptr) {}
            DyArray(const size_t size) noexcept
                : m_pDataPtr(std::make_unique<T[]>(size))
                , m_size(size)
            {}
            ~DyArray() = default;
            DyArray(const DyArray& rhs) noexcept
            {
                copy(*this, rhs);
            }
            DyArray(DyArray&& rhs) noexcept
                : m_pDataPtr(std::move(rhs.m_pDataPtr))
                , m_size(std::move_if_noexcept(rhs.m_size))
            {
                rhs.m_size = 0;
            }
            DyArray& operator=(const DyArray& rhs) noexcept
            {
                if (this != &rhs)
                    copy(*this, rhs);
                return *this;
            }
            DyArray& operator=(DyArray&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    m_size = std::move_if_noexcept(rhs.m_size);
                    m_pDataPtr = std::move_if_noexcept(rhs.m_pDataPtr);
                    rhs.m_size = 0;
                }
                return *this;
            }
            inline bool empty() const noexcept { return (m_size == 0); }
            inline size_t size() const noexcept { return m_size; }
            inline T& operator[](const size_t pos)
            { 
                if (pos >= m_size)
                    throw std::out_of_range("Array size smaller than the index given");
            
                return m_pDataPtr[pos]; 
            }
            inline const T& operator[](const size_t pos) const
            { 
                if (pos >= m_size)
                    throw std::out_of_range("Array size smaller than the index given");
            
                return m_pDataPtr[pos]; 
            }
            inline void clear() noexcept
            {
                if (m_pDataPtr)
                    m_pDataPtr.reset();
                if (m_size != 0)
                    m_size = 0;
            }
            void resize(const size_t size)
            {
                if (!empty())
                {
                    clear();
                    if (size > 0)
                    {
                        m_size = size;
                        m_pDataPtr = std::make_unique<T[]>(m_size);
                    }
                }
            }

        private:
            void copy(DyArray& dest, const DyArray& src)
            {
                dest.clear();
                if (!src.empty())
                {
                    dest.m_size = src.size();
                    dest.m_pDataPtr = std::make_unique<T[]>(dest.m_size);
                    for (size_t cnt = 0; cnt < dest.m_size; ++cnt)
                        dest[cnt] = src[cnt];
                }
            }
            std::unique_ptr<T[]> m_pDataPtr;
            size_t m_size = 0;
    };
} // namespace swarnendu