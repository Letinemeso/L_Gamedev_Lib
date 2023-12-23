#pragma once


namespace LGL
{

    enum class BT_Execution_Result
    {
        Success,
        Fail,
        In_Progress
    };

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
