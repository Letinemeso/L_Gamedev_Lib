#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <Graph/Graph.h>


namespace LGL
{

    class Pathfinder final
    {
    private:
        const Graph* m_graph = nullptr;

    private:
        struct Node final
        {
            unsigned int m_step_id = 0;

            Node* m_possible_branches = nullptr;
            unsigned int m_possible_branches_amount = 0;
        };

    private:
        Node* m_path_start = nullptr;

    public:


    };

}

#endif // PATHFINDER_H
