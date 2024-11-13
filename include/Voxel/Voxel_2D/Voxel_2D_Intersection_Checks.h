#pragma once

#include <Voxel/Voxel_2D/Voxel_2D.h>


namespace LGL
{

    bool voxel_2d_inside_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius);
    bool voxel_2d_touches_circle(Voxel_2D* _voxel, const float* _circle_center, float _circle_radius);

}
