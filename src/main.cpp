#include <iostream>
#include <raylib.h>

bool isRunning = true;

int main()
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280,720, "Terriria Clone");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("First Window Complete",(1280/2),(720/2),36,BLACK);

		DrawRectangle(50,50,100,100,{255,0,0,127});
		DrawRectangle(75,75,100,100,{0,255,0,127});



		EndDrawing();
	}

	CloseWindow();
	return 0;
}