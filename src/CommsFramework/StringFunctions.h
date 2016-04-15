#pragma once

#include <string>

#include "BaseList.h"


BaseList<std::string>* StringSplit(std::string str, char* delimiter);

/*
 * Take a string a and subtract b from it
 *
 */
std::string StringSubtract(std::string a, std::string b);