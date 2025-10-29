#include "main_functions.h"
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "doubly_linked_list.h"

void init_keyboard();
void moveleft();
void moveright();
void select_letter();
void remove_letter();
void check_word();
void endGame(int row);
void keyboardAnimate(LLNode* curr);
void setWord(char word[6]);
void endKeyboard();