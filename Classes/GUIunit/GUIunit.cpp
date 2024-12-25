#include "GUIunit.hpp"

/// @brief Default(empty) GUI unit constructor
ACD::GUIunit::GUIunit()
{

}


/// @brief Function to generate new frame of GUI Unit
void ACD::GUIunit::Process()
{
    //Default frame process 
    ImDrawList* canvas= ImGui::GetWindowDrawList();
    canvas->AddTriangleFilled(ImVec2(100, 100), ImVec2(100, 200), ImVec2(150, 100), ImColor(0, 255, 0));
}


/// @brief Default (empty) GUI unit deconstructor
ACD::GUIunit::~GUIunit()
{

}


/// @brief Basic vector math (add)
/// @param a left operand
/// @param b right operand
/// @return answer a+b
ImVec2 ACD::operator+(const ImVec2 a, const ImVec2 b)
{
    return ImVec2(a.x+b.x, a.y+b.y);
}


/// @brief Basic vector math (subtract)
/// @param a left operand
/// @param b right operand
/// @return answer a-b
ImVec2 ACD::operator-(const ImVec2 a, const ImVec2 b)
{
    return ImVec2(a.x-b.x, a.y-b.y);
}
