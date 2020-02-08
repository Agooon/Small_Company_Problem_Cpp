#include "pch.h"
#include "CTimer.h"
#pragma warning(disable:4244)


CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

void CTimer::vsetD_secs(LARGE_INTEGER end, LARGE_INTEGER start, LARGE_INTEGER freq)
{
	d_secs = end.QuadPart - start.QuadPart;
	d_secs = d_secs / freq.QuadPart;
}


