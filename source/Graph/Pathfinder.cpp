#include <Graph/Pathfinder.h>

using namespace LGL;


Pathfinder::Pathfinder()
{

}

Pathfinder::Pathfinder(const Pathfinder& _other)
{
    m_graph = _other.m_graph;
    m_calculate_distance_func = _other.m_calculate_distance_func;
}

void Pathfinder::operator=(const Pathfinder& _other)
{
    m_graph = _other.m_graph;
    m_calculate_distance_func = _other.m_calculate_distance_func;
}


Pathfinder::Pathfinder(const Graph* _graph, const Distance_Calculation_Func& _calculate_distance_func)
{
    set_graph(_graph);
    set_distance_calculation_func(_calculate_distance_func);
}


Pathfinder::~Pathfinder()
{

}



unsigned int Pathfinder::M_find_closest(const Step_Node *_nodes, unsigned int _amount) const
{
    unsigned int result_id = _amount;

    for(unsigned int i=0; i<_amount; ++i)
    {
        if(_nodes[i].is_processed)
            continue;

        if(_nodes[i].distance_from_start < 0.0f)
            continue;

        result_id = i;
        break;
    }

    if(result_id == _amount)
        return result_id;

    for(unsigned int i=result_id; i<_amount; ++i)
    {
        if(_nodes[i].is_processed)
            continue;

        if(_nodes[i].distance_from_start < 0.0f)
            continue;

        if(_nodes[i] < _nodes[result_id])
            result_id = i;
    }

    return result_id;
}

void Pathfinder::M_update_neighbours(Step_Node* _nodes, unsigned int _id) const
{
    L_ASSERT(_nodes[_id].distance_from_start >= 0.0f);

    for(Graph_Node::Links_Map::Const_Iterator it = m_graph->nodes_links(_id).iterator(); !it.end_reached(); ++it)
    {
        const unsigned int neighbour_id = it.key();
        Step_Node& current_step_node = _nodes[neighbour_id];

        float distance_to_neighbour = *it;
        float distance_to_neighbour_from_start = _nodes[_id].distance_from_start + distance_to_neighbour;

        L_ASSERT(distance_to_neighbour_from_start > 0.0f);

        if(current_step_node.distance_from_start < 0.0f || (current_step_node.distance_from_start > distance_to_neighbour_from_start))
        {
            current_step_node.distance_from_start = distance_to_neighbour_from_start;
            current_step_node.previous = _id;
        }
    }
}

Pathfinder::Path Pathfinder::M_backtrace_path(const Step_Node *_nodes, unsigned int _start_id, unsigned int _finish_id) const
{
    unsigned int path_length = 0;

    unsigned int current_id = _finish_id;
    while(current_id != _start_id)
    {
        current_id = _nodes[current_id].previous;
        ++path_length;
    }

    Path result;
    result.resize(path_length);

    current_id = _finish_id;
    while(current_id != _start_id)
    {
        result.push(current_id);
        current_id = _nodes[current_id].previous;
    }

    unsigned int half = path_length / 2;
    for(unsigned int i=0; i<half; ++i)
        result.swap(i, path_length - i - 1);

    return result;
}



void Pathfinder::process(unsigned int _start_id, unsigned int _finish_id)
{
    L_ASSERT(m_graph && m_calculate_distance_func);
    L_ASSERT(_start_id < m_graph->nodes_amount() && _finish_id < m_graph->nodes_amount());

    m_path_result.clear();

    if(_start_id == _finish_id)
        return;

    const unsigned int nodes_amount = m_graph->nodes_amount();
    Step_Node* nodes = new Step_Node[nodes_amount];
    for(unsigned int i=0; i<nodes_amount; ++i)
        nodes[i].distance_to_finish = m_calculate_distance_func(i, _finish_id);

    unsigned int current_id = _start_id;
    nodes[current_id].distance_from_start = 0;
    do
    {
        nodes[current_id].is_processed = true;
        M_update_neighbours(nodes, current_id);

        current_id = M_find_closest(nodes, nodes_amount);
    }
    while(current_id != _finish_id && current_id != nodes_amount);

    if(current_id == _finish_id)
        m_path_result = M_backtrace_path(nodes, _start_id, _finish_id);

    delete[] nodes;
}
