#include "Graph.h"

#include <queue>
#include <stack>

using swarnendu::Graph;

Graph::Graph(const std::vector<StdPair>& data, const bool zeroBased)
{
    fill(data, zeroBased);
}

Graph::Graph(Graph&& rhs) noexcept
    : m_nodeCnt(rhs.m_nodeCnt)
    , m_edgeCnt(rhs.m_edgeCnt)
    , m_bZeroBased(rhs.m_bZeroBased)
    , m_adjacencyMatrix(std::move(rhs.m_adjacencyMatrix))
{
    rhs.m_nodeCnt = 0;
    rhs.m_edgeCnt = 0;
    rhs.m_bZeroBased = false;
}

Graph& Graph::operator=(Graph&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_nodeCnt = rhs.m_nodeCnt;
        m_edgeCnt = rhs.m_edgeCnt;
        m_bZeroBased = rhs.m_bZeroBased;
        m_adjacencyMatrix = std::move(rhs.m_adjacencyMatrix);

        rhs.m_nodeCnt = 0;
        rhs.m_edgeCnt = 0;
        rhs.m_bZeroBased = false;
    }
    return *this;
}

void Graph::fill(const std::vector<StdPair>& data, const bool zeroBased)
{
    if (data.empty() || data.size() < 2)
        return;

    m_nodeCnt = static_cast<size_t>(data[0].first);
    m_edgeCnt = static_cast<size_t>(data[0].second);
    m_bZeroBased = zeroBased;
    
    size_t idx = 1;
    if (m_bZeroBased)
    {
        m_adjacencyMatrix.resize(m_nodeCnt);
    }
    else
    {
        m_adjacencyMatrix.resize(m_nodeCnt + 1);
        m_adjacencyMatrix[0].resize(0);
    }
    while (idx < data.size())
    {
        m_adjacencyMatrix[data[idx].first].emplace_back(data[idx].second);
        m_adjacencyMatrix[data[idx].second].emplace_back(data[idx].first);
        ++idx;
    }
}

void Graph::clear() noexcept
{
    if (!m_adjacencyMatrix.empty())
    {
        for (auto& neighbours : m_adjacencyMatrix)
            neighbours.clear();

        m_adjacencyMatrix.clear();        
    }
}

void Graph::addEdge(const StdPair& data) noexcept
{
    if (!m_adjacencyMatrix.empty() && 
        data.first <= static_cast<int>(m_adjacencyMatrix.size()) && 
        data.second <= static_cast<int>(m_adjacencyMatrix.size()))
    {
        if (std::find(m_adjacencyMatrix[data.first].cbegin(), m_adjacencyMatrix[data.first].cend(), data.second) 
            == m_adjacencyMatrix[data.first].cend())
        {
            m_adjacencyMatrix[data.first].emplace_back(data.second);
            m_adjacencyMatrix[data.second].emplace_back(data.first);
            ++m_edgeCnt;
        }
    }
}

void Graph::addEdges(const std::vector<StdPair>& data) noexcept
{
    if (!data.empty() && !m_adjacencyMatrix.empty())
    {
        for (const auto& dataItm : data)
            addEdge(dataItm);
    }
}

void Graph::removeEdge(const StdPair& data) noexcept
{
    if (!m_adjacencyMatrix.empty())
    {
        auto secondNode = std::find(m_adjacencyMatrix[data.first].cbegin(), m_adjacencyMatrix[data.first].cend(), data.second);
        auto firstNode = std::find(m_adjacencyMatrix[data.second].cbegin(), m_adjacencyMatrix[data.second].cend(), data.first);
        
        if (secondNode != m_adjacencyMatrix[data.first].cend() && firstNode != m_adjacencyMatrix[data.second].cend())
        {
            m_adjacencyMatrix[data.first].erase(secondNode);
            m_adjacencyMatrix[data.second].erase(firstNode);
            --m_edgeCnt;
        }
    }
}

void Graph::removeEdges(const std::vector<StdPair>& data) noexcept
{
    if (!data.empty() && !m_adjacencyMatrix.empty())
    {
        for (const auto& dataItm : data)
            removeEdge(dataItm);
    }
}

std::vector<int> Graph::getBFSList() const noexcept
{
    if (!getNodeCnt() || !getEdgeCnt())
        return std::vector<int>{};

    std::queue<int> nodeQ;
    std::vector<int> outVec;
    auto arrSize = m_adjacencyMatrix.size();
    bool visitedArr[arrSize];
    std::fill(visitedArr, visitedArr + arrSize, false);
    size_t idx = m_bZeroBased ? 0 : 1;
    nodeQ.push(idx);

    while (idx < arrSize)
    {
        while (!nodeQ.empty())
        {
            auto data = nodeQ.front();
            nodeQ.pop();
            if (!visitedArr[data])
            {
                visitedArr[data] = true;
                outVec.emplace_back(data);
            }
            for (const auto& neighbours : m_adjacencyMatrix[data])
            {
                if (!visitedArr[neighbours])
                    nodeQ.push(neighbours);
            }
        }
        ++idx;
        if (!visitedArr[idx])
            nodeQ.push(idx);
    }
    return outVec;
}

std::vector<int> Graph::getDFSList() const noexcept
{
    if (!getNodeCnt() || !getEdgeCnt())
        return std::vector<int>{};

    std::stack<int> nodeStack;
    std::vector<int> outVec;
    auto arrSize = m_adjacencyMatrix.size();
    bool visitedArr[arrSize];
    std::fill(visitedArr, visitedArr + arrSize, false);
    size_t idx = m_bZeroBased ? 0 : 1;
    nodeStack.push(idx);

    while (idx < arrSize)
    {
        while (!nodeStack.empty())
        {
            auto data = nodeStack.top();
            nodeStack.pop();
            if (!visitedArr[data])
            {
                visitedArr[data] = true;
                outVec.emplace_back(data);
            }
            for (const auto& neighbours : m_adjacencyMatrix[data])
            {
                if (!visitedArr[neighbours])
                    nodeStack.push(neighbours);
            }
        }
        ++idx;
        if (!visitedArr[idx])
            nodeStack.push(idx);
    }
    return outVec;
}

