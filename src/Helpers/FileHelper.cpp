//
// Created by Ronan on 27/01/2021.
//

#include "FileHelper.h"
#include <filesystem>

bool FileHelper::exist(const std::string &path) {
	return std::filesystem::exists(path);
}

bool FileHelper::createDirectory(const std::string &path) {
	std::filesystem::create_directories(path);
	return FileHelper::exist(path);
}

bool FileHelper::remove(const std::string &path) {
	if (FileHelper::exist(path)) {
		std::filesystem::remove_all(path);
		return !FileHelper::exist(path);
	} else {
		return true;
	}
}

bool FileHelper::clearDirectory(const std::string &path){
	FileHelper::remove(path);
	return FileHelper::createDirectory(path);
}

