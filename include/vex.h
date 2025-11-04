#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"
#include "util.h"

#include "PID.h"
#include "Drive.h"
#include "Odom.h"
#include "images.h"
#include "screen.h"
#include "auton.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)