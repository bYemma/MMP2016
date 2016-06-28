#include "GameMap.h"
#include <ctime>
#include <algorithm>

GameMap::GameMap()
{
	createMap(0.5, 0.1, 0.1, 100);
}

GameMap::~GameMap()
{
}

void GameMap::createMap(double max_abs, double min_abs, double y_offset, int steps) {
	srand(static_cast<unsigned int>(time(NULL))); // Init rand
	points.resize(steps);
	double point = fRand(min_abs, max_abs);
	for (unsigned i = 0; i <= steps; ++i) {
		point = fRand(max(point - y_offset, min_abs), min(point + y_offset, max_abs));
		points[i] = point;
		cout << point << endl;
	}
}

vector<double> GameMap::getPoints() {
	return points;
}

double GameMap::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}