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

	float lightColorImGui[3] = { 1.0f, 1.0f, 1.0f };

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

				Color lightColorRaylib = {
				(unsigned char)(lightColorImGui[0] * 255),
				(unsigned char)(lightColorImGui[1] * 255),
				(unsigned char)(lightColorImGui[2] * 255),
				255
				};

				float r = (bushColors[i].r / 255.0f) * (lightColorRaylib.r / 255.0f);
				float g = (bushColors[i].g / 255.0f) * (lightColorRaylib.g / 255.0f);
				float b = (bushColors[i].b / 255.0f) * (lightColorRaylib.b / 255.0f);
				pixels[i].r = (unsigned char)(r * factor * 255);
				pixels[i].g = (unsigned char)(g * factor * 255);
				pixels[i].b = (unsigned char)(b * factor * 255);
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
		ImGui::ColorEdit3("Color", lightColorImGui);
		ImGui::End();
#endif

		rlImGuiEnd();

		EndDrawing();
	}
	rlImGuiShutdown();
	CloseWindow();
}