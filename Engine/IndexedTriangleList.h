#pragma once

#include<vector>
#include"Vec3.h"

template<typename T>
struct IndexedTriangleList
{
	IndexedTriangleList(std::vector<T>ver, std::vector<size_t> ind)
		:
		verticies(std::move(ver)),
		indicies(std::move(ind))
	{
		assert(verticies.size() > 2);
		assert(indicies.size() % 3 == 0);
		cullingFlags.resize(indicies.size() / 3, false);
	}

	std::vector<T> verticies;
	std::vector<size_t> indicies;
	std::vector<bool> cullingFlags;
};