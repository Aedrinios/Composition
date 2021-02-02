//
// Created by Ronan on 25/01/2021.
//

#ifndef COMPOSITION_STRINGHELPERS_H
#define COMPOSITION_STRINGHELPERS_H

#include <string>

namespace StringHelper {
	/**
	 * Lower case
	 * @param str to lower
	 */
	void toLower(std::string *str);

	/**
	 * Upper case
	 * @param str to Upper
	 */
	void toUpper(std::string *str);

	/**
	 * Convert std::string to Int
	 * @param value
	 * @return converted value
	 */
	int StringToInt(const std::string &value);
}
#endif //COMPOSITION_STRINGHELPERS_H
