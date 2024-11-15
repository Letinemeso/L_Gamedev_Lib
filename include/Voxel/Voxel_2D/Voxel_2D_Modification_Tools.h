#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Voxel/Voxel_2D/Voxel_2D.h>


namespace LGL
{

    using Voxel_Intersection_Check_Func = LST::Function<bool(Voxel_2D*)>;


    bool apply_id_to_voxel_recursive(Voxel_2D* _voxel, const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id);

}
