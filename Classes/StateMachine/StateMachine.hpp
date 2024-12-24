
namespace ACD
{
    class StateMachine
    {
    private:
        int next_state_id;
        int my_state_id;
    public:
        StateMachine();
        bool IsValidStateSwitch(int new_state_id);
        void Frame();
        ~StateMachine();
    };
       
}