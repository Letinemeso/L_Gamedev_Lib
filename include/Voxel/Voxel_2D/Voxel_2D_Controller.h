#pragma once

#include <Data_Structures/List.h>

#include <Voxel/Voxel_2D/Voxel_2D.h>


namespace LGL
{

    class Voxel_2D_Controller
    {
    public:
        struct Voxel_Data
        {
            int index_x = 0;
            int index_y = 0;
            Voxel_2D* voxel = nullptr;
        };

    public:
        using Voxel_List = LDS::List<Voxel_Data>;

    private:
        Voxel_List m_voxels;

        float m_expected_voxel_size_x = 0.0f;
        float m_expected_voxel_size_y = 0.0f;

    public:
        Voxel_2D_Controller();
        ~Voxel_2D_Controller();

    public:
        inline const Voxel_List& voxel_list() const { return m_voxels; }

        inline void set_expected_voxel_size(float _x, float _y) { m_expected_voxel_size_x = _x; m_expected_voxel_size_y = _y; }

        inline float expected_voxel_size_x() const { return m_expected_voxel_size_x; }
        inline float expected_voxel_size_y() const { return m_expected_voxel_size_y; }

    private:
        Voxel_List::Iterator M_find_voxel(Voxel_2D* _voxel);
        Voxel_List::Iterator M_find_voxel(int _index_x, int _index_y);

    public:
        void insert_voxel(Voxel_2D* _voxel);
        void remove_voxel(Voxel_2D* _voxel);
        void remove_voxel(int _index_x, int _index_y);

    public:
        void update();

    };

}
