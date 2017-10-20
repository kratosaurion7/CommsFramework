#pragma once

class TgaFile;

#include <string>

/* Functions to create sequence of points */
float* CreateSinusTrack(int amount, int amplitude);
float* CreateCosineTrack(int amount, int amplitude);
float* CreateTangentTrack(int amount);

/* Enlarges the curve to allow more points in between the existing points of the curve.
 * The result curve will be 'trackLength*factor' long. The function works by averaging each point
 * together and insert 'factor-1' points between each points.*/
float* SmoothCurveTrack(float* track, int trackLength, int factor);

/* Averaging functions */
int avg(int one, int two);
float favg(float one, float two);

/** Represent the pixels of a curve into an image.
 *  The image will have the height of 'amplitude*2' and a width of 'curveLength' */
TgaFile* PlotSequenceToImage(float* curve, int curveLength);