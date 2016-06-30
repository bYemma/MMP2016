#pragma once

#include <iostream>
#include <vector>

using namespace std;

class GameMap {

public:
	GameMap();
	virtual ~GameMap();
	void createMap(double max_abs, double min_abs, double y_offset, int times);
	vector<double> getPoints();
private:
	vector<double> points;
	double fRand(double fMin, double fMax);
};