#include "keyboard.h"
#include "dictionary.h"
#include "doubly_linked_list.h"
#include "hardware.h"
#include "speech.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

#include "main_functions.h"

DLinkedList* keyboard;
LLNode* curr;
char currTest;
char* goal_word;
char guess[6];
int idx_2;
int row;
char* currData;
char* hint1;
char* hint2;
int newInd;
char selectedWord[6] = "null";
int highScore = INT_MAX;
bool notSet = true;


/*
* Function to implement comparisons of data in the DLL.
* This function allows the comparisons of chars if you input
* chars into the doubly_linked_list. If you want you can make 
* additional functions to compare different types of data.
*
* This function should be passed into the create_dLinkedList()
* call.
*
*/
int compareChar(void* input1, void* input2){
    if(*(char*)input1 == *(char*)input2){
        return 1;
    }
    else{
        return 0;
    }
}

void init_keyboard()
{
    // Select random word from dictionary
    int random_word_ind = rand() % 30; // change with size of dictionary
    Word random_selection = dictionary[random_word_ind];

    
    if(notSet) {
        goal_word = random_selection.letters;
    }
    notSet = true;

    hint1 = random_selection.hint1;
    hint2 = random_selection.hint2;
    idx_2 = 0;
    row = 0;
    printf("Goal word is %s\n\r", goal_word);

    // Instantiate alphabet keyboard
    keyboard = create_dlinkedlist();
    char initial_char = 'a';
    char* current = (char*)malloc(sizeof(char));
    *current = initial_char;
    insertHead(keyboard, (void*)current);
    /*
    YOUR CODE HERE
    Populate the 'keyboard' linked list with the rest of the letters of the alphabet (b-z)
     */
    
    for(int i = 1; i < 26; i++) {
        char* newCurr = (char*)malloc(sizeof(char));
        *newCurr = initial_char + i;
        insertTail(keyboard, newCurr);
    }

    curr = getHead(keyboard);
    keyboard->head->prev = keyboard->tail;
    keyboard->tail->next = curr;

    uLCD.color(WHITE);
    uLCD.locate(8,15);
    ASSERT_P(getData(curr) != NULL, getSize(keyboard));
    uLCD.puts((char*) getData(curr));

    keyboardAnimate(curr);

}

void moveleft()
{
    /*
    YOUR CODE HERE (Feature 1)
    1) Update the global 'curr' to the left (previous letter) and display
    */
    ASSERT_P(curr != NULL, -1);
    if(getPrev(curr)) {
        curr = getPrev(curr);
    }
    uLCD.locate(8,15);
    uLCD.puts((char*) getData(curr));
    keyboardAnimate(curr);
    wait_us(10000);
}
void moveright()
{
    /*
    YOUR CODE HERE (Feature 1)
    1) Update the global 'curr' to the right (next letter) and display
    */
    ASSERT_P(curr != NULL, -getSize(keyboard));

    if(getNext(curr)) {
        curr = getNext(curr);
    }
    uLCD.locate(8,15);
    uLCD.puts((char*) getData(curr));
    keyboardAnimate(curr);
    wait_us(10000);

}

void select_letter()
{   
    /*
    YOUR CODE HERE (Feature 2)
    1) Update the next letter of your guess with the current 
        letter from the keyboard
        a) use globals guess and idx_2
    2) Display the letter on the uLCD screen in the correct location (Feature 4)
        a) see uLCD.locate() and uLCD.puts()
    3) Increment idx_2
    4) If the guess is completed, call check_word() to check the guess
    */

        guess[idx_2] = *(char*) getData(curr);
        uLCD.locate(6 + idx_2, row + 4);
        uLCD.puts((char*) getData(curr));
        idx_2 = idx_2 + 1;
        if(idx_2 == 5) {
            check_word();
        }
        wait_us(250000);


}

void remove_letter()
{   
    /*
    YOUR CODE HERE (Feature 3)
    1) Remove the current letter of your guess
    2) Remove the letter from the uLCD screen 
        (this can be done in multiple ways)
    3) Decrement idx_2
        a) Hint: prevent decrement in certain edge case
    */
    if(idx_2 > 0) {
        idx_2--;
        guess[idx_2] = NULL;
        uLCD.locate(6 + idx_2, row + 4);
        uLCD.putc(' ');
        wait_us(250000);
    }

}

void check_word() 
{
    /* YOUR CODE HERE (Feature 5, 6, 7, 8, 9)
    Implement an algorithm to check the word
    1) If a letter is in the word, and in the correct location in the guess
        a) Leave it on the screen in the correct position
        b) Display it at the top of the screen with the other correct letters
        c) Leave it in the keyboard
    2) If a letter is in the word, but in the wrong location in the guess
        a) Remove it from the guess on the screen
        b) Display it at the top of the screen with the other correct letters
        c) Leave it in the keyboard
    3) If a letter is not in the word, but is in the guess
        a) Remove it from the guess on the screen
        b) Remove it from the keyboard
    4) If a guess is fully correct, display the 'You Win!' screen
    5) If the player just submitted their 5th guess and it was incorrect
        call speech() to display the hint
    6) If the player just submitted their 6th guess and it was incorrect
        display the "You Lose :(" screen
    */
    int i = 0;
    while(i < 5) {
        if (guess[i] == goal_word[i]) {
            wait_us(1000);
            uLCD.locate(6 + i, row + 4);
            uLCD.color(GREEN);
            uLCD.putc(goal_word[i]);
        } else {
            bool found = false;
            for(int m = 0; m < 5; m++) {
                if(guess[i] == goal_word[m]) {
                    wait_us(1000);
                    uLCD.locate(6 + i, row + 4);
                    uLCD.color(YELLOW);
                    uLCD.putc(guess[i]);
                    found = true;
                }
            } 
            if(!found) {
                //remove from guess
                wait_us(1000);
                uLCD.locate(6 + i, 4 + row);
                uLCD.color(DGREY);
                uLCD.putc(guess[i]);
                //remove from keyboard
                LLNode* root = getHead(keyboard);
                for(int k = 0; k < getSize(keyboard); k++) {
                    if(*(char*) getData(root) == guess[i]) {
                        deleteNode(keyboard, root);
                    }
                    root = getNext(root);
                }
            }

        }
        i++;
    }
    uLCD.color(WHITE);
    row = row + 1;
    idx_2 = 0;
    endGame(row);
}




void endGame(int row) {
    bool same = true;
    for(int i = 0; i < 5; i++) {
        if(goal_word[i] != guess[i]) {
            same = false;
        }
    }

    GameInputs inputs;

    if(same) {
        stopGameTimer();
        uLCD.cls();
        uLCD.locate(4, 7);
        char* win = (char*) "You Win!!!!\n";
        uLCD.printf("%s", win);
        
        if(getGameTimer() < highScore) {
            highScore = getGameTimer();
        }

        uLCD.locate(0,12);
        uLCD.printf("High Score: %.2d: %.2d", highScore/60, highScore%60);
        uLCD.locate(0, 14);
        char* reset = (char*) "Push to restart.\n";
        uLCD.printf("%s", reset);
        while(1) {
            inputs = read_inputs();
            if(inputs.b1 || inputs.b2 || inputs.b3) {
                Timer t;
                int dt;
                t.start();
                uLCD.cls();
                loop(inputs, t, dt);
            }
        }
        return;
    }

    if(row == 5) {
        speech(hint1, hint2);
    }


    if(row == 6) {
        uLCD.cls();
        uLCD.locate(4, 7);
        char* gameOver = (char*) "You lose.\n";
        uLCD.printf("%s", gameOver);
        uLCD.locate(0, 14);
        char* reset = (char*) "Push to restart.\n";
        uLCD.printf("%s", reset);
        endKeyboard();

        while(1) {
            inputs = read_inputs();
            if(inputs.b1 || inputs.b2 || inputs.b3) {
                Timer t;
                int dt;
                t.start();
                uLCD.cls();
                loop(inputs, t, dt);
            }
        }
    }
}


void keyboardAnimate(LLNode* curr) {
    if(getPrev(curr)) {
        uLCD.color(LGREY);
        uLCD.locate(6,15);
        uLCD.putc(*(char *) getData(getPrev(curr)));
        if(getPrev(getPrev(curr))) {
            uLCD.color(DGREY);
            uLCD.locate(4,15);
            uLCD.putc(*(char *) getData(getPrev(getPrev(curr))));
        }
        uLCD.color(WHITE);
    }
    if(getNext(curr)) {
        uLCD.color(LGREY);
        uLCD.locate(10,15);
        uLCD.putc(*(char *) getData(getNext(curr)));
        if(getNext(getNext(curr))) {
            uLCD.color(DGREY);
            uLCD.locate(12,15);
            uLCD.putc(*(char *) getData(getNext(getNext(curr))));
        }
        uLCD.color(WHITE);
    }

}

void setWord(char word[6]) {
    notSet = false;
    goal_word = (char*) malloc(6 * sizeof(char));
    strncpy(goal_word, word, 5);
    goal_word[5] = '\0';
}

void endKeyboard() {
    destroyList(keyboard);
}