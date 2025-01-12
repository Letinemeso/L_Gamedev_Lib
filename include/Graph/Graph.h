#pragma once

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
        void operator=(const Graph& _other);
        void operator=(Graph&&  _other);

        ~Graph();

    public:
        inline unsigned int nodes_amount() const { return m_nodes_amount; }

    public:
        void clear();
        void allocate_nodes(unsigned int _amount);

        void link_nodes(unsigned int _id_1, unsigned int _id_2, float _distance, bool _mutually = true);
        void unlink_nodes(unsigned int _id_1, unsigned int _id_2, bool _mutually = true);

    public:
        float distance_if_linked(unsigned int _id_1, unsigned int _id_2) const;
        unsigned int nodes_links_amount(unsigned int _id) const;
        const Graph_Node::Links_Map& nodes_links(unsigned int _id) const;

    };

}
