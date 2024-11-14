#include <Voxel/Voxel_2D/Voxel_2D_Serializer.h>

#include <Stuff/File.h>

using namespace LGL;


std::string Voxel_2D_Serializer::M_parse_word(const std::string& _str, unsigned int _offset) const
{
    for(; _offset < _str.size(); ++_offset)
    {
        if(_str[_offset] != ' ')
            break;
    }

    if(_offset >= _str.size())
        return "";

    unsigned int word_size = 1;
    for(; _offset + word_size < _str.size(); ++word_size)
    {
        if(_str[_offset + word_size] == ' ')
            break;
    }

    return _str.substr(_offset, word_size);
}


std::string Voxel_2D_Serializer::M_serialize_voxel(const Voxel_2D* _voxel) const
{
    std::string result = std::to_string(_voxel->id()) + ' ';
    if(_voxel->is_split())
        result += "S ";
    else
        result += "M ";

    if(!_voxel->is_split())
        return result;

    for(unsigned int i=0; i<4; ++i)
        result += M_serialize_voxel(_voxel->child(i));

    return result;
}

Voxel_2D* Voxel_2D_Serializer::M_deserialize_voxel(const std::string& _serialized_data, unsigned int& _offset) const
{
    std::string id_str = M_parse_word(_serialized_data, _offset);
    L_ASSERT(id_str.size() > 0);
    _offset += id_str.size() + 1;
    std::string split_info = M_parse_word(_serialized_data, _offset);
    L_ASSERT(split_info == "S" || split_info == "M");
    _offset += 2;

    unsigned int id = std::stoi(id_str);
    bool is_split = (split_info == "S");

    Voxel_2D* result = new Voxel_2D;

    result->m_id = id;

    if(!is_split)
        return result;

    for(unsigned int i=0; i<4; ++i)
    {
        result->m_childs[i] = M_deserialize_voxel(_serialized_data, _offset);
        result->m_childs[i]->m_parent = result;
    }

    return result;
}

void Voxel_2D_Serializer::M_fill_voxel_with_data(Voxel_2D* _voxel) const
{
    if(!_voxel->is_split())
        return;

    auto fill_voxel_data = [](Voxel_2D* _voxel, float _position_x, float _position_y, float _size_x, float _size_y)
    {
        _voxel->m_size_x = _size_x;
        _voxel->m_size_y = _size_y;
        _voxel->m_position_x = _position_x;
        _voxel->m_position_y = _position_y;
        _voxel->m_max_depth = _voxel->m_parent->m_max_depth;
        _voxel->m_depth = _voxel->m_parent->m_depth + 1;
    };

    float size_x_halved = _voxel->m_size_x * 0.5f;
    float size_y_halved = _voxel->m_size_y * 0.5f;

    fill_voxel_data(_voxel->m_childs[0], _voxel->m_position_x, _voxel->m_position_y, size_x_halved, size_y_halved);
    fill_voxel_data(_voxel->m_childs[1], _voxel->m_position_x + size_x_halved, _voxel->m_position_y, size_x_halved, size_y_halved);
    fill_voxel_data(_voxel->m_childs[2], _voxel->m_position_x, _voxel->m_position_y + size_y_halved, size_x_halved, size_y_halved);
    fill_voxel_data(_voxel->m_childs[3], _voxel->m_position_x + size_x_halved, _voxel->m_position_y + size_y_halved, size_x_halved, size_y_halved);

    for(unsigned int i=0; i<4; ++i)
        M_fill_voxel_with_data(_voxel->m_childs[i]);
}



void Voxel_2D_Serializer::save_voxel(const Voxel_2D* _voxel, int _index_x, int _index_y) const
{
    std::string file_path = m_file_path_format + '_' + std::to_string(_index_x) + '_' + std::to_string(_index_y) + ".vch";
    LST::File file(file_path);

    std::string serialized_data = M_serialize_voxel(_voxel);

    file.clear();
    file.append_block(serialized_data);
}

Voxel_2D* Voxel_2D_Serializer::load_voxel(int _index_x, int _index_y, float _expected_size_x, float _expected_size_y, unsigned int _expected_max_depth) const
{
    std::string file_path = m_file_path_format + '_' + std::to_string(_index_x) + '_' + std::to_string(_index_y) + ".vch";
    LST::File file(file_path);

    if(!file.exists())
        return nullptr;

    std::string serialized_data = file.extract_block();

    unsigned int offset = 0;
    Voxel_2D* result = M_deserialize_voxel(serialized_data, offset);

    result->m_size_x = _expected_size_x;
    result->m_size_y = _expected_size_y;
    result->m_position_x = (float)_index_x * _expected_size_x;
    result->m_position_y = (float)_index_y * _expected_size_y;
    result->m_max_depth = _expected_max_depth;

    M_fill_voxel_with_data(result);

    return result;
}
