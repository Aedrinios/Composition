//
// Created by Ronan on 25/01/2021.
//

#include "StringHelpers.h"
#include <iostream>

void StringHelper::toLower(std::string *str) {
	for (char &c : *str) {
		c = std::tolower(c);
	}
}

void StringHelper::toUpper(std::string *str) {
	for (char &c : *str) {
		c = std::toupper(c);
	}
}

int StringHelper::StringToInt(const std::string &value) {
	try {
		return std::stoi(value);
	}
	catch (std::invalid_argument const &e) {
		std::cout << "Bad input: std::invalid_argument thrown" << std::endl;

	}
	catch (std::out_of_range const &e) {
		std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
	}
	return 0;
}

