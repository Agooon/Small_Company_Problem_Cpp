#pragma once
#include <Windows.h>

// Class made to measure time of optimizers
// In my opinion a whole class wasn't nessesary, but
// the task required it.

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
	double d_secs = 0;
	LARGE_INTEGER li_start, li_end, li_freq;
};

