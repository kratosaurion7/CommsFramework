#pragma once

#include <stdio.h>
#include <fstream>

#include <string>

void DumpData(const char* data, int size, std::string outputName = "output.png");

int GetTicks();

float SafeCharToFloat(char* data, float defaultValue = 0);