//DISCLAIMER
//THIS CODE IS NOT MY CODE
//THIS CODE IS FROM PROGRAMMING 2 LESSONS

#include "MiniginPCH.h"
#include "Structs.h"


//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f()
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f(float x, float y)
	: x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}
