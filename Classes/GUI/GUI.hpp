#ifndef GUI_CLASS
#define GUI_CLASS


#include "../GUIunit/GUIunit.hpp"

#include "../../GUIunits/InfoScreen/InfoScreen.hpp"


#include "../StateMachine/StateMachine.hpp"
#include "../../States/Idle/StateIdle.hpp"
#include "../../States/SpeedUp/StateSpeedUp.hpp"
#include "../../States/Working/StateWorking.hpp"
#include "../../States/SlowDown/StateSlowDown.hpp"
#include "../../States/Result/StateResult.hpp"

//used for store personal best in file
#include <fstream>

//Time (in seconds) to automaticly switch from working mode to slow down
#define AUTOSTOP_SEC 10;

//Amount of chips on game start
#define START_CHIP_AMOUNT 100

//Minimal amount chips in bet
#define MIN_BET 10
//Maximum amount chips in bet
#define MAX_BET 100

//Enable/Disable ImGui demo window
#define DEFAULT_SHOW_DEMO false
//Default background color
#define DEFAULT_BCGND_COLOR ImVec4(0.45f, 0.55f, 0.60f, 1.00f)

namespace ACD{


    /// @brief Class For Managing main UI window processing
    class GUI{
        private:
            /// @brief Main window pointer
            GLFWwindow *window;
            /// @brief Demo window switch
            bool show_demo_window;
            /// @brief Background color
            ImVec4 clear_color;

            /// @brief Autostop timer holdeer
            float auto_stop_timer;

            /// @brief All in game drums array
            Drum drum_list[DRUMS_AMOUNT];
            /// @brief Quick info subwindow
            InfoScreen q_info;

            /// @brief GUI StateMachine
            StateMachine* cur_state;

            /// @brief Preloaded States
            StateIdle internal_idle;
            StateSpeedUp internal_speedup;
            StateWorking internal_working;
            StateSlowDown internal_slow;
            StateResult internal_result;

            /// @brief Result subwindow switch
            bool is_show_results;
            /// @brief Precalculated result value
            int result_val;
            
            /// @brief Player's chips amount
            int chips_amount;
            /// @brief Stored PB
            int personal_best;
            /// @brief Memorised last bet
            int last_bet;
            /// @brief Last win in chips
            int last_win;
            /// @brief Stored current bet(for safety reasons)
            int cur_bet;

            /// @brief Swith for autostop after speedup
            bool is_buffering_input;


            int CreateFrame(ImGuiIO io);
            int Render();

            bool TryStateSwitch(int new_state);

            void LoadPB();
            void StorePB();

            void Init(int w, int h, const char *name);


        public:
            GUI();
            GUI(int w, int h, const char *w_name);
            int Launch();
            ~GUI();


    };

    static void glfw_error_callback(int error, const char* description);
}
#endif