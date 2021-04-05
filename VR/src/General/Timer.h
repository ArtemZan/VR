#pragma once
#include "pch.h"

namespace VR
{
	class Timer
	{
	public:
		Timer();

		//Returns time(in milliseconds) since last Update() or 
		//since creation of timer if Update() hasn't been called yet
		double Update();
	private:
		std::chrono::high_resolution_clock::time_point m_lastUpdate;
	};
}
