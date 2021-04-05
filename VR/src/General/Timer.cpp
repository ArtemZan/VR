#include "pch.h"
#include "Timer.h"

VR::Timer::Timer()
{
	m_lastUpdate = std::chrono::high_resolution_clock::now();
}

double VR::Timer::Update()
{
	double time = round((std::chrono::high_resolution_clock::now() - m_lastUpdate).count() * 1e-3) * 1e-3;
	m_lastUpdate = std::chrono::high_resolution_clock::now();
	return time;
}
