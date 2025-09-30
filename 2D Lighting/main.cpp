#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

int main()
{
	const int w = 800;
	const int h = 450;

	float sliderDemo = 0.5f;
	bool checkboxDemo = true;

	InitWindow(w, h, "Raylib+ImGui");

	Texture2D bush = LoadTexture("SimpleBush.png");
	Texture2D lightIcon = LoadTexture("LightIcon.png");

	Image img = LoadImageFromTexture(bush);

	Color* bushColors = LoadImageColors(img);

	float lightPosX = 350;
	float lightPosY = h / 2;
	float lightIconScale = 0.1f;

	float lightRadius = 100.0f;

	rlImGuiSetup(true);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		Color* pixels = LoadImageColors(img);

		int pixelCount = img.width * img.height;
		for (int i = 0; i < pixelCount; i++)
		{
			if (pixels[i].a > 0)
			{
				float distance = Vector2Distance({ w / 2, h / 2 }, { lightPosX, lightPosY });
				float factor = 1.0f - (distance / lightRadius);
				if (factor < 0) 
					factor = 0;

				pixels[i].r = (unsigned char)(bushColors[i].r * factor);
				pixels[i].g = (unsigned char)(bushColors[i].g * factor);
				pixels[i].b = (unsigned char)(bushColors[i].b * factor);
			}
		}

		UpdateTexture(bush, pixels);

		UnloadImageColors(pixels);

		DrawTexture(bush, w / 2, h / 2, WHITE);

		DrawTexture(bush, w / 2, h / 2, WHITE);
		DrawTextureEx(lightIcon, { lightPosX - (lightIcon.width * lightIconScale / 2) , lightPosY - (lightIcon.height * lightIconScale / 2)}, 0.0f, lightIconScale, WHITE);

		rlImGuiBegin();

#ifdef _DEBUG

		DrawCircleLines(lightPosX, lightPosY, lightRadius, RED);

		ImGui::Begin("light", NULL);
		ImGui::SliderFloat("X", &lightPosX, 0.0f, (float)w);
		ImGui::SliderFloat("Y", &lightPosY, 0.0f, (float)h);
		ImGui::SliderFloat("Radius", &lightRadius, 10.0f, 300.0f);
		ImGui::End();
#endif

		rlImGuiEnd();

		EndDrawing();
	}
	rlImGuiShutdown();
	CloseWindow();
}