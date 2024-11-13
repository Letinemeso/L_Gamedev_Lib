#include <Voxel/Voxel_2D/Voxel_2D_Intersection_Checks.h>

using namespace LGL;


bool LGL::voxel_2d_inside_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius)
{
    float radius_squared = _circle_radius * _circle_radius;

    float left_squared = _voxel->position_x() - _circle_center[0];
    left_squared *= left_squared;
    float right_squared = _voxel->position_x() + _voxel->size_x() - _circle_center[0];
    right_squared *= right_squared;
    float bottom_squared = _voxel->position_y() - _circle_center[1];
    bottom_squared *= bottom_squared;
    float top_squared = _voxel->position_y() + _voxel->size_y() - _circle_center[1];
    top_squared *= top_squared;

    if(left_squared + bottom_squared > radius_squared)
        return false;
    if(right_squared + bottom_squared > radius_squared)
        return false;
    if(left_squared + top_squared > radius_squared)
        return false;
    if(right_squared + top_squared > radius_squared)
        return false;

    return true;
}

bool LGL::voxel_2d_touches_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius)
{
    float radius_squared = _circle_radius * _circle_radius;

    if(((_voxel->position_x() - _circle_center[0]) * (_voxel->position_y() - _circle_center[1])) <= radius_squared)
        return true;
    if(((_voxel->position_x() + _voxel->size_x() - _circle_center[0]) * (_voxel->position_y() - _circle_center[1])) <= radius_squared)
        return true;
    if(((_voxel->position_x() - _circle_center[0]) * (_voxel->position_y() + _voxel->size_y() - _circle_center[1])) <= radius_squared)
        return true;
    if(((_voxel->position_x() + _voxel->size_x() - _circle_center[0]) * (_voxel->position_y() + _voxel->size_y() - _circle_center[1])) <= radius_squared)
        return true;

    if(_circle_center[0] < _voxel->position_x() && _circle_center[0] > _voxel->position_x() * _voxel->size_x())
        return false;
    if(_circle_center[1] < _voxel->position_y() && _circle_center[1] > _voxel->position_y() * _voxel->size_y())
        return false;

    return true;
}
