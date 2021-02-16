#ifndef _ALLHEADER_H
#define _ALLHEADER_H

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

#include "bot.h"
#include "dice.h"
#include "card.h"
#include "map.h"
#include "property.h"
#include "player.h"
#include "menu.h"
#include "game.h"

#endif