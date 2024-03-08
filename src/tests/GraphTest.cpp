#include "GraphTest.h"

static std::vector<std::pair<int, int>> data = { 
                                                std::make_pair(10, 5),
                                                std::make_pair(1, 3),
                                                std::make_pair(2, 4),
                                                std::make_pair(5, 7),
                                                std::make_pair(6, 8),
                                                std::make_pair(9, 10)
                                            };

static size_t expMtxSizeData = 11;

static std::vector<std::pair<int, int>> zeroBasedData = { 
                                                            std::make_pair(10, 5),
                                                            std::make_pair(1, 3),
                                                            std::make_pair(2, 4),
                                                            std::make_pair(5, 7),
                                                            std::make_pair(6, 8),
                                                            std::make_pair(9, 0)
                                                        };

static size_t expMtxSizeZeroBasedData = 10;
static size_t dataNodeCnt = 10;
static size_t dataEdgCnt = 5;

void GraphTest::testGraph(  const Graph& graph,
                            const std::vector<std::pair<int, int>>& data, 
                            const size_t expMatrixSize, 
                            const size_t expNodeCnt,
                            const size_t expEdgCnt
                        )
{
    EXPECT_EQ(expMatrixSize, graph.getAdjMatrix().size());
    EXPECT_EQ(expNodeCnt, graph.getNodeCnt());
    EXPECT_EQ(expEdgCnt, graph.getEdgeCnt());

    auto matrix = graph.getAdjMatrix();
    size_t idx = 1;
    while (idx < data.size())
    {
        EXPECT_NE(std::find(matrix[data[idx].first].cbegin(), matrix[data[idx].first].cend(), data[idx].second), matrix[data[idx].first].cend());
        EXPECT_NE(std::find(matrix[data[idx].second].cbegin(), matrix[data[idx].second].cend(), data[idx].first), matrix[data[idx].second].cend());
        ++idx;
    }
}


TEST_F(GraphTest, testDefaultConstructor)
{
    size_t expectedMatrixSize = 0;
    size_t expNodeCnt = 0;
    size_t expEdgCnt = 0;
    ASSERT_EQ(m_graph.getAdjMatrix().size(), expectedMatrixSize);
    ASSERT_EQ(expNodeCnt, m_graph.getNodeCnt());
    ASSERT_EQ(expEdgCnt, m_graph.getEdgeCnt());
    ASSERT_EQ(false, m_graph.zeroBased());
}

TEST_F(GraphTest, testParameterizedConstructor)
{
    Graph graph(data);
    testGraph(graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);
}

TEST_F(GraphTest, testFill)
{
    m_graph.fill(zeroBasedData, true);
    testGraph(m_graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);
}

TEST_F(GraphTest, testCopy)
{
    m_graph.fill(zeroBasedData, true);
    testGraph(m_graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);

    auto graph = m_graph;
    testGraph(graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);
}

TEST_F(GraphTest, testAssignment)
{
    {
        Graph graph(data);
        testGraph(graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);
        m_graph = graph;
    }
    testGraph(m_graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);
}

TEST_F(GraphTest, testMove)
{
    m_graph.fill(zeroBasedData, true);
    testGraph(m_graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);

    auto graph = std::move(m_graph);
    testGraph(graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);

    size_t expectedMatrixSize = 0;
    size_t expNodeCnt = 0;
    size_t expEdgCnt = 0;
    ASSERT_EQ(m_graph.getAdjMatrix().size(), expectedMatrixSize);
    ASSERT_EQ(expNodeCnt, m_graph.getNodeCnt());
    ASSERT_EQ(expEdgCnt, m_graph.getEdgeCnt());
    ASSERT_EQ(false, m_graph.zeroBased());
}

TEST_F(GraphTest, testMoveAssignment)
{
    m_graph.fill(zeroBasedData, true);
    testGraph(m_graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);

    Graph graph(data);
    testGraph(graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);

    graph = std::move(m_graph);
    testGraph(graph, zeroBasedData, expMtxSizeZeroBasedData, dataNodeCnt, dataEdgCnt);

    size_t expectedMatrixSize = 0;
    size_t expNodeCnt = 0;
    size_t expEdgCnt = 0;
    ASSERT_EQ(m_graph.getAdjMatrix().size(), expectedMatrixSize);
    ASSERT_EQ(expNodeCnt, m_graph.getNodeCnt());
    ASSERT_EQ(expEdgCnt, m_graph.getEdgeCnt());
    ASSERT_EQ(false, m_graph.zeroBased());
}

TEST_F(GraphTest, testAddEdge)
{
    m_graph.fill(data);
    testGraph(m_graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);
    auto matrix = m_graph.getAdjMatrix();
    ASSERT_EQ(std::find(matrix[2].cbegin(), matrix[2].cend(), 10), matrix[2].cend());
    ASSERT_EQ(std::find(matrix[10].cbegin(), matrix[10].cend(), 2), matrix[10].cend());

    m_graph.addEdge(std::make_pair(2, 10));
    matrix = m_graph.getAdjMatrix();
    ASSERT_EQ(matrix.size(), expMtxSizeData);
    ASSERT_EQ(dataNodeCnt, m_graph.getNodeCnt());
    ASSERT_EQ(dataEdgCnt + 1, m_graph.getEdgeCnt());
    ASSERT_NE(std::find(matrix[2].cbegin(), matrix[2].cend(), 10), matrix[2].cend());
    ASSERT_NE(std::find(matrix[10].cbegin(), matrix[10].cend(), 2), matrix[10].cend());
}

TEST_F(GraphTest, testRemoveEdge)
{
    m_graph.fill(data);
    testGraph(m_graph, data, expMtxSizeData, dataNodeCnt, dataEdgCnt);
    auto matrix = m_graph.getAdjMatrix();
    ASSERT_NE(std::find(matrix[2].cbegin(), matrix[2].cend(), 4), matrix[2].cend());
    ASSERT_NE(std::find(matrix[4].cbegin(), matrix[4].cend(), 2), matrix[4].cend());

    m_graph.removeEdge(std::make_pair(2, 4));
    matrix = m_graph.getAdjMatrix();
    ASSERT_EQ(matrix.size(), expMtxSizeData);
    ASSERT_EQ(dataNodeCnt, m_graph.getNodeCnt());
    ASSERT_EQ(dataEdgCnt - 1, m_graph.getEdgeCnt());
    ASSERT_EQ(std::find(matrix[2].cbegin(), matrix[2].cend(), 4), matrix[2].cend());
    ASSERT_EQ(std::find(matrix[4].cbegin(), matrix[4].cend(), 2), matrix[4].cend());
}

TEST_F(GraphTest, testBFS)
{
    m_graph.fill(data);
    {
        auto outPut = m_graph.getBFSList();
        std::vector<int> expOutPut = { 1, 3, 2, 4, 5, 7, 6, 8, 9, 10 };
        ASSERT_EQ(outPut.size(), expOutPut.size());
        for (size_t idx = 0; idx < expOutPut.size(); ++idx)
            EXPECT_EQ(outPut[idx], expOutPut[idx]) << outPut[idx];
    }
    m_graph.clear();
    m_graph.fill(zeroBasedData, true);
    {
        auto outPut = m_graph.getBFSList();
        std::vector<int> expOutPut = { 0, 9, 1, 3, 2, 4, 5, 7, 6, 8 };
        ASSERT_EQ(outPut.size(), expOutPut.size());
        for (size_t idx = 0; idx < expOutPut.size(); ++idx)
            EXPECT_EQ(outPut[idx], expOutPut[idx]) << outPut[idx];
    }
}

TEST_F(GraphTest, testDFS)
{
    m_graph.fill(data);
    m_graph.addEdge(std::make_pair(3, 2));
    m_graph.addEdge(std::make_pair(4, 6));
    {
        auto outPut = m_graph.getDFSList();
        std::vector<int> expOutPut = { 1, 3, 2, 4, 6, 8, 5, 7, 9, 10 };
        ASSERT_EQ(outPut.size(), expOutPut.size());
        for (size_t idx = 0; idx < expOutPut.size(); ++idx)
            EXPECT_EQ(outPut[idx], expOutPut[idx]) << outPut[idx];
    }
    m_graph.clear();
    m_graph.fill(zeroBasedData, true);
    m_graph.addEdge(std::make_pair(3, 2));
    m_graph.addEdge(std::make_pair(4, 6));
    {
        auto outPut = m_graph.getDFSList();
        std::vector<int> expOutPut = { 0, 9, 1, 3, 2, 4, 6, 8, 5, 7 };
        ASSERT_EQ(outPut.size(), expOutPut.size());
        for (size_t idx = 0; idx < expOutPut.size(); ++idx)
            EXPECT_EQ(outPut[idx], expOutPut[idx]) << outPut[idx];
    }
}

