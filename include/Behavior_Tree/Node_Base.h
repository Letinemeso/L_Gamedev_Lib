#pragma once


namespace LGL
{

    enum class BT_Execution_Result
    {
        Success,
        Fail,
        In_Progress
    };

    inline LGL::BT_Execution_Result bool_to_bt_result(bool _value)
    {
        return _value ? BT_Execution_Result::Success : BT_Execution_Result::Fail;
    }

    template <typename... Args>
    class Node_Base
    {
    public:
        Node_Base() { }
        virtual ~Node_Base() { }

    public:
        virtual BT_Execution_Result process(Args... _args) const = 0;

    };

}
