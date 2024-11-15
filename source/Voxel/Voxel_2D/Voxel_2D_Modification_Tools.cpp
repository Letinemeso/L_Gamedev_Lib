#include <Voxel/Voxel_2D/Voxel_2D_Modification_Tools.h>

using namespace LGL;


bool LGL::apply_id_to_voxel_recursive(Voxel_2D* _voxel, const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id)
{
    if(!_voxel->is_split() && _voxel->id() == _id)
        return false;

    if(_should_apply_to_whole(_voxel))
    {
        if(_voxel->is_split())
            _voxel->merge();

        _voxel->set_id(_id);
        return true;
    }

    if(!_should_apply_partially(_voxel))
        return false;

    if(_voxel->reached_max_depth())
    {
        _voxel->set_id(_id);
        return true;
    }

    if(!_voxel->is_split())
        _voxel->split();

    bool result = false;
    for(unsigned int i=0; i<4; ++i)
    {
        if(apply_id_to_voxel_recursive(_voxel->child(i), _should_apply_to_whole, _should_apply_partially, _id))
            result = true;
    }

    return result;
}
