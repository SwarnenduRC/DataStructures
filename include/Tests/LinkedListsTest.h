#include <iostream>

/**
 * @brief 
 * 
 */
class Student
{
    public:
        Student() noexcept { std::cout << std::endl << m_name << "'s Constructor called" << std::endl << std::endl; }
        Student(const std::string& val) noexcept : m_name(val) { std::cout << std::endl << m_name << "'s Constructor called" << std::endl << std::endl; }
        ~Student() noexcept { std::cout << std::endl << m_name << "'s Destructor called" << std::endl << std::endl; }
        inline std::string getName() const noexcept { return m_name; }
        Student(const Student& rhs) = default;
        Student(Student&& rhs) = default;
        Student& operator = (const Student& rhs) = default;
        Student& operator = (Student&& rhs) = default;
        
        friend std::ostream& operator<<(std::ostream& os, const Student& obj)
        {
            os << obj.getName();
            return os;
        }

    private:
        std::string m_name;
};

/**
 * @brief 
 * 
 */
void testDoublyNode();

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
void testSinglyLinkedList(int argc, char** argv);