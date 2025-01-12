#pragma once

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

            float distance_from_start = -1.0f;
            float distance_to_finish = 0.0f;

            bool is_processed = false;
            bool is_being_processed = false;

        public:
            inline bool operator<(const Step_Node& _other) const
            {
                float this_total_value = distance_to_finish + distance_from_start;
                float other_total_value = _other.distance_to_finish + _other.distance_from_start;

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

    public:
        using Distance_Calculation_Func = LST::Function<float(unsigned int, unsigned int)>;

    private:
        const Graph* m_graph = nullptr;
        Distance_Calculation_Func m_calculate_distance_func;

    public:
        using Path = LDS::Vector<unsigned int>;

    private:
        Path m_path_result;

    public:
        Pathfinder();
        Pathfinder(const Pathfinder& _other);
        void operator=(const Pathfinder& _other);

        Pathfinder(const Graph* _graph, const Distance_Calculation_Func& _calculate_distance_func);

        ~Pathfinder();

    public:
        inline void set_graph(const Graph* _graph) { m_graph = _graph; }
        inline void set_distance_calculation_func(const Distance_Calculation_Func& _calculate_distance_func) { m_calculate_distance_func = _calculate_distance_func; }

    public:
        inline const Path& path_result() const { return m_path_result; }

    private:
        unsigned int M_find_closest(const Step_Node* _nodes, unsigned int _amount) const;
        void M_update_neighbours(Step_Node* _nodes, unsigned int _id) const;
        Path M_backtrace_path(const Step_Node* _nodes, unsigned int _start_id, unsigned int _finish_id) const;

    public:
        void process(unsigned int _start_id, unsigned int _finish_id);

    };

}
