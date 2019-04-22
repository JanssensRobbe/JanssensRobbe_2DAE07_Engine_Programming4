//DISCLAIMER
//THIS CODE IS NOT MY CODE
//THIS CODE IS FROM PROGRAMMING 2 LESSONS

#pragma once

struct Point2f
{
	Point2f();
	Point2f(float x, float y);

	float x;
	float y;
};


struct Rectf
{
	Rectf();
	Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

};

namespace dae
{
	enum class State
	{
		Walking,
		Idle,
		Pumping,
		Digging

	};
}
