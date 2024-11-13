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


bool point_inside_triangle(const float* p, const float* a, const float* b, const float* c)
{
    auto sign = [](const float p1[2], const float p2[2], const float p3[2])
    {
        return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1]);
    };

    float d1 = sign(p, a, b);
    float d2 = sign(p, b, c);
    float d3 = sign(p, c, a);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool LGL::voxel_2d_inside_triangle(Voxel_2D* _voxel, const float* _vertex_0, const float* _vertex_1, const float* _vertex_2)
{
    float rectCorners[4][2] = {
        {_voxel->position_x(),                     _voxel->position_y()},
        {_voxel->position_x() + _voxel->size_x(),  _voxel->position_y()},
        {_voxel->position_x() + _voxel->size_x(),  _voxel->position_y() + _voxel->size_y()},
        {_voxel->position_x(),                     _voxel->position_y() + _voxel->size_y()}
    };

    for (const auto& corner : rectCorners)
    {
        if (!point_inside_triangle(corner, _vertex_0, _vertex_1, _vertex_2))
            return false;
    }

    return true;
}

int orientation(const float* p, const float* q, const float* r)
{
    float val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

bool segments_intersect(const float* p1, const float* q1, const float* p2, const float* q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    return false;
}

bool LGL::voxel_2d_touches_triangle(Voxel_2D* _voxel, const float* _vertex_0, const float* _vertex_1, const float* _vertex_2)
{
    float rectCorners[4][2] = {
        {_voxel->position_x(),                     _voxel->position_y()},
        {_voxel->position_x() + _voxel->size_x(),  _voxel->position_y()},
        {_voxel->position_x() + _voxel->size_x(),  _voxel->position_y() + _voxel->size_y()},
        {_voxel->position_x(),                     _voxel->position_y() + _voxel->size_y()}
    };

    const float* triangleEdges[3][2] = {{_vertex_0, _vertex_1}, {_vertex_1, _vertex_2}, {_vertex_2, _vertex_0}};
    for (const auto& edge : triangleEdges)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (segments_intersect(edge[0], edge[1], rectCorners[i], rectCorners[(i + 1) % 4]))
                return true;
        }
    }

    auto point_inside_voxel = [_voxel](const float* _point)
    {
        if(_point[0] < _voxel->position_x() && _point[0] > _voxel->position_x() * _voxel->size_x())
            return false;
        if(_point[1] < _voxel->position_y() && _point[1] > _voxel->position_y() * _voxel->size_y())
            return false;

        return true;
    };

    if(point_inside_voxel(_vertex_0))
        return true;
    if(point_inside_voxel(_vertex_1))
        return true;
    if(point_inside_voxel(_vertex_2))
        return true;

    return false;
}
