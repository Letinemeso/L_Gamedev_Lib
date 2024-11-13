#include <Voxel/Voxel_2D/Voxel_2D_Controller.h>

#include <cmath>

using namespace LGL;


Voxel_2D_Controller::Voxel_2D_Controller()
{

}

Voxel_2D_Controller::~Voxel_2D_Controller()
{
    for(Voxel_List::Iterator it = m_voxels.begin(); !it.end_reached(); ++it)
    {
        Voxel_Data& voxel_data = *it;
        delete voxel_data.voxel;
    }
}



typename Voxel_2D_Controller::Voxel_List::Iterator Voxel_2D_Controller::M_find_voxel(Voxel_2D* _voxel)
{
    for(Voxel_List::Iterator it = m_voxels.begin(); !it.end_reached(); ++it)
    {
        Voxel_Data& voxel_data = *it;

        if(voxel_data.voxel == _voxel)
            return it;
    }
    return {};
}

typename Voxel_2D_Controller::Voxel_List::Iterator Voxel_2D_Controller::M_find_voxel(int _index_x, int _index_y)
{
    for(Voxel_List::Iterator it = m_voxels.begin(); !it.end_reached(); ++it)
    {
        Voxel_Data& voxel_data = *it;

        if(voxel_data.index_x == _index_x && voxel_data.index_y == _index_y)
            return it;
    }
    return {};
}



void Voxel_2D_Controller::insert_voxel(Voxel_2D* _voxel)
{
    L_ASSERT(!M_find_voxel(_voxel).is_ok());
    L_ASSERT(fabs(m_expected_voxel_size_x - _voxel->size_x()) < 0.0001f);
    L_ASSERT(fabs(m_expected_voxel_size_y - _voxel->size_y()) < 0.0001f);

    Voxel_Data voxel_data;

    voxel_data.index_x = _voxel->position_x() / m_expected_voxel_size_x;
    voxel_data.index_y = _voxel->position_y() / m_expected_voxel_size_y;
    L_ASSERT(!M_find_voxel(voxel_data.index_x, voxel_data.index_y).is_ok());

    voxel_data.voxel = _voxel;

    m_voxels.push_back(voxel_data);
}

void Voxel_2D_Controller::remove_voxel(Voxel_2D* _voxel)
{
    Voxel_List::Iterator voxel_it = M_find_voxel(_voxel);
    L_ASSERT(voxel_it.is_ok());

    m_voxels.erase(voxel_it);
}

void Voxel_2D_Controller::remove_voxel(int _index_x, int _index_y)
{
    Voxel_List::Iterator voxel_it = M_find_voxel(_index_x, _index_y);
    L_ASSERT(voxel_it.is_ok());

    Voxel_Data& voxel_data = *voxel_it;
    delete voxel_data.voxel;

    m_voxels.erase(voxel_it);
}



void Voxel_2D_Controller::M_apply_id_to_voxel_recursive(Voxel_2D* _voxel, const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id)
{
    if(_should_apply_to_whole(_voxel))
    {
        if(_voxel->is_split())
            _voxel->merge();

        _voxel->set_id(_id);
        return;
    }

    if(!_should_apply_partially(_voxel))
        return;

    if(_voxel->reached_max_depth())
    {
        _voxel->set_id(_id);
        return;
    }

    if(!_voxel->is_split())
        _voxel->split();

    for(unsigned int i=0; i<4; ++i)
        M_apply_id_to_voxel_recursive(_voxel->child(i), _should_apply_to_whole, _should_apply_partially, _id);
}



void Voxel_2D_Controller::apply_id_to_voxels(const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id)
{
    L_ASSERT(_should_apply_to_whole);
    L_ASSERT(_should_apply_partially);

    for(Voxel_List::Iterator it = m_voxels.begin(); !it.end_reached(); ++it)
        M_apply_id_to_voxel_recursive(it->voxel, _should_apply_to_whole, _should_apply_partially, _id);
}



void Voxel_2D_Controller::update()
{
    for(Voxel_List::Iterator it = m_voxels.begin(); !it.end_reached(); ++it)
    {
        Voxel_Data& voxel_data = *it;
    }
}
