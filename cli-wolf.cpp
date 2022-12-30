// cli-wolf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>

using namespace std;

int screen_w = 120;
int screen_h = 32;

float player_x = 8.0f;
float player_y = 8.0f;
float player_ang = 0.0f;
float player_fov = M_PI_4;

int map_h = 16;
int map_w = 16;

float fov_depth = 16.0f;

int main()
{
	wchar_t* screen = new wchar_t[screen_w * screen_h];
	HANDLE h_console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(h_console);
	DWORD dBytesWritten = 0;
	
	wstring map;

	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	while (1)
	{
		for (int i = 0; i < screen_w; i++)
		{
			float ray_a = (player_ang - player_fov / 2.0f) + ((float)i / (float)screen_w) * player_fov;
			float distance_wall = 0;
			
			bool hit_wall = false;

			float eye_x = sinf(ray_a);
			float eye_y = cosf(ray_a);

			while (!hit_wall)
			{
				distance_wall += 0.1f;

				int nTestX = (int)(player_x + eye_x + distance_wall);
				int nTestY = (int)(player_y + eye_y + distance_wall);

				if (nTestX < 0 || nTestX >= map_w || nTestY < 0 || nTestY >= map_h)
				{
					hit_wall = true;
					distance_wall = fov_depth;
				}
				else if (map[nTestY * map_w + nTestX] == '#')
				{
						hit_wall = true;
				}	
			}
			int nCeiling = (float)(screen_h / 2.0) - screen_h / ((float)distance_wall);
			int nfloor = screen_h - nCeiling;

			for (int j = 0; j < screen_h; j++)
			{
				if (j < nCeiling)
				{
					screen[j * screen_h + i] = ' ';
				}
				else if(j > nCeiling && j <= nfloor) 
				{
					screen[j * screen_h + i] = '#';
				}
				else
				{
					screen[j * screen_h + i] = ' ';
				}
			}
		}

		screen[screen_w * screen_h - 1] = '\0';
		WriteConsoleOutputCharacter(h_console, screen, screen_w * screen_h, { 0,0 }, &dBytesWritten);
	}

	return 0;
}
