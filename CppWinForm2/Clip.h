#pragma once;
#include "Transform.h"

void Clip1Left(point &A, float dx, float dy, float dXl);

void Clip1Top(point &A, float dx, float dy, float dYt);

void Clip1Bottom(point &A, float dx, float dy, float dYb);

void Clip2Right(point &A, point &B, float dx, float dy, float dXr);

void Clip2Top(point &A, point &B, float dx, float dy, float dYt);

void Clip2Bottom(point &A, point &B, float dx, float dy, float dYb);

bool clip(point &A, point &B, point Pmin, point Pmax);