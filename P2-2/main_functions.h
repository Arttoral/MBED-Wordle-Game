#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"
#include "speech.h"



void set_random_seed(Timer t, GameInputs inputs);
void loop(GameInputs inputs, Timer t, int dt);
int start_screen();
int getGameTimer();
void stopGameTimer();


#endif