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
	enum class TileName
	{
		BlockNormal,
		BlockSpecial,
		BlockEnemy,
		Black,
		Border
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

	enum class ActionName
	{
		Action,
		EntryAction,
		ExitAction
	};

	struct Tag
	{
		std::string tag;
	};

	enum class EnemyType
	{
		SnoBee
	};
};
