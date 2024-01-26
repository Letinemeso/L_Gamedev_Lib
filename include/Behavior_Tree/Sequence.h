#pragma once

#include <Data_Structures/List.h>

#include <Behavior_Tree/Node_Base.h>


namespace LGL
{

    template <typename... Args>
    class Sequence : public Node_Base<Args...>
    {
    public:
        using Node_Base_Type = Node_Base<Args...>;
        using Node_Base_List_Type = LDS::List<Node_Base_Type*>;

    private:
        Node_Base_List_Type m_childs;

    public:
        Sequence();
        ~Sequence();

    public:
        void add_child(Node_Base_Type* _node);   //  this class becomes _node's owner
        void remove_child(Node_Base_Type* _node);    //  deletes specified child
        void remove_childs();

    public:
        inline const Node_Base_List_Type& childs() const { return m_childs; }

    public:
        BT_Execution_Result process(Args... _args) const override;

    };





    template <typename... Args>
    Sequence<Args...>::Sequence()
    {

    }

    template <typename... Args>
    Sequence<Args...>::~Sequence()
    {
        remove_childs();
    }



    template <typename... Args>
    void Sequence<Args...>::add_child(Node_Base_Type *_node)
    {
        m_childs.push_back(_node);
    }

    template <typename... Args>
    void Sequence<Args...>::remove_child(Node_Base_Type *_node)
    {
        typename Node_Base_List_Type::Iterator it = m_childs.begin();
        for(; !it.end_reached(); ++it)
        {
            if(*it != _node)
                continue;

            delete _node;
            m_childs.erase(it);
            break;
        }
        L_ASSERT(!it.end_reached());
    }

    template <typename... Args>
    void Sequence<Args...>::remove_childs()
    {
        for(typename Node_Base_List_Type::Iterator it = m_childs.begin(); !it.end_reached(); ++it)
            delete *it;

        m_childs.clear();
    }



    template <typename... Args>
    BT_Execution_Result Sequence<Args...>::process(Args... _args) const
    {
        L_ASSERT(m_childs.size() > 0);
        BT_Execution_Result result = BT_Execution_Result::Success;
        for(typename Node_Base_List_Type::Const_Iterator it = m_childs.begin(); !it.end_reached(); ++it)
        {
            result = (*it)->process(_args...);

            if(result == BT_Execution_Result::Success)
                continue;

            return result;
        }

        return result;
    }

}
