#pragma once

#include <Voxel/Voxel_2D/Voxel_2D.h>


namespace LGL
{

    class Voxel_2D_Serializer
    {
    private:
        std::string m_file_path_format;

    public:
        inline void set_file_path_format(const std::string& _value) { m_file_path_format = _value; }
        inline const std::string& file_path_format() const { return m_file_path_format; }

    private:
        std::string M_parse_word(const std::string& _str, unsigned int _offset) const;

        std::string M_serialize_voxel(const Voxel_2D* _voxel) const;
        Voxel_2D* M_deserialize_voxel(const std::string& _serialized_data, unsigned int& _offset) const;
        void M_fill_voxel_with_data(Voxel_2D* _voxel) const;

    public:
        void save_voxel(const Voxel_2D* _voxel, int _index_x, int _index_y) const;
        Voxel_2D* load_voxel(int _index_x, int _index_y, float _expected_size_x, float _expected_size_y, unsigned int _expected_max_depth) const;

    };

}
