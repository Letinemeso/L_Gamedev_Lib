#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <Data_Structures/Map.h>


namespace LGL
{

    class Graph_Node final
    {
    private:
        unsigned int m_id = 0;
        LDS::Map<unsigned int, unsigned int> m_linked_with;

    public:
        inline void set_id(unsigned int _id) { m_id = _id; }

    public:
        inline unsigned int id() const { return m_id; }
        inline unsigned int connections_amount() const { return m_linked_with.size(); }
        inline const LDS::Map<unsigned int, unsigned int>& connections() const { return m_linked_with; }

    public:
        void link_with(unsigned int _id, unsigned int _distance);
        void unlink_with(unsigned int _id);
        void unlink_with_all();

    public:
        unsigned int distance_if_linked(unsigned int _id) const;

    };

}

#endif // GRAPH_NODE_H
