#pragma once

#include <Data_Structures/Map.h>


namespace LGL
{

    class Graph_Node final
    {
    public:
        using Links_Map = LDS::Map<unsigned int, float>;    //  key: node index, value: distance

    private:
        unsigned int m_id = 0;
        Links_Map m_linked_with;

    public:
        inline void set_id(unsigned int _id) { m_id = _id; }

    public:
        inline unsigned int id() const { return m_id; }
        inline unsigned int connections_amount() const { return m_linked_with.size(); }
        inline const Links_Map& connections() const { return m_linked_with; }

    public:
        void link_with(unsigned int _id, float _distance);
        void unlink_with(unsigned int _id);
        void unlink_with_all();

    public:
        float distance_if_linked(unsigned int _id) const;

    };

}
