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
	auto triangled = cube.GetRtiangles();
	const Mat3 rot =
		Mat3::RotateX(rotX)*
		Mat3::RotateY(rotY)*
		Mat3::RotateZ(rotZ);
	for (auto& v : triangled.verticies)
	{
		v *= rot;
		v += {0.0f, 0.0f, 2.0f};
		sst.Transform(v);
	}

	for (auto i = triangled.indicies.cbegin(), end = triangled.indicies.cend(); i != end; std::advance(i, 3))
	{
		gfx.DrawTriangle(triangled.verticies[*i], triangled.verticies[*std::next(i)], triangled.verticies[*std::next(i,2)], Colors::White);
	}
}