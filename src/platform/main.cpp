#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>


int main()
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280,720, "Terriria Clone");

#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  //enables docking
	io.FontGlobalScale = 2; //control font size for ImGui
#pragma endregion imgui

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
#pragma region imgui
		rlImGuiBegin();

		//setting up docking and styling for it
		ImGui::PushStyleColor(ImGuiCol_WindowBg,{});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion imgui
		DrawText("First Window Complete",(1280/2),(720/2),36,BLACK);
#pragma region imgui windows
		ImGui::Begin("test");

		ImGui::Text("Hello World");

		if (ImGui::Button("button"))
		{
			std::cout << "Imgui button pressed \n";
		}
		ImGui::SameLine();
		if (ImGui::Button("button2"))
		{
			std::cout << "Imgui button pressed 2  \n";
		}
		static bool booleanCheck = false;
		ImGui::Checkbox("True or False", &booleanCheck);

		static int e = 0;
		if (ImGui::RadioButton("Option A", e==0))
		{
			e = 0;
		}
		if (ImGui::RadioButton("Option B", e==1))
		{
			e = 1;
		}
		if (ImGui::RadioButton("Option C", e==2))
		{
			e = 2;
		}
		static int g = 0;
		ImGui::InputInt("int", &g);

		static float f = 0;
		ImGui::DragFloat3("Dragf3", &f, 0.01f);

		ImGui::Text("Speed");
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Control over how faster the character goes");
			ImGui::EndTooltip();
		}

		static char buffer[128] = "";

		ImGuiInputTextFlags flags =
			ImGuiInputTextFlags_CharsNoBlank|
			ImGuiInputTextFlags_EnterReturnsTrue |
			ImGuiInputTextFlags_AutoSelectAll;
		if (ImGui::InputText("Player Name",buffer,sizeof(buffer),flags))
		{
			std::cout << "Player Name: " << buffer << std::endl;
		}



		ImGui::End();

		ImGui::Begin("test2");
		ImGui::Text("hello");
		ImGui::Separator();
		ImGui::NewLine();
		static float a = 0;
		ImGui::SliderFloat("slider", &a, 0, 1);

		ImGui::End();
#pragma endregion imgui windows
#pragma region imgui
		rlImGuiEnd();
#pragma endregion imgui
		EndDrawing();
	}
#pragma region imgui
	rlImGuiEnd();
#pragma endregion imgui
	CloseWindow();
	return 0;
}