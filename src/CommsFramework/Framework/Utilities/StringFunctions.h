#pragma once

#include <string>
#include <string.h>
#include "Collections/BaseList.h"


BaseList<std::string>* StringSplit(std::string str, const char* delimiter);

/*
 * Take a string a and subtract b from it
 *
 */
std::string StringSubtract(std::string a, std::string b);