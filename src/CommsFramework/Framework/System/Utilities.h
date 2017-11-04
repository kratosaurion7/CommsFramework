#pragma once

#include <stdio.h>
#include <fstream>

#include <string>

void DumpData(const char* data, int size, std::string outputName = "output.png");

uint32_t GetTicks();

float SafeCharToFloat(char* data, float defaultValue = 0);