#pragma once
#include "CharacterComponent.h"

/////////////////////////////////////////////////
// Based on Observer from Programming 4 lessons//
/////////////////////////////////////////////////

namespace dae
{
	class Observer
	{
	public:
		enum class Event
		{
			ScoreNormal1,
			ScoreNormal2,
			ScoreNormal3,
			ScoreNormal4,
			ScoreRock1,
			ScoreRock2,
			ScoreRock3,
			ScoreRock4
		};
		virtual ~Observer() {}
		virtual void onNotify(const int playerIndex, Event event) = 0;
	};
}

