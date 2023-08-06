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

namespace swarnendu_nodes
{
    struct SinglyNode
    {
        int m_element;
        SinglyNode* m_pNext = nullptr;
    };
}