#pragma once

#include <L_Debug/L_Debug.h>
#include <Stuff/Function_Wrapper.h>

#include <Behavior_Tree/Node_Base.h>


namespace LGL
{

    template <typename... Args>
    class Action : public Node_Base<Args...>
    {
    public:
        using Action_Func_Type = BT_Execution_Result(Args...);

    private:
        LST::Function<Action_Func_Type> m_action;

    public:
        Action(const LST::Function<Action_Func_Type>& _action);
        ~Action();

    public:
        void set_action(const LST::Function<Action_Func_Type>& _action);

    public:
        BT_Execution_Result process(Args... _args) const override;

    };





    template <typename... Args>
    Action<Args...>::Action(const LST::Function<Action_Func_Type>& _action)
        : m_action(_action)
    {
        L_ASSERT(_action);
    }

    template <typename... Args>
    Action<Args...>::~Action()
    {

    }



    template <typename... Args>
    void Action<Args...>::set_action(const LST::Function<Action_Func_Type>& _action)
    {
        L_ASSERT(_action);
        m_action = _action;
    }



    template <typename... Args>
    BT_Execution_Result Action<Args...>::process(Args... _args) const
    {
        return m_action((Args&&)_args...);
    }

}
