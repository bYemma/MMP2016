#pragma once
#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "ProjectileFactory.h"

class ImageLoader {

	static ImageLoader* ilInstance;

public:
	static ImageLoader* getInstance();
	Sprite* load(ProjectileFactory::MunitionType mt);
private:

	ImageLoader();
	std::vector<std::string> listFiles();
	bool initalized;
	void loadImages(); //loads all Images in directory
	//into map
	std::map<std::string, Sprite*> images;
};