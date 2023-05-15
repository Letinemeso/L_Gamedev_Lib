#ifndef GRAPH_H
#define GRAPH_H

#include <Graph/Graph_Node.h>


namespace LGL
{

    class Graph final
    {
    private:
        Graph_Node* m_nodes = nullptr;
        unsigned int m_nodes_amount = 0;

    public:
        Graph();
        Graph(const Graph& _other);
        Graph(Graph&& _other);

        ~Graph();

    public:
        inline unsigned int nodes_amount() const { return m_nodes_amount; }

    public:
        void clear();
        void allocate_nodes(unsigned int _amount);

        void link_nodes(unsigned int _id_1, unsigned int _id_2, bool _mutually = true);
        void unlink_nodes(unsigned int _id_1, unsigned int _id_2);

    public:
        bool have_connection(unsigned int _id_1, unsigned int _id_2) const;
        unsigned int nodes_amount_of_connections(unsigned int _id) const;

    };

}

#endif // GRAPH_H
