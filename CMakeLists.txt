cmake_minimum_required(VERSION 3.28)

set (CMAKE_CXX_STANDARD 11)

project(Gambler)


set(SOURCE
   "Source/main.cpp"
   
   "Libs/ImGUI/imgui/imgui_demo.cpp"
   "Libs/ImGUI/imgui/imgui_draw.cpp"
   "Libs/ImGUI/imgui/imgui_tables.cpp"
   "Libs/ImGUI/imgui/imgui_widgets.cpp"
   "Libs/ImGUI/imgui/imgui.cpp"
   
   "Libs/ImGUI/backend/imgui_impl_glfw.cpp"
   "Libs/ImGUI/backend/imgui_impl_opengl2.cpp"

   "Classes/GUI/GUI.cpp"
   "Classes/GUIunit/GUIunit.cpp"  

   "GUIunits/Drum/Drum.cpp"
    "GUIunits/InfoScreen/InfoScreen.cpp"

   "Libs/MiniLib/MiniLib.cpp"

    "Classes/StateMachine/StateMachine.cpp"

    "Libs/ImageLoader/ImageLoader.cpp"

    "States/Idle/StateIdle.cpp"
    "States/SpeedUp/StateSpeedUp.cpp"
    "States/Working/StateWorking.cpp"
    "States/SlowDown/StateSlowDown.cpp"
    "States/Result/StateResult.cpp"
)

set(HEADERS
    "Libs/ImGUI/imgui/imconfig.h"
    "Libs/ImGUI/imgui/imgui_internal.h"
    "Libs/ImGUI/imgui/imstb_rectpack.h"
    "Libs/ImGUI/imgui/imstb_textedit.h"
    "Libs/ImGUI/imgui/imstb_truetype.h"
    "Libs/ImGUI/imgui/imgui.h"

    "Libs/ImGUI/backend/imgui_impl_glfw.h"
    "Libs/ImGUI/backend/imgui_impl_opengl2.h"

    "Libs/STD_img/std_image.h"

    "Classes/GUI/GUI.hpp"
    "Classes/GUIunit/GUIunit.hpp"

    "GUIunits/Drum/Drum.hpp"
    "GUIunits/InfoScreen/InfoScreen.hpp"

    "Libs/MiniLib/MiniLib.hpp"

    "Classes/StateMachine/StateMachine.hpp"

    "Libs/ImageLoader/ImageLoader.hpp"

    "States/Idle/StateIdle.hpp"
    "States/SpeedUp/StateSpeedUp.hpp"
    "States/Working/StateWorking.hpp"
    "States/SlowDown/StateSlowDown.hpp"
    "States/Result/StateResult.hpp"
)



find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)
