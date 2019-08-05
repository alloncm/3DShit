#pragma once
#include"Graphics.h"
#include"Vec3.h"

class ScreenSpaceTransformer
{
public:
	ScreenSpaceTransformer() 
		:
		_xFactor(float(Graphics::ScreenWidth/2)),
		_yFactor(float(Graphics::ScreenHeight / 2))
	{}

	Vec3& Transform(Vec3& v)
	{
		const float zin = 1.0f / v.z;
		v.x = (v.x*zin + 1.0f)*_xFactor;
		v.y = (-v.y*zin + 1.0f)*_yFactor;
		return v;
	}

	Vec3 GetTransformed(const Vec3& v)
	{
		return Transform(Vec3(v));
	}

private:
	float _xFactor;
	float _yFactor;
};