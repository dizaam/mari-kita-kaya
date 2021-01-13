#ifndef _SYSTEM_H
#define _SYSTEM_H

#ifdef __linux__
    #include <ncurses.h>

#elif __APPLE__
    #include <ncurses.h>

#elif _WIN32
    #include "lib/curses.h"

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "dadu.h"
#include "kartu.h"
#include "map.h"
#include "properti.h"
#include "player.h"

#endif