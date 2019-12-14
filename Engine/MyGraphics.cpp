#include"Graphics.h"

void Graphics::DrawTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, Color c)
{
	const Vec2* pv0 = &v0;
	const Vec2* pv1 = &v1;
	const Vec2* pv2 = &v2;

	if (pv0->y > pv1->y) std::swap(pv0, pv1);
	if (pv1->y > pv2->y) std::swap(pv1, pv2);
	if (pv0->y > pv1->y) std::swap(pv0, pv1);

	if (pv0->y == pv1->y)
	{
		if (pv0->x > pv1->x) std::swap(pv0, pv1);
		DrawFlatTopTriangle(*pv0, *pv1, *pv2, c);
	}
	else if (pv1->y == pv2->y)
	{
		if (pv1->x > pv2->x) std::swap(pv1, pv2);
		DrawFlatBottomTriangle(*pv0, *pv1, *pv2, c);
	}
	else
	{
		const float alpha = (pv1->y - pv0->y) / (pv2->y - pv0->y);
		const Vec2 vi = *pv0 + (*pv2 - *pv0) * alpha;

		if (pv1->x < vi.x)
		{
			DrawFlatBottomTriangle(*pv0, *pv1, vi, c);
			DrawFlatTopTriangle(*pv1, vi, *pv2, c);
		}
		else
		{
			DrawFlatBottomTriangle(*pv0, vi, *pv1, c);
			DrawFlatTopTriangle(vi, *pv1, *pv2, c);
		}
	}
}

void Graphics::DrawTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const Surface& surface)
{
	const TexVertex* pv0 = &v0;
	const TexVertex* pv1 = &v1;
	const TexVertex* pv2 = &v2;

	if (pv0->pos.y > pv1->pos.y) std::swap(pv0, pv1);
	if (pv1->pos.y > pv2->pos.y) std::swap(pv1, pv2);
	if (pv0->pos.y > pv1->pos.y) std::swap(pv0, pv1);

	if (pv0->pos.y == pv1->pos.y)
	{
		if (pv0->pos.x > pv1->pos.x) std::swap(pv0, pv1);
		DrawFlatTopTriangleTex(*pv0, *pv1, *pv2, surface);
	}
	else if (pv1->pos.y == pv2->pos.y)
	{
		if (pv1->pos.x > pv2->pos.x) std::swap(pv1, pv2);
		DrawFlatBottomTriangleTex(*pv0, *pv1, *pv2, surface);
	}
	else
	{
		const float alpha = (pv1->pos.y - pv0->pos.y) / (pv2->pos.y - pv0->pos.y);
		const TexVertex vi = pv0->InterpolateTo(*pv2, alpha);

		if (pv1->pos.x < vi.pos.x)
		{
			DrawFlatBottomTriangleTex(*pv0, *pv1, vi, surface);
			DrawFlatTopTriangleTex(*pv1, vi, *pv2, surface);
		}
		else
		{
			DrawFlatBottomTriangleTex(*pv0, vi, *pv1, surface);
			DrawFlatTopTriangleTex(vi, *pv1, *pv2, surface);
		}
	}
}



void Graphics::DrawLine(float x1, float y1, float x2, float y2, Color c)
{
	const float dx = x2 - x1;
	const float dy = y2 - y1;

	if (dy == 0.0f && dx == 0.0f)
	{
		PutPixel(int(x1), int(y1), c);
	}
	else if (abs(dy) > abs(dx))
	{
		if (dy < 0.0f)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dx / dy;
		float y = y1;
		int lastIntY;
		for (float x = x1; y < y2; y += 1.0f, x += m)
		{
			lastIntY = int(y);
			PutPixel(int(x), lastIntY, c);
		}
		if (int(y2) > lastIntY)
		{
			PutPixel(int(x2), int(y2), c);
		}
	}
	else
	{
		if (dx < 0.0f)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dy / dx;
		float x = x1;
		int lastIntX;
		for (float y = y1; x < x2; x += 1.0f, y += m)
		{
			lastIntX = int(x);
			PutPixel(lastIntX, int(y), c);
		}
		if (int(x2) > lastIntX)
		{
			PutPixel(int(x2), int(y2), c);
		}
	}
}

void Graphics::DrawFlatBottomTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, Color c)
{
	const float m0 = (v0.x - v1.x) / (v0.y - v1.y);
	const float m1 = (v0.x - v2.x) / (v0.y - v2.y);

	const int startY = (int)ceil(v0.y - 0.5);
	const int endY = (int)ceil(v1.y - 0.5);

	for (int y = startY; y < endY; y++)
	{
		const float px0 = m0 * (float(y) + 0.5 - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5 - v0.y) + v0.x;

		const int startX = (int)ceil(px0 - 0.5);
		const int endX = (int)ceil(px1 - 0.5);

		for (int x = startX; x < endX; x++)
		{
			PutPixel(x, y, c);
		}
	}
}

void Graphics::DrawFlatTopTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, Color c)
{
	const float m0 = (v2.x - v0.x) / (v2.y - v0.y);
	const float m1 = (v2.x - v1.x) / (v2.y - v1.y);

	const int startY = (int)ceil(v0.y - 0.5);
	const int endY = (int)ceil(v2.y - 0.5);

	for (int y = startY; y < endY; y++)
	{
		const float px0 = m0 * (float(y) + 0.5 - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5 - v1.y) + v1.x;

		const int startX = (int)ceil(px0 - 0.5);
		const int endX = (int)ceil(px1 - 0.5);

		for (int x = startX; x < endX; x++)
		{
			PutPixel(x, y, c);
		}
	}
}

void Graphics::DrawFlatBottomTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const Surface& surface)
{
	const float m0 = (v0.pos.x - v1.pos.x) / (v0.pos.y - v1.pos.y);
	const float m1 = (v0.pos.x - v2.pos.x) / (v0.pos.y - v2.pos.y);

	const int startY = (int)ceil(v0.pos.y - 0.5);
	const int endY = (int)ceil(v1.pos.y - 0.5);


}

void Graphics::DrawFlatTopTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const Surface& surface)
{
	const float m0 = (v2.pos.x - v0.pos.x) / (v2.pos.y - v0.pos.y);
	const float m1 = (v2.pos.x - v1.pos.x) / (v2.pos.y - v1.pos.y);

	const int startY = (int)ceil(v0.pos.y - 0.5);
	const int endY = (int)ceil(v2.pos.y - 0.5);

	Vec2 tcEdgeL = v0.tc;
	Vec2 tcEdgeR = v1.tc;
	const Vec2 tcBottom = v2.tc;



}
