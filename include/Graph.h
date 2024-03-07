#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

namespace swarnendu
{
    class Graph
    {
        using StdPair = std::pair<int, int>;
        using Matrix = std::vector<std::vector<int>>;
        
        public:
            Graph() = default;
            ~Graph() = default;
            Graph(const Graph& rhs) = default;
            Graph& operator=(const Graph& rhs) = default;
            Graph(Graph&& rhs) noexcept;
            Graph& operator=(Graph&& rhs) noexcept;
            Graph(const std::vector<StdPair>& data, const bool zeroBased = false);

            void fill(const std::vector<StdPair>& data, const bool zeroBased = false);
            void clear() noexcept;
            void addEdge(const StdPair& data) noexcept;
            void addEdges(const std::vector<StdPair>& data) noexcept;
            void removeEdge(const StdPair& data) noexcept;
            void removeEdges(const std::vector<StdPair>& data) noexcept;

            std::vector<int> getBFSList() const noexcept;
            std::vector<int> getDFSList() const noexcept;

            inline size_t getNodeCnt()      const noexcept   { return m_nodeCnt;         }
            inline size_t getEdgeCnt()      const noexcept   { return m_edgeCnt;         }
            inline bool   zeroBased()       const noexcept   { return m_bZeroBased;      }
            inline Matrix getAdjMatrix()    const noexcept   { return m_adjacencyMatrix; }

        private:
            size_t m_nodeCnt = 0;
            size_t m_edgeCnt = 0;
            bool m_bZeroBased = false;
            Matrix m_adjacencyMatrix;
    };
}   // namespace swarnendu

#endif  // _GRAPH_H_