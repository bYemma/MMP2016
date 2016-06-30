#include "MapScene.h"
#include "GameMap.h"
#include "GameLayer.h"
#include "iostream"

USING_NS_CC;

using namespace cocos2d;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	_sSize = Director::getInstance()->getWinSize();
	int height = _sSize.height;
	int width = _sSize.width;

	GameMap map;
	map.createMap(0.5, 0.1, 0.1, 100);
	vector<double> points = map.getPoints();
	/*
	auto rectNode = DrawNode::create();
	Vec2 map_shape[102];
	map_shape[0] = Vec2(0, 0);
	for (unsigned i = 0; i < points.size(); ++i) {
		map_shape[i+1] = Vec2(width / 100 * i, height * points[i]);
	}
	map_shape[101] = Vec2(width, 0);

	Color4F white(1, 1, 1, 1);
	rectNode->drawPolygon(map_shape, 102, white, 1, white);
	this->addChild(rectNode);
	*/
	return true;
}