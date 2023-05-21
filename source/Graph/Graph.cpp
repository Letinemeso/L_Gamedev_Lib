#include <Graph/Graph.h>

using namespace LGL;


Graph::Graph()
{

}

Graph::Graph(const Graph& _other)
{
    m_nodes_amount = _other.m_nodes_amount;
    m_nodes = new Graph_Node[m_nodes_amount];
    for(unsigned int i=0; i < m_nodes_amount; ++i)
        m_nodes[i] = _other.m_nodes[i];
}

Graph::Graph(Graph&& _other)
{
    m_nodes_amount = _other.m_nodes_amount;
    _other.m_nodes_amount = 0;
    m_nodes = _other.m_nodes;
    _other.m_nodes = nullptr;
}


Graph::~Graph()
{
    delete[] m_nodes;
}



void Graph::clear()
{
    delete[] m_nodes;
    m_nodes = nullptr;
}

void Graph::allocate_nodes(unsigned int _amount)
{
    m_nodes_amount = _amount;
    m_nodes = new Graph_Node[m_nodes_amount];
    for(unsigned int i=0; i < m_nodes_amount; ++i)
        m_nodes[i].set_id(i);
}


void Graph::link_nodes(unsigned int _id_1, unsigned int _id_2, unsigned int _distance, bool _mutually)
{
    L_ASSERT(_id_1 < m_nodes_amount && _id_2 < m_nodes_amount);

    m_nodes[_id_1].link_with(_id_2, _distance);
    if(_mutually)
        m_nodes[_id_2].link_with(_id_1, _distance);
}

void Graph::unlink_nodes(unsigned int _id_1, unsigned int _id_2, bool _mutually)
{
    L_ASSERT(_id_1 < m_nodes_amount && _id_2 < m_nodes_amount);

    m_nodes[_id_1].unlink_with(_id_2);
    if(_mutually)
        m_nodes[_id_2].unlink_with(_id_1);
}



unsigned int Graph::distance_if_linked(unsigned int _id_1, unsigned int _id_2) const
{
    L_ASSERT(_id_1 < m_nodes_amount && _id_2 < m_nodes_amount);

    return m_nodes[_id_1].distance_if_linked(_id_2);
}

unsigned int Graph::nodes_links_amount(unsigned int _id) const
{
    L_ASSERT(_id < m_nodes_amount);

    return m_nodes[_id].connections_amount();
}

const LDS::Map<unsigned int, unsigned int>& Graph::nodes_links(unsigned int _id) const
{
    L_ASSERT(_id < m_nodes_amount);

    return m_nodes[_id].connections();
}
