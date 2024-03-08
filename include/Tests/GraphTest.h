#include "Graph.h"

#include <gtest/gtest.h>

using swarnendu::Graph;

class GraphTest : public ::testing::Test
{
    public:
        void testGraph( const Graph& graph,
                        const std::vector<std::pair<int, int>>& data, 
                        const size_t expMatrixSize, 
                        const size_t expNodeCnt,
                        const size_t expEdgCnt
                    );
    protected:
        Graph m_graph;
};