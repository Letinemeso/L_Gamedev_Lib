#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <Data_Structures/Vector.h>
#include <Stuff/Function_Wrapper.h>

#include <Graph/Graph.h>


namespace LGL
{

    class Pathfinder final
    {
    private:
        struct Step_Node final
        {
        public:
            unsigned int previous = 0xFFFFFFFF;

            unsigned int distance_from_start = 0xFFFFFFFF;
            unsigned int distance_to_finish = 0;

            bool is_processed = false;
            bool is_being_processed = false;

        public:
            inline bool operator<(const Step_Node& _other) const
            {
                unsigned int this_total_value = distance_to_finish + distance_from_start;
                unsigned int other_total_value = _other.distance_to_finish + _other.distance_from_start;

                if(this_total_value < other_total_value)
                    return true;
                else if(this_total_value > other_total_value)
                    return false;
                return distance_to_finish < _other.distance_to_finish;
            }
            inline bool operator>(const Step_Node& _other) const
            {
                return !(*this < _other);
            }
        };

    private:
        const Graph* m_graph = nullptr;
        LST::Function<unsigned int(unsigned int, unsigned int)> m_calculate_distance_func;

    private:
        LDS::Vector<unsigned int> m_path_result;

    public:
        Pathfinder();
        Pathfinder(const Pathfinder& _other);
        void operator=(const Pathfinder& _other);

        Pathfinder(const Graph* _graph, LST::Function<unsigned int(unsigned int, unsigned int)> _calculate_distance_func);

        ~Pathfinder();

    public:
        inline void set_graph(const Graph* _graph) { m_graph = _graph; }
        inline void set_distance_calculation_func(const LST::Function<unsigned int(unsigned int, unsigned int)> _calculate_distance_func) { m_calculate_distance_func = _calculate_distance_func; }

    public:
        inline const LDS::Vector<unsigned int>& path_result() const { return m_path_result; }

    private:
        unsigned int M_find_closest(const Step_Node* _nodes, unsigned int _amount) const;
        void M_update_neighbours(Step_Node* _nodes, unsigned int _id) const;
        LDS::Vector<unsigned int> M_backtrace_path(const Step_Node* _nodes, unsigned int _start_id, unsigned int _finish_id) const;

    public:
        void process(unsigned int _start_id, unsigned int _finish_id);

    };

}

#endif // PATHFINDER_H
