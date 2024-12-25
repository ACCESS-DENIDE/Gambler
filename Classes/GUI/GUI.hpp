#ifndef GUI_CLASS
#define GUI_CLASS

#define START_CHIP_AMOUNT 10000
#define MIN_BET 10
#define MAX_BET 100

#include "../GUIunit/GUIunit.hpp"



#include "../StateMachine/StateMachine.hpp"
#include "../../States/Idle/StateIdle.hpp"
#include "../../States/SpeedUp/StateSpeedUp.hpp"
#include "../../States/Working/StateWorking.hpp"
#include "../../States/SlowDown/StateSlowDown.hpp"
#include "../../States/Result/StateResult.hpp"

#define AUTOSTOP_SEC 10;

#define DEFAULT_SHOW_DEMO false
#define DEFAULT_BCGND_COLOR ImVec4(0.45f, 0.55f, 0.60f, 1.00f)

namespace ACD{

    class GUI{
        private:
            GLFWwindow *window;
            bool show_demo_window;
            ImVec4 clear_color;

            float auto_stop_timer;

            Drum drum_list[DRUMS_AMOUNT];

            StateMachine* cur_state;

            StateIdle internal_idle;
            StateSpeedUp internal_speedup;
            StateWorking internal_working;
            StateSlowDown internal_slow;
            StateResult internal_result;

            bool is_show_results;
            int result_val;

            int CreateFrame(ImGuiIO io);
            int Render();

            bool TryStateSwitch(int new_state);

            long long int chips_amount;
            int last_bet;
            int last_win;
            int cur_bet;

            bool is_buffering_input;

        public:
            GUI();
            GUI(int w, int h, const char *w_name);
            int Launch();
            ~GUI();


    };

    static void glfw_error_callback(int error, const char* description);
}
#endif