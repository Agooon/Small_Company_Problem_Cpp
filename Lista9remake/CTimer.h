#pragma once
#include <Windows.h>
class CTimer
{
public:
	CTimer();
	~CTimer();



	void queryPerfStart() { QueryPerformanceCounter(&li_start); }
	void queryPerfEnd()   { QueryPerformanceCounter(&li_end); }
	void queryPerfFreq()  { QueryPerformanceFrequency(&li_freq); }

	LARGE_INTEGER getliStart() { return li_start; }
	LARGE_INTEGER getliEnd()   { return li_end; }
	LARGE_INTEGER getliFreq()  { return li_freq; }


	double dgetD_secs() { return d_secs; }
	void vsetD_secs(double secs) { d_secs = secs; }
	void vsetD_secs(LARGE_INTEGER end, LARGE_INTEGER start, LARGE_INTEGER freq);
private:
	double d_secs;
	LARGE_INTEGER li_start, li_end, li_freq;
};

