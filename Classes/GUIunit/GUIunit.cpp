#include "GUIunit.hpp"

ACD::GUIunit::GUIunit()
{

}


void ACD::GUIunit::Process()
{
    
    ImDrawList* canvas= ImGui::GetWindowDrawList();
    canvas->AddTriangleFilled(ImVec2(100, 100), ImVec2(100, 200), ImVec2(150, 100), ImColor(0, 255, 0));
}


ACD::GUIunit::~GUIunit()
{

}

ImVec2 ACD::operator+(const ImVec2 a, const ImVec2 b)
{
    return ImVec2(a.x+b.x, a.y+b.y);
}
