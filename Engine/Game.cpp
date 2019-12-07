/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat3.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float rotInc = 0.03;
	if (wnd.kbd.KeyIsPressed('A'))
	{
		rotX += rotInc;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		rotY += rotInc;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		rotZ += rotInc;
	}

}

void Game::ComposeFrame()
{
	auto triangles = cube.GetRtiangles();
	const Mat3 rot =
		Mat3::RotateX(rotX)*
		Mat3::RotateY(rotY)*
		Mat3::RotateZ(rotZ);
	for (auto& v : triangles.verticies)
	{
		v *= rot;
		v += {0.0f, 0.0f, 2.0f};
	}

	for (size_t i = 0, end = triangles.indicies.size() / 3; i < end; i++)
	{
		const Vec3& v0 = triangles.verticies[triangles.indicies[i * 3]];
		const Vec3& v1 = triangles.verticies[triangles.indicies[i * 3+1]];
		const Vec3& v2 = triangles.verticies[triangles.indicies[i * 3+2]];
		triangles.cullingFlags[i] = (v1 - v0).cross(v2 - v0)*v0 >= 0.0f;
	}

	for (auto& v : triangles.verticies)
	{
		sst.Transform(v);
	}
	std::vector<Color> colors{
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::LightGray,
		Colors::Magenta,
		Colors::Red,
		Colors::White,
		Colors::Yellow,
		Color::Color(50,50,0),
		Color::Color(150,150,0),
		Color::Color(100,100,0),
	};
	for (size_t i=0,end = triangles.indicies.size()/3;i<end;i++)
	{
		if (!triangles.cullingFlags[i])
		{
			gfx.DrawTriangle(triangles.verticies[triangles.indicies[i*3]], 
				triangles.verticies[triangles.indicies[i*3+1]], 
				triangles.verticies[triangles.indicies[i*3+2]], 
				colors[i]);
		}
	}
}