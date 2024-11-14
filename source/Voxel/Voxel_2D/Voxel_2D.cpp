#include <Voxel/Voxel_2D/Voxel_2D.h>

using namespace LGL;


Voxel_2D::Voxel_2D(Voxel_2D* _parent, unsigned int _max_depth, unsigned int _depth, unsigned int _id, float _position_x, float _position_y, float _size_x, float _size_y)
    : m_parent(_parent), m_max_depth(_max_depth), m_depth(_depth), m_id(_id), m_position_x(_position_x), m_position_y(_position_y), m_size_x(_size_x), m_size_y(_size_y)
{

}

Voxel_2D::~Voxel_2D()
{
    for(unsigned int i=0; i<4; ++i)
        delete m_childs[i];
}



bool Voxel_2D::should_be_merged() const
{
    if(!is_split())
        return false;

    for(unsigned int i=0; i<4; ++i)
    {
        if(m_childs[i]->is_split())
            return false;
    }

    unsigned int first_child_id = m_childs[0]->id();
    for(unsigned int i=1; i<4; ++i)
    {
        if(m_childs[i]->id() != first_child_id)
            return false;
    }

    return true;
}



void Voxel_2D::M_merge_voxel_tree_if_needed()
{
    if(!m_parent)
        return;

    if(!m_parent->should_be_merged())
        return;

    Voxel_2D* parent = m_parent;
    unsigned int id = m_id;

    m_parent->merge();

    parent->set_id(id);
}



void Voxel_2D::split()
{
    L_ASSERT(!is_split());
    L_ASSERT(can_be_split());

    float size_x_halved = m_size_x * 0.5f;
    float size_y_halved = m_size_y * 0.5f;

    m_childs[0] = new Voxel_2D(this, m_max_depth, m_depth + 1, m_id, m_position_x, m_position_y, size_x_halved, size_y_halved);
    m_childs[1] = new Voxel_2D(this, m_max_depth, m_depth + 1, m_id, m_position_x + size_x_halved, m_position_y, size_x_halved, size_y_halved);
    m_childs[2] = new Voxel_2D(this, m_max_depth, m_depth + 1, m_id, m_position_x, m_position_y + size_y_halved, size_x_halved, size_y_halved);
    m_childs[3] = new Voxel_2D(this, m_max_depth, m_depth + 1, m_id, m_position_x + size_x_halved, m_position_y + size_y_halved, size_x_halved, size_y_halved);
}

void Voxel_2D::merge()
{
    L_ASSERT(is_split());

    for(unsigned int i=0; i<4; ++i)
    {
        delete m_childs[i];
        m_childs[i] = nullptr;
    }
}
