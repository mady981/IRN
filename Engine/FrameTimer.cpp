#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Duration()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTimer = last - old;
	return frameTimer.count();
}
