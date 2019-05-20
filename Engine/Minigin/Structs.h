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
	class TextureComponent;
	enum class State
	{
		Walking,
		Idle,
		Pumping,
		Digging

	};

	enum class TileName
	{
		Sky,
		Ground1,
		Ground2,
		Ground3,
		Ground4,
		Black
	};

	struct Tile
	{
		TextureComponent* Texture;
		Point2f Position;
		TileName tileName;
	};

	enum class Direction
	{
		right,
		down,
		left,
		up,
		none
	};
}
