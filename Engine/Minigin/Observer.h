#pragma once
#include "CharacterComponent.h"

/////////////////////////////////////////////////
// Based on Observer from Programming 4 lessons//
/////////////////////////////////////////////////

namespace dae
{
	class Observer
	{
		enum class Event {

		};
	public:
		virtual ~Observer() {}
		virtual void onNotify(const int playerIndex, Event event) = 0;
	};
}

