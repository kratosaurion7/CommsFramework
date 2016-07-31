#pragma once

class TgaFile;

#include <string>

float* CreateSinusTrack(int amount, int amplitude);

float* SmoothCurveTrack(float* track, int trackLength, int factor);

int avg(int one, int two);
float favg(float one, float two);

TgaFile* PlotSequenceToImage(float* curve, int curveLength);