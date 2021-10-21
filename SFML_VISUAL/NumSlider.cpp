#include <iostream>

class NumSlider
{
public:
	NumSlider(float numS, float numE, float numTime)
	{
		float numDistance = abs(numE - numS);
		numStart = numS;
		numCurrent = numS;
		numEnd = numE;
		numRate = numDistance / numTime;
		going = true;
	}

	NumSlider(float numS, float numE, float numC, float numTime)
	{
		float numDistance = abs(numE - numS);
		numStart = numS;
		numCurrent = numC;
		numEnd = numE;
		numRate = numDistance / numTime;
		going = true;
	}

	float tick()
	{
		if (numCurrent <= numEnd && going) numCurrent += numRate;
		else going = false;

		if (numCurrent >= numStart && !going) numCurrent -= numRate;
		else going = true;

		return numCurrent;
	}

	float numStart, numEnd, numCurrent, numRate;
	bool going;



};