// Autograder for the Graphics Module
// C Ammar Alsalka, 2020
// This is not a complete listing of the code.
// Some sections have been removed,
// and some lines have been replaced with comments.
// This file cannot be compiled.
// It is provided so that you know how
// the autograder/selfgrader tests your code
// Note: The AddTestString function reports the mark to Gradescope


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uni.h"

#define JsonStrSize 5000
#define Presubmission 1

int mustShow=0;
int stage= 1;
char* JsonStr;


// test plot function
int t_plot () // 2 marks
{
	int m=0;
	char s[100];
	tell ("\n*** Checking function plot (peek should be implemented for this to work) ***\n");
	tell ("#Checking it can handle invalid parameters\n");
	plot (-1, 10,'*');
	plot (60, -1, 'G');
	plot (33, 61, '.');
	plot (31, 60, 'i');
	tell ("#Checking it does plot correctly\n");
	plot (2,1,'X');
	char c = peek (2,1);
	if (c == 'X') m+=2;
	sprintf (s,"%i/2 for function plot", m);
	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 2, s, 0);
	return m;
}

// test peek function
int t_peek () // 2 marks
{
	char r;
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function peek (plot should be implemented for this to work)***\n");
	tell ("#Checking it can handle invalid parameters:");
	r = peek (-1, 10);
	if (r != 0) fail = 1;
	r = peek (60, -1);
	if (r != 0) fail = 1;
	r = peek (33, 61);
	if (r != 0) fail = 1;
	r = peek (32, 60);
	if (r != 0) fail = 1;
	if (!fail) 
	{
		tell ("Passed \n");
		m = 1;
	}
	else
		tell ("Failed\n");
	tell ("#Checking it does peek correctly:");
	plot (22, 17, 'v');
	r = peek (22,17);
	if (r == 'v') 
	{
		tell ("Passed\n");
		m+=1;
	}
	else
		tell ("Failed\n");
	sprintf (s,"%i/2 for function peek", m);
	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 2, s, 0);
	return m;
}

// test clearBuffer()
int t_clearBuffer () // 4 marks
{
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function clearBuffer ***\n");
	clearBuffer ();
	tell ("#Checking frame buffer is initialised correctly:");
	for (int i = 0 ; i < MaxRow ; i ++)
	{
		for (int j = 0 ; j < MaxCol; j++)
			if (peek(i,j) != 32)
			{
				fail = 1;
				break;
			}
		if (fail) break;
	}
	if (!fail) 
	{
		m+=4;
		tell ("Passed\n");
	}
	else
		tell ("Failed\n");

	sprintf (s,"%i/4 for function clearBuffer", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 4, s, 0);
	return m;
}


// test writeAt function
int t_writeAt () // 6 marks
{
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function writeAt (peek should be implemented for this to work) ***\n");
	tell ("#Checking it can handle invalid parameters\n");
	writeAt (-1, 10,"****");
	writeAt (60, -1, "Good morning");
	writeAt (33, 61, "This is a string.");
	writeAt (31, 60, "Too long to fit in its entirety");
	tell ("#Checking it does write correctly\n");
	char* str= "Good morning";
	writeAt (2,1,str);
	int j = 0;
	for (int i = 1; i < (int) strlen (str) ; i++)
	{
		if (peek (2, i) != str[j])
		{
			fail = 1;
			break;
		}
		j++;
	}
	char* str1= "Too long to fit in its entirety";
	writeAt (21,56,str1);
	j = 0;
	for (int i = 56; i < MaxCol ; i++)
	{
		if (peek (21, i) != str1[j])
		{
			fail = 1;
			break;
		}
		j++;
	}

	if (!fail)
	{
		m += 6;
		tell ("Passed\n");
	}

	
	sprintf (s,"%i/6 for function writeAt", m);
	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 6, s, 0);
	return m;
}

// fill the frame buffer with random letters
void Fill ()
{
	char c = 'A';
	for (int i = 0; i < MaxRow ; i++)
	{
		for (int j =0; j < MaxCol; j++)
		{ 
			plot (i,j,c);
			c += 1;
			if (c > 'Z') 
				c ='A';
		}
	}	
}

void test_showBuffer ()
{
	clearBuffer ();
	Fill ();
	showBuffer ();
}

#ifdef TEST
int main (int argc, char* argv[])
{
	FILE* jsonFile;
	int tot = 0;

	if (argc > 1 && !strcmp(argv[1], "s"))
		mustShow= 1;

	if (argc > 1 && !strcmp(argv[1], "2"))
		stage = 2;

	
	if (!Presubmission && stage == 1)
		InitGraderString ();

	tell ("\t$$$ Checking your functions, behold $$$\n");
	tell ("\t=========================================\n");
	tell ("Started ...\n");

	if (stage == 1)
	{
		
		tot += t_plot ();
		tot += t_peek ();
		tot += t_clearBuffer ();
		tot += t_writeAt();
	}

	if (stage == 2)
		test_showBuffer ();

	if (Presubmission && stage == 1)
	{
		printf ("\n---------------------------------------------------------------------\n");
		printf ("\tTotal mark = %i/14\n", tot);
		printf ("---------------------------------------------------------------------\n\n");
	}
	tell ("Finished\n");

	
	if (!Presubmission && stage ==1)  // create the results.json file
	{
		CloseGraderString ();
		//printf ("%s",JsonStr);
		jsonFile = fopen ("/autograder/results/results.json", "w");
		fprintf (jsonFile, "%s", JsonStr);
		fclose (jsonFile);
	}
	return 0;
}
#endif

