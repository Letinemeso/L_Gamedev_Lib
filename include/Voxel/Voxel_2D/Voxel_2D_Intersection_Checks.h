#pragma once

#include <Voxel/Voxel_2D/Voxel_2D.h>


namespace LGL
{

    bool voxel_2d_inside_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius);
    bool voxel_2d_touches_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius);

    bool voxel_2d_inside_triangle(Voxel_2D* _voxel, const float* _vertex_0, const float* _vertex_1, const float* _vertex_2);
    bool voxel_2d_touches_triangle(Voxel_2D* _voxel, const float* _vertex_0, const float* _vertex_1, const float* _vertex_2);

}
