#pragma once
#include<vector>
#include"Vec3.h"
#include"IndexedLineList.h"
class Cube
{
public:
	Cube(float size)
	{
		const float side = size / 2.0f;
		verticies.emplace_back(-side, -side, -side);
		verticies.emplace_back(-side, -side, side);
		verticies.emplace_back(side, -side, side);
		verticies.emplace_back(side, -side, -side);
		verticies.emplace_back(-side, side, -side);
		verticies.emplace_back(side, side, -side);
		verticies.emplace_back(side, side, side);
		verticies.emplace_back(-side, side, side);
	}

	IndexedLineList GetLines()const
	{
		return{
			verticies,{
				0,1, 0,3, 2,1, 2,3,
				4,5, 4,7, 6,5, 6,7,
				0,4, 2,6, 1,7, 3,5
			}
		};
	}

private:
	std::vector<Vec3> verticies;
};