/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: main.c

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Daniel Lartey
Student ID: 201417135
Email: sc20dl@leeds.ac.uk
Date Work Commenced: 06/12/20
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uni.h"


// Use the following format strings in your printf statements so that your program output will be identical to mine
//-----------------------------------------------------------------------------------------------------------------
/*

"star %i\n"
"name: %s\n"
"coords: (%.3f,%.3f)\n"
"Pair %i:\n"
"distance: %f\n"
"**************************\n"
"The Big Bang has occurred!\n"
"Sorry, unable to bang!\n"
"Sorry no pairs were found!\nWish you a better luck in the next universe\n"
"The closest pair of stars are no. %i and %i\n"
"They are %.3f light years apart\n"
"Would you like to name this pair (y/n)?"
"Enter your full name:"
"Enter your spouse full name:"
"Congratulations a pair of stars has been named after you and your spouse\n"
"Thanks, you have saved the universe!\n"
"Congratulations, your saved universe was restored!\n"
"No such command!\n"

*/


// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************



// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// initially, some of these functions contain 'return 0'. Before implementing a function you should delete this statement



// Print the details of a star
void printStar (Star* s)
{
  printf("star %i\n", s->id);
  printf("name: %s\n", s->name);
  printf("coords: (%.3f,%.3f)\n",s->x,s->y);
  if (s->named == 1){
    printf("name: %s\n",s->name);
  }
  // find a way to get which pair it is in printed
}

// Display a list of all stars in the universe
void listStars ()
{
  for (int i = 0; i <numStars; i++){
    printf("star %i\n",stars[i]->id);
    if (stars[i]->named == 1){
      printf("name: %s\n",stars[i]->name);
    }
    printf("coords: (%.3f,%.3f)\n",stars[i]->x,stars[i]->y);
  }

}

// List all named pairs
void listPairs ()
{
  for (int i = 0; i < numPairs; i++){
    printf("Pair %i\n",i);
    printf("distance: %f\n",pairs[i]->d);
    printf("star %i\n",pairs[i]->h->id);
    printf("name: %s\n",pairs[i]->h->name);
    printf("coords: (%.3f,%.3f)\n",pairs[i]->h->x,pairs[i]->h->y);
    printf("star %i\n",pairs[i]->w->id);
    printf("name: %s\n",pairs[i]->w->name);
    printf("coords: (%.3f,%.3f)\n",pairs[i]->w->x,pairs[i]->w->y);
    printf("**************************\n");
  }

}

// Draw the entire universe
void drawUniverse ()
{
  for (int i = 0; i < numStars;i++){
    if (stars[i]->named == 0){
      plot(stars[i]->x,stars[i]->y,".");
    }else{
      plot(stars[i]->x,stars[i]->y,"*");
    }
  }
  showBuffer();
}

// Tag a named pair of stars by writing a string comprising the names of the couple that own the pair
// underneath this pair in the frame buffer (see assignment brief)
// The names of the 2 owners should be concatenated into one string with an & sign in between.
// The name of the h star should be first followed by the name of the w star (by the way, h stands for husband and w stands for wife).
// For example, if the the h star name is "Mr Bean" and the w star name is "Irma Gobb", the string will be "Mr Bean & Irma Gobb"
// with exactly one space before and after the &.
// The string should be positioned one row below the h star's row, with the middle of the string aligned with the h star's column
// Calling this function will NOT cause the frame buffer to be redisplayed on the screen, if you need to show the frame buffer, you must
// call showBuffer (but NOT inside this function)

void tagPair (Pair* p)
{
  char *names[62];
  strcpy(names,p->h->name);
  strcat(names," & ");
  strcat(names,p->w->name);
  int new_row = p->h->x + 1;
  writeAt(new_row,p->h->y,names);
}

// DON'T CHANGE THE FOLLOWING 3 LINES
#ifndef TEST
int  main (int argc, char* argv[])
{
  time_t t;
  srand((unsigned) time(&t));
	// ENTER THE CODE OF YOUR main FUNCTION BELOW


// DON'T CHANGE THE FOLLOWING 2 LINES
}
#endif
// DON'T WRITE ANYTHING BELOW THIS LINE
