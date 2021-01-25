//
// Created by Ronan on 25/01/2021.
//

#include "StringHelpers.h"

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
