#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <Data_Structures/AVL_Tree.h>


namespace LGL
{

    class Graph_Node final
    {
    private:
        unsigned int m_id = 0;
        LDS::AVL_Tree<unsigned int> m_linked_with;    //  this stuff is stored in AVL_Tree for quick search of link presence

    public:
        inline void set_id(unsigned int _id) { m_id = _id; }

    public:
        inline unsigned int id() const { return m_id; }
        inline unsigned int connections_amount() const { return m_linked_with.size(); }

    public:
        void link_with(unsigned int _id);
        void unlink_with(unsigned int _id);
        void unlink_with_all();

    public:
        bool linked_with(unsigned int _id) const;

    };

}

#endif // GRAPH_NODE_H
