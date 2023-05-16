#include <Graph/Graph_Node.h>

using namespace LGL;


void Graph_Node::link_with(unsigned int _id, unsigned int _distance)
{
    L_ASSERT(distance_if_linked(_id) == 0 && m_id != _id && _distance > 0);

    m_linked_with.insert(_id, _distance);
}

void Graph_Node::unlink_with(unsigned int _id)
{
    LDS::Map<unsigned int, unsigned int>::Iterator it = m_linked_with.find(_id);
    L_ASSERT(it.is_ok());

    m_linked_with.erase(it);
}

void Graph_Node::unlink_with_all()
{
    m_linked_with.clear();
}



unsigned int Graph_Node::distance_if_linked(unsigned int _id) const
{
    LDS::Map<unsigned int, unsigned int>::Const_Iterator it = m_linked_with.find(_id);
    if(!it.is_ok())
        return 0;
    return *it;
}
