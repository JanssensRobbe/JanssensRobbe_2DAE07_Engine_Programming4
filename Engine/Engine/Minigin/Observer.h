#pragma once
#include "CharacterComponent.h"
/////////////////////////////////////////////////
// Based on Observer from Programming 4 lessons//
/////////////////////////////////////////////////

namespace dae
{
	class Subject;
	class Observer
	{
	public:
		Observer(Subject *mod);
		~Observer() = default;
		virtual void Notify() = 0;

		Subject* GetSubject()
		{
			return m_pSubject;
		}

	private:
		Subject* m_pSubject;
	};
}

