#pragma once
#include"Vec3.h"	

class TexVertex
{
public:
	TexVertex(const Vec3& pos, const Vec2& tc)
		:
		pos(pos),
		tc(tc)
	{}
	TexVertex InterpolateTo(const TexVertex& dest, float alpha)const 
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			tc.InterpolateTo(dest.tc, alpha)
		};
	}

public:
	Vec3 pos;
	Vec2 tc;
};