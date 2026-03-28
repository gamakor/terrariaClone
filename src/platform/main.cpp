#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <gameMain.h>


int main()
{
#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280,720, "Terriria Clone");
	SetExitKey(KEY_NULL);//disable Esc from closing window
	SetTargetFPS(144);

#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  //enables docking
	io.FontGlobalScale = 2; //control font size for ImGui
#pragma endregion imgui

	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();

#pragma region imgui
		rlImGuiBegin();

		//setting up docking and styling for it
		ImGui::PushStyleColor(ImGuiCol_WindowBg,{});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion imgui

	if (!updateGame())
	{
		CloseWindow();
	}

#pragma region imgui
		rlImGuiEnd();
#pragma endregion imgui
		EndDrawing();
	}
#pragma region imgui
	rlImGuiEnd();
#pragma endregion imgui
	CloseWindow();
	closeGame();
	return 0;
}