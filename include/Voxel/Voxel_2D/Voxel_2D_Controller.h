#pragma once

#include <Data_Structures/List.h>
#include <Stuff/Function_Wrapper.h>

#include <Voxel/Voxel_2D/Voxel_2D.h>
#include <Voxel/Voxel_2D/Voxel_2D_Serializer.h>


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
        using Voxel_Intersection_Check_Func = LST::Function<bool(Voxel_2D*)>;

    private:
        Voxel_List m_voxels;

        float m_expected_voxel_size_x = 0.0f;
        float m_expected_voxel_size_y = 0.0f;
        unsigned int m_expected_max_depth = 1;

    private:
        Voxel_2D_Serializer m_serializer;
        std::string m_save_folder;
        std::string m_save_name;
        unsigned int m_loaded_voxels_amount_from_center = 10;

    public:
        Voxel_2D_Controller();
        ~Voxel_2D_Controller();

    public:
        inline const Voxel_List& voxel_list() const { return m_voxels; }

        inline void set_expected_voxel_size(float _x, float _y) { m_expected_voxel_size_x = _x; m_expected_voxel_size_y = _y; }
        inline void set_expected_max_depth(unsigned int _value) { m_expected_max_depth = _value; }
        inline void set_save_folder(const std::string& _value) { m_save_folder = _value; }
        inline void set_save_name(const std::string& _value) { m_save_name = _value; }

        inline float expected_voxel_size_x() const { return m_expected_voxel_size_x; }
        inline float expected_voxel_size_y() const { return m_expected_voxel_size_y; }
        inline unsigned int expected_max_depth() const { return m_expected_max_depth; }

    private:
        Voxel_List::Iterator M_find_voxel(Voxel_2D* _voxel);
        Voxel_List::Iterator M_find_voxel(int _index_x, int _index_y);

    public:
        void load_voxels(float _world_center_x, float _world_center_y);
        void save_voxels();

    public:
        void insert_voxel(Voxel_2D* _voxel);
        void remove_voxel(Voxel_2D* _voxel);
        void remove_voxel(int _index_x, int _index_y);

    private:
        void M_apply_id_to_voxel_recursive(Voxel_2D* _voxel, const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id);

    public:
        void apply_id_to_voxels(const Voxel_Intersection_Check_Func& _should_apply_to_whole, const Voxel_Intersection_Check_Func& _should_apply_partially, unsigned int _id);

    public:
        void update();

    };

}
