/**
 * @brief 
 * 
 */

#include <iostream>
#include <string>

class Employee
{
    public:
        Employee() = default;
        Employee(const std::string& val) noexcept : m_name(val) {}
        ~Employee() = default;
        inline std::string getName() const noexcept { return m_name; }
        Employee(const Employee& rhs) = default;
        Employee(Employee&& rhs) = default;
        Employee& operator = (const Employee& rhs) = default;
        Employee& operator = (Employee&& rhs) = default;
        
        friend std::ostream& operator<<(std::ostream& os, const Employee& obj)
        {
            os << obj.getName();
            return os;
        }

    private:
        std::string m_name;
};

void testQueue();