/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: logic.c

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
// However, please read through this section and look at the declarations of arrays and global vars that you will be using in your program


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "uni.h"


int SerNum=0;			// a counter to create unique star numbers (identifiers)
int numStars = 0;		// the actual number of stars in the universe (not the same as the maximum)
int numPairs = 0;		// the number of pairs that have been named

Star *stars[MaxStar];		// the array of stars (an array of pointers to stars)
Pair *pairs[MaxPair];		// the array of named pairs (an array of pointers to pairs)

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// NOW IT IS YOUR TURN, YOU CAN DEFINE ANY OTHER GLOBAL VARIABLES YOU MAY NEED IN YOUR CODE BELOW THIS LINE

FILE *myfile;
int previous_Stars = 0;
int previous_Pairs = 0;

// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// Initially, some of these functions contain 'return 0' or 'return -99'. Before implementing a function you should delete this statement
// None of the functions should cause memory leaks


// The purpose of this function is to find a star through its coordinates.
// The first two parameters are the coordinates of the star we are looking for.
// Since the coordinates are double (real) numbers, we cannot compare them for exact equality,
// hence the 3rd parameter to this function is a very small number (e.g. 0.00000001) called the tolerance.
// If the absolute difference between the x (or y) coordinate of a star and the given x (or y) coordinate
// is less than the tolerance, we assume that the two values are equal.
// If a star with the given x and y coordinates is found, the function should return a pointer to this star
// otherwise the function returns 0 indicating failure to find a star with such coordinates.
// 4-6 lines of code.
Star* findStarByXY  (double x , double y, double tolerance)
{
	int count = 0;
	for (int i = 0; i < numStars; i++){
		if ((fabs(stars[i]->x - x) < tolerance) && (fabs(stars[i]->y - y) < tolerance)){
			return stars[i];
			i = numStars;
			count = 1;
		}
	}
	if (count == 0){
		return 0;
	}

}

// The purpose of this function is to create a new universe containing stars only.
// The number of stars in this new universe is given by the parameter n_stars.
// The stars should be randomly scattered within the universe, i.e, each star should be assigned a random value
// for its x and y coordinates. x can take any random value from [0 - MaxX] inclusive,
// and y can take any random value from [0 - MaxY] inclusive.
// Although the x and y coordinates of a star are defined as double numbers, for simplicity we will only
// assign whole numbers to x and y. Every star should have its unique location, no two stars can have the same x and y coordinates.
// Hence the maximum number of stars in a completely filled universe that is 60 lights years long and 30 light years wide
// is 1891 stars (this is the value of MaxStar defined in uni.h). The minimum number of stars in a universe is 1.
// If the function fails to create the universe for any reason (including an invalid value of n_stars), it should return 0
// indicating failure, otherwise it should return 1 indicating success.
// Since this function is the start of a new universe, it should also initialise all global variables.
int bigBang (int n_stars)
{
	if (n_stars < 0 || n_stars > 1891){
		return 0;
	}else{
		numStars = 0;
		numPairs = 0;
		double temp_x = rand() % (MaxX +1);
		double temp_y = rand() % (MaxY +1);
		SerNum = 0;
		for (int i = 0; i < n_stars; i++){
			//loops while a star doesn't have distinct x and y points
			stars[i] = (Star *) malloc(sizeof(Star));
			numStars +=1;
			int validCounter = 0;
			while (validCounter == 0){
				temp_x = rand() % (MaxX +1);
				temp_y = rand() % (MaxY +1);
				// creates a random x and y

				// loops for all the elements that have been created
				if (findStarByXY(temp_x,temp_y,0.000001) == 0){
					validCounter = 1;
				}
			}
			stars[i]->x = temp_x;
			stars[i]->y = temp_y;
			stars[i]->named = 0;
			stars[i]->id = SerNum;
			SerNum +=1;
		}
	}


}


// The purpose of this function is to compute the distance between two points in a Cartesian plane.
// The coordinates of the first point are x1 , y1.
// The coordinates of the second point are x2, y2.
// The function returns the distance between the two points.
// 2 lines of code.
double pointDistance (double x1, double y1, double x2, double y2)
{
	return sqrt( pow(x1-x2,2)+pow(y1-y2,2) );
}


// The purpose of this function is to find the closest pair of stars that have not been named yet.
// If a pair cannot be found (e.g. because all pairs have already been named) the function should return 0 (null),
// otherwise the function should return a pointer to a Pair structure initialised with h pointing to the first star in the pair
// and w pointing to the second star.
Pair* closestPair ()
{
	double distance = sqrt(4500); // storing the shortest distance
	double temp = 0;

	// compare each star against eachother
	if (numStars < 2 || numPairs == numStars/2){
		return 0;
	}else{
		for (int i = 0; i < numStars;i++){
			if (stars[i]->named == 1){
				i++;
			}
			for (int j = 0; j < numStars; j++){
				if (stars[j]->named == 1){
					j++;
				}
				if (i != j){
					if ( (stars[i]->named == 0) && (stars[j]->named == 0) ){
						temp = pointDistance(stars[i]->x,stars[i]->y,stars[j]->x,stars[j]->y);
						if (temp < distance){
							distance = temp;
							pairs[numPairs]->h = stars[i];
							pairs[numPairs]->w = stars[j];
						}
					}
				}
			}
		}
		numPairs +=1;
		return pairs[numPairs];
	}

}

// The purpose of this function is to assign the name of a person to a star.
// The first parameter is a pointer to the star to be named.
// The second parameter is the first name of the person.
// The last parameter is the surname of the person.
// The function should append the surname to the first name - with one single space in between - to create one single string for the full name.
// For example, if the first name is "Mr" and the surname is "Bean", the full name string will be "Mr Bean".
// If everything goes well and the star is named, the function returns 1 indicating success.
// The function also sets the named flag of the star to 1.
// If anything goes wrong (including invalid parameter values), the function should return 0 indicating failure.
int nameStar (Star *s, char* first_name, char* sur_name)
{
	if (s == 0 || first_name == 0 || sur_name == 0|| (strlen(first_name) +strlen(sur_name) > 28) ){
		return 0;
	}else{
		strcpy(s->name,first_name);
		strcat(s->name," ");
		strcat(s->name,sur_name);
		s->named = 1;
		return 1;
	}
}


// The purpose of this function is to find a pair by the name of either spouse (one of the owners of the pair).
// The parameter to this function is the full name of a person.
// If either star in a named pair have this name, the function returns a pointer to this pair,
// If no such pair is found the function returns 0
Pair* findPairByName (char* name)
{
	int count = 0;
	int len = strlen(name);
	// iterate over all the pairs of stars and compare their names to the parameter variable
	for (int i = 0; i < numPairs; i++){
		if (strcmp(pairs[i]->h->name,name) == 0 || strcmp(pairs[i]->w->name,name) == 0){
			return pairs[i];
			i = numPairs;
			count = 1;
		}
	}
	if (count == 0){
		return 0;
	}
}

// The purpose of this function is to save all the data of the program to a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1 indicating success in saving the universe
int saveUniverse ()
{
		Star temp[numStars];
		Pair tpairs[numPairs];

	for (int i = 0; i< numStars; i++){
		stars[i] = (Star *) malloc(sizeof(Star));
		temp[i].id = stars[i]->id;
		temp[i].x = stars[i]->x;
		temp[i].y = stars[i]->y;
		temp[i].named = stars[i]->named;
		strcpy(temp[i].name,stars[i]->name);
	}

	for (int a = 0; a < numPairs; a++){
		pairs[a] = (Pair *) malloc(sizeof(Pair));
		tpairs[a].h= pairs[a]->h;
		tpairs[a].w= pairs[a]->w;
		tpairs[a].d = pairs[a]->d;
	}

	// need to store the star pointers into an array of struct with all the elements
	myfile = fopen("universe.bin","w");
	if (!myfile){
		return 0;
	}else{
		for (int i = 0; i< numStars; i++){
			stars[i] = (Star *) malloc(sizeof(Star));
			temp[i].id = stars[i]->id;
			temp[i].x = stars[i]->x;
			temp[i].y = stars[i]->y;
			temp[i].named = stars[i]->named;
			strcpy(temp[i].name,stars[i]->name);
		}

		for (int a = 0; a < numPairs; a++){
			pairs[a] = (Pair *) malloc(sizeof(Pair));
			tpairs[a].h= pairs[a]->h;
			tpairs[a].w= pairs[a]->w;
			tpairs[a].d = pairs[a]->d;
		}

		previous_Pairs = numPairs;
		previous_Stars = numStars;
		fwrite(temp,sizeof(Star),numStars,myfile);
		fwrite(tpairs,sizeof(Pair),numPairs,myfile);
		return 1;
	}
}



// The purpose of this function is to load a universe from a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1, indicating success in loading the universe
int loadUniverse ()
{
	Star temp[previous_Stars];
	Pair tpairs[previous_Pairs];

	myfile = fopen("universe.bin","r");
	if (!myfile){
		return 0;
	}else{
		fread(temp,sizeof(Star),previous_Stars,myfile);
		fread(tpairs,sizeof(Pair),previous_Pairs,myfile);

		for (int i = 0; i< previous_Stars; i++){
			stars[i] = (Star *) malloc(sizeof(Star));
			stars[i]->id = temp[i].id;
			stars[i]->x = temp[i].x;
			stars[i]->y = temp[i].y;
			stars[i]->named = temp[i].named;
			strcpy(stars[i]->name,temp[i].name);
		}

		for (int a = 0; a < previous_Pairs; a++){
			pairs[a] = (Pair *) malloc(sizeof(Pair));
			pairs[a]->h =tpairs[a].h;
			pairs[a]->w = tpairs[a].w;
			pairs[a]->d = tpairs[a].d;
		}
		return 1;
	}

	return -99;
}

// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW
// WITH THEIR PROTOTYPES DEFINED IN THE GLOBAL VARS SECTION OF THIS FILE
//----------------------------------------------------------------------
