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
    ImGui::Begin("Test");
    ImGui::Text("Hello World!");
}
    