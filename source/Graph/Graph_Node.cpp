#include <Graph/Graph_Node.h>

using namespace LGL;


void Graph_Node::link_with(unsigned int _id)
{
    L_ASSERT(!linked_with(_id) && m_id != _id);

    m_linked_with.insert(_id);
}

void Graph_Node::unlink_with(unsigned int _id)
{
    LDS::AVL_Tree<unsigned int>::Iterator it = m_linked_with.find(_id);
    L_ASSERT(it.is_ok());

    m_linked_with.erase(it);
}

void Graph_Node::unlink_with_all()
{
    m_linked_with.clear();
}



bool Graph_Node::linked_with(unsigned int _id) const
{
    LDS::AVL_Tree<unsigned int>::Const_Iterator it = m_linked_with.find(_id);
    return it.is_ok();
}
