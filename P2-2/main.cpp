//=================================================================
// The main program file.
//
// Copyright 2024 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <cstring>
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"
#include "speech.h"

#include "main_functions.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

void set_random_seed(Timer t, GameInputs inputs);
void loop(GameInputs, Timer, int);
int start_screen();

Timer gameTimer;

/*
* This function handles the main logic of the game. You should
* initialize the hardware in this function, make calls to 
* functions that update the keyboard and your guess of 
* the word. 
*/
int main()
{
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    printf("Program Starting\n");
    //led1 hardware initialization
    myled1=1;  
    
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    /* Put code here to initialize the game state:
    1) you will need to use a psuedo random number generator such as
        rand() to randomly select a goal word from the dictionary.
        The random function needs to be seeded before you call rand(),
        otherwise, rand() will always generate the same series of numbers.
        Call the function set_random_seed -- you need to complete its
        definition below.*/
    /*
    2) call init_keyboard() and show start screen
    
    3) initialize any other game state that you add.
    */
    
    loop(inputs, t, dt);
    return 0;
}


// Set timer, display start screen
void set_random_seed(Timer t, GameInputs inputs) {
    char* tmp = (char*) "Random word (b1)\n";
    uLCD.printf(tmp);
    wait_us(1000);
    char* choose = (char*) "Choose word (b2)\n";
    uLCD.printf(choose);
    wait_us(1000);
    // WORD GENERATION
    while(1){
        inputs = read_inputs();
        //add word generate functionality or choosing.
        
        if(inputs.b1) {
            char* button = (char*) "b1.\n";
            uLCD.printf(button);
            break;

        }
        
        if(inputs.b2) {
            char* button = (char*) "b2.\n";
            char word[6];
            uLCD.printf("%s", button);
            printf("Enter a 5-letter word: ");
            scanf("%5s", word);
            printf("%s\n", word);
            setWord(word);
            break;
        }
        
        // Compute update time
        wait_us(2500);

    }
    wait_us(200000);
    t.stop();
    int seed = t.read_ms(); 
    srand(seed);
    uLCD.cls();
}


void loop(GameInputs inputs, Timer t, int dt) {
    
    start_screen();
    set_random_seed(t, inputs);

    draw_sprite();
    
    init_keyboard();
    draw_lower_status();
    
    gameTimer.reset();
    gameTimer.start();
    while(1)
    {
        t.start();
        myled2 =!myled2; //blink led2 to show game progress


        inputs = read_inputs();

        if(inputs.left) {
            moveleft();
            
            printf("move left\n");
        }
        
        if (inputs.right) {
            moveright();
            printf("move right\n");

        }
        
        if(inputs.center) {
            select_letter();
            printf("Select Letter\n");

        }
        
        if(inputs.b2) {
            remove_letter();
            printf("Remove letter\n");

        }


        uLCD.locate(4,0);
        int time = gameTimer.read_ms()/1000;
        uLCD.printf("Time: %02d:%02d", time / 60, time % 60);

        if(inputs.b3) {
            Timer t;
            int dt;
            t.start();
            uLCD.cls();
            loop(inputs, t, dt);
        }

        // Compute update time
        t.stop();
        dt = t.read_ms();
        if (dt < 100) wait_us((100 - dt)*2500);
    }
}


int start_screen() {
    uLCD.color(BLUE);
    uLCD.text_bold(1);
    char wordle[] = "Wordle";
    uLCD.locate(6,0);
    uLCD.puts(wordle);
    wait_us(1000);

    uLCD.color(WHITE);
    uLCD.text_bold(0);
    char intro[] = "Welcome to wordle!\nUse the Nav switch\nto explore!";
    uLCD.locate(0,4);
    uLCD.puts(intro);
    wait_us(1000);

    uLCD.color(GREEN);
    uLCD.text_bold(1);
    char play[] = "Play";
    uLCD.locate(7, 12);
    uLCD.puts(play);
    wait_us(1000);

    GameInputs inputs;
    int track = 1;
    char clear[] = "                   ";
    char image[] = "Instructions";
    char hard[] = "Hard Mode";
    int display = 1;

    while(1) {
        inputs = read_inputs();
        
        if(inputs.down) {
            if(track < 3) {
                track++;
                display = 1;
            }
            wait_us(10000);
        }


        if(inputs.up) {
            if(track > 1) {
                track--;
                display = 1;
            }
            wait_us(10000);
            

        }

        if(inputs.center) {
            uLCD.color(DGREY);
            uLCD.text_bold(1);

            if(track == 1) {
                uLCD.locate(7, 12);
                uLCD.puts(play);
                wait_us(1000000/2);
                uLCD.cls();
                return 0;
            }   

            if(track == 2) {
                uLCD.locate(3, 12);
                uLCD.puts(image);
                wait_us(1000000/2);
                uLCD.cls();

                uLCD.color(WHITE);
                uLCD.text_mode(OPAQUE);
                char lines[] =  "Use nav switch to\nselect a letter.\nPress to submit.\nB2 removes.\nGreen = correct,\nYellow = wrong pos.\nPress any button\nto exit.";
                wait_us(10000);
                uLCD.puts(lines);
                    while(1){
                    inputs = read_inputs();
                    if (inputs.b1 || inputs.b2 || inputs.b3 || inputs.center) {
                        break;
                        }
                    }
                uLCD.cls();
                wait_us(10000);
                return start_screen();
            }
        
            if(track == 3) {
                uLCD.locate(4, 12);
                uLCD.puts(hard);
                wait_us(1000000/2);
                uLCD.cls();
                return 1;
            }
        }
        

        if(display) {
            uLCD.locate(0, 12);
            uLCD.puts(clear);
            uLCD.color(GREEN);
            uLCD.text_bold(1);


            if(track == 1) {
                uLCD.locate(7, 12);
                uLCD.puts(play);
                wait_us(10000);
            }
        
            if(track == 2) {
                uLCD.locate(3, 12);
                uLCD.puts(image);
                wait_us(10000);
            }

            if(track == 3) {
                uLCD.locate(4, 12);
                uLCD.puts(hard);
                wait_us(10000);

            }
            display = 0;
        }

        wait_us(1000);
    }
}


int getGameTimer() {
    return gameTimer.read();
}
void stopGameTimer() {
    gameTimer.stop();
}
