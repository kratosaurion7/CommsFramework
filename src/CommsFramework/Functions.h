#pragma once

class TgaFile;

#include <string>

float* CreateSinusTrack(int amount, int amplitude);
float* CreateCosineTrack(int amount, int amplitude);
float* CreateTangentTrack(int amount);

float* SmoothCurveTrack(float* track, int trackLength, int factor);

int avg(int one, int two);
float favg(float one, float two);

TgaFile* PlotSequenceToImage(float* curve, int curveLength);