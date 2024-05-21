#pragma once

#include "vex.h"

float pi();

float reduce_to_180s(float input);

float Rad_to_Deg(float input);

float Deg_to_Rad(float input);

float clamp(float value, float minClamp, float maxClamp);
