#include <Graph/Graph_Node.h>

using namespace LGL;


void Graph_Node::link_with(unsigned int _id, float _distance)
{
    L_ASSERT(distance_if_linked(_id) <= 0.0f && m_id != _id && _distance > 0.0f);

    m_linked_with.insert(_id, _distance);
}

void Graph_Node::unlink_with(unsigned int _id)
{
    Links_Map::Iterator it = m_linked_with.find(_id);
    L_ASSERT(it.is_ok());

    m_linked_with.erase(it);
}

void Graph_Node::unlink_with_all()
{
    m_linked_with.clear();
}



float Graph_Node::distance_if_linked(unsigned int _id) const
{
    Links_Map::Const_Iterator it = m_linked_with.find(_id);
    if(!it.is_ok())
        return -1.0f;
    return *it;
}
