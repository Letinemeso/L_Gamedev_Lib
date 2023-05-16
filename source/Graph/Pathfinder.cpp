#include <Graph/Pathfinder.h>

using namespace LGL;


Pathfinder::Pathfinder()
{

}

Pathfinder::Pathfinder(const Pathfinder& _other)
{
    m_graph = _other.m_graph;
}


Pathfinder::Pathfinder(const Graph* _graph, LST::Function<unsigned int(unsigned int, unsigned int)> _calculate_distance_func)
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

    for(unsigned int i=0; i<_amount && result_id == _amount; ++i)
        if(!_nodes[i].is_processed && _nodes[i].is_being_processed)
            result_id = i;

    for(unsigned int i=result_id; i<_amount; ++i)
    {
        if(_nodes[i].is_processed || !_nodes[i].is_being_processed)
            continue;

        if(_nodes[i] < _nodes[result_id])
            result_id = i;
    }

    return result_id;
}

void Pathfinder::M_update_neighbours(Step_Node* _nodes, unsigned int _id) const
{
    for(LDS::Map<unsigned int, unsigned int>::Const_Iterator it = m_graph->nodes_links(_id).iterator(); !it.end_reached(); ++it)
    {
        const unsigned int neighbour_id = it.key();
        unsigned int distance_to_neighbour = *it;

        if(_nodes[neighbour_id].is_processed)
            continue;

        unsigned int distance_to_neighbour_from_start = _nodes[_id].distance_from_start + distance_to_neighbour;

        if(!_nodes[neighbour_id].is_being_processed)
            _nodes[neighbour_id].is_being_processed = true;

        if(_nodes[neighbour_id].distance_from_start > distance_to_neighbour_from_start)
        {
            _nodes[neighbour_id].distance_from_start = distance_to_neighbour_from_start;
            _nodes[neighbour_id].previous = _id;
        }
    }
}

LDS::Vector<unsigned int> Pathfinder::M_backtrace_path(const Step_Node *_nodes, unsigned int _start_id, unsigned int _finish_id) const
{
    unsigned int path_length = 0;

    unsigned int current_id = _finish_id;
    while(current_id != _start_id)
    {
        current_id = _nodes[current_id].previous;
        ++path_length;
    }

    LDS::Vector<unsigned int> result;
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

    nodes[_start_id].is_processed = true;
//    for(LDS::Map<unsigned int, unsigned int>::Const_Iterator it = m_graph->nodes_links(_start_id).iterator(); !it.end_reached(); ++it)
//    {
//        nodes[*it].is_being_processed = true;
//        nodes[*it].previous = _start_id;
//    }
    M_update_neighbours(nodes, _start_id);

    unsigned int current_id = _start_id;
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
