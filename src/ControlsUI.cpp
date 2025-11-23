#include <ControlsUI.h>
// #include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>

void ControlsUI::Init(SDL_Window* Window, SDL_Renderer* Renderer){

}


void ControlsUI::Render(){
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Configuration");
    // ImGui::SliderFloat("Number of molecules",&ShapeCount, 100.f, 5000.f);
    ImGui::SliderInt("Number of molecules",&ShapeCount, 100, 5000);
    ImGui::SliderInt("Relative Temperature",&RelativeTemperature, 1, 1000);
    ImGui::Checkbox("Gravity     For demonstration purposes only, boltzmann distribution no longer accurate", &Gravity);
    if( ImGui::Button("Save and Reset") && Loop){
        Loop->Reset(ShapeCount, RelativeTemperature, Gravity);
    }
    if( ImGui::Button("Plot all") && Loop){
        Loop->Reset(ShapeCount, RelativeTemperature, Gravity);
        Loop->Clean();
    }
}
    