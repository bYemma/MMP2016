#include "ImageLoader.h"
#include <dirent.h>

ImageLoader* ImageLoader::ilInstance = 0;

ImageLoader::ImageLoader() {
	loadImages();
}

ImageLoader* ImageLoader::getInstance()
{
	if (ilInstance)
		ilInstance = new ImageLoader();
	return ilInstance;
}

Sprite* ImageLoader::load(ProjectileFactory::MunitionType mt)
{
	switch (mt) {
	case ProjectileFactory::MunitionType::NADE:
		return images["res\ball.png"];
		break;
	}
	return nullptr;
}

void ImageLoader::loadImages()
{
	if (initalized) {
		CCLOG("Images already loaded!");
		return;
	}
	std::vector<std::string> files = ImageLoader::listFiles();
	for (std::vector<std::string>::const_iterator ci = files.begin(); ci != files.end(); ++ci){
		images[*ci] = GameSprite::create(*ci);
	}
	
}

std::vector<std::string> ImageLoader::listFiles() {
	DIR *pDIR;
	struct dirent *entry;
	std::vector<std::string> filelist;
	if (pDIR = opendir("./res")) {
		while (entry = readdir(pDIR)) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				filelist.push_back(entry->d_name);
		}
		closedir(pDIR);
	}

	return filelist;
}

