// Autograder for the Logic Module
// C Ammar Alsalka, 2020
// This is not a complete listing of the code.
// Some sections have been removed,
// and some lines have been replaced with comments.
// This file cannot be compiled.
// It is provided so that you know how
// the autograder/selfgrader tests your code
// Note: The AddTestString function simply reports the mark to Gradescope

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "uni.h"

#define JsonStrSize 5000
#define Presubmission 0


int IsAutoGradinng = 0;
int mustShow=0;
int stage= 1;
char* JsonStr;

// used to clone the universe when testing saveUniverse and loadUniverse
Star *_stars[MaxStar];		// the array of stars of the cloned universe
Pair *_pairs[MaxPair];		// the array of named pairs in the cloned universe
int _numStars;				// number of stars in the cloned universe
int _numPairs;				// number of pairs in the cloned universe


// test the pointDistance function
int t_pointDistance ()
{
	int m=2; // 2 marks
	tell ("\n*** Checking function pointDistance ***\n");
	tell ("checking 100 random cases: ");
	for (int i = 0; i < 100; i++) // checking 100 random cases
	{
		int x1 = rand() % (MaxX+1);
		int y1 = rand() % (MaxY+1);
		int x2 = rand() % (MaxX+1);
		int y2 = rand() % (MaxY+1);

		double d1 = __RpointDistance (x1, y1, x2, y2); // a reference function that correctly computes the distance
		double d2 = pointDistance (x1, y1, x2, y2);
		if (fabs (d2-d1) > 0.01)
		{
			tell ("Failed\n");
			AddTestString (0, 2, "pointDistance", 0);  // report the mark to Gradescope
			return 0;
		}
	}
	tell ("Passed\n");
	AddTestString (m, 2, "pointDistance", 0);
	return m;
}

// test the findStarByXY function
int t_findStarByXY ()
{
	int m=5; // initially 5 marks
	tell ("\n*** Checking function findStarByXY ***\n");
	tell ("Checking it for a very small universe of 3 stars\n");
	Star* s1 = (Star *) malloc (sizeof (Star));
	s1->x = 20.0;
	s1->y = 17.0;
	stars[0] = s1;
	Star* s2 = (Star *) malloc (sizeof (Star));
	s2->x = 45.00001;
	s2->y = 12.00003;
	stars[1] = s2;
	Star* s3 = (Star *) malloc (sizeof (Star));
	s3->x = 30.0002;
	s3->y = 29.0006;
	stars[2] = s3;
	numStars = 3;
	Star *p, *q;
	p = findStarByXY (20, 17 , 0.000000001);
	if (p != s1)
	{
		tell ("Failed to find a star\n");
		m = 0 ;
	}
	p = findStarByXY (45, 12 , 0.001);
	if (p != s2)
	{
		tell ("Failed to find a star\n");
		m = 0 ;
	}
	p = findStarByXY (30, 29 , 0.01);
	if (p != s3)
	{
		tell ("Failed to find a star\n");
		m = 0  ;
	}
	p = findStarByXY (30, 29 , 0.00001);
	if (p != 0)
	{
		tell ("Found a wrong star\n");
		m = 0  ;
	}
	// free dynamic vars
	stars[0] = 0 ;
	free (s1);
	stars[1] = 0 ;
	free (s2);
	stars[2] = 0 ;
	free (s3);
	numStars = 0;
	AddTestString (m, 5, "findStarByXY", 0);
	return m;
}

// test the nameStar function
int t_nameStar ()
{
	int m=5; // 5 marks
	int r;
	int failed = 0;
	tell ("\n*** Checking function nameStar ***\n");
	Star * s = (Star *) malloc (sizeof (Star));
	r = nameStar (s, "Ammar" , "Alsalka");
	if (r == -99)
	{
		tell ("Not implemented, cannot continue\n");
		AddTestString (0, 5, "nameStar", 0);
		return 0;
	}
	tell ("#Checking it can handle invalid parameters (null parameters):");
	r = nameStar (0, "Ammar" , "Alsalka");
	if (r != 0) failed = 1;
	r = nameStar (s, 0 , "Alsalka");
	if (r != 0) failed = 1;
	r = nameStar (s, "Ammar" , 0);
	if (r != 0) failed = 1;
	if (failed)
	{
		tell ("Failed, -1 mark\n");
		m = m - 1;
	}
	else
		tell ("Passed\n");
	tell ("#Checking it can name a star and return proper code\n");
	r = nameStar (s, "Ammar" , "Alsalka");
	if (r != 1) m = m -1;
	if (s->named != 1) m = m -1;
	if (strcmp (s->name , "Ammar Alsalka")) m = m -1;
	tell ("#Checking it does not crash with long names\n");
	r = nameStar (s, "Doctor Mohammad Ammar" , "Alsalka, FHEA");
	if (r != 0) m = m -1;
	if (m == 5) tell ("Passed\n");
	free (s);
	AddTestString (m, 5, "nameStar", 0);
	return m;
}


// test the bigBang function
int t_bigBang ()
{
	int m=12;
	int failed = 0;
	int fxy = 0;
	int fid = 0;
	int fflag = 0;
	int r;
	char s[512];
	tell ("\n*** Checking function bigBang ***\n");
	r = bigBang (10);
	if (r == -99)
	{
		tell ("bigBang not implemented. Cannot continue.");
		AddTestString (0, 12, "bigBang", 0);
		return 0;
	}
	tell ("#Checking it can handle invalid parameters:");
	r = bigBang (0);
	if (r != 0) failed = 1;
	r = bigBang (1892);
	if (r != 0) failed = 1;
	if (failed)
	{
		tell ("Failed, 1 mark deducted.\n");
		m--;
	}
	else
		tell ("Passed\n");
	// checking it can create universes correctly
	time_t t;
	srand((unsigned) time(&t));
	// repeat this test 10 times
	tell ("#Checking bigBang can create stars correctly:\n");
	for (int t= 0; t < 10 ; t++)
	{
		int num_stars = 20 + (rand () % 100) + (rand() % 15) * 100;
		sprintf (s, "test no. %i, checking bigBang can create %i stars\n", t, num_stars);
		tell (s);
		r  = bigBang (num_stars);
		if (r == 0)
		{
			tell ("\nFailed: function returned 0 for a valid number of stars. Testing of this function will not continue\n");
			AddTestString (0, 12, "bigBang", 0);
			return 0;

		}
		if (numStars != num_stars)
		{
			tell ("\nFailed: invalid number of stars. Testing of this function will not continue\n");
			AddTestString (0, 12, "bigBang", 0);
			return 0;
		}
		// check stars
		double tolerance = 0.00000001;
		for (int i = 0; i < numStars ; i++)
		{
			if (stars[i] == 0) //  null pointer in stars array
			{
				tell ("\nFailed: null pointer in stars array. Testing of this function will not continue\n");
				AddTestString (0, 12, "bigBang", 0);
				return 0;
			}
			for (int j = 0; j < i ; j++)
			{
				// two stars in same location
				if ( (fabs(stars[j]->x - stars[i]->x) < tolerance) && (fabs(stars[j]->y -stars[i]->y) < tolerance ))
				{
					if (!fxy)
					{
						tell ("Failed: found two stars in same location.");
						tell (" 4 marks will be deducted\n");
						m = m -4;
						fxy = 1;
					}
				}
				// two stars have same id
				if (stars [i]->id == stars[j]->id)
				{
					if (!fid)
					{
						tell ("Failed: found two stars with identical identifiers.");
						tell (" 2 marks will be deducted\n");
						m = m -2;
						fid = 1;
					}
				}
			}
			// named flag not initialised
			if (stars [i]->named != 0)  //
			{
				if (!fflag)
				{
					tell ("Failed: some fields were not initialised.");
					tell (" 2 mark will be deducted\n");
					m = m -2;
					fflag = 1;
				}

			}
		}
	}

	// checking bigBang is really random
	Star *prev[MaxStar];
	int num_identical=0;
	fflag = 0;
	tell ("#Checking bigBang creates stars with random positions\n");
	for (int t= 0; t < 10 ; t++)
	{
		num_identical = 0;
		int num_stars = 1000;
		sprintf (s, "iteration %i, 1000 stars will be created with bigBang\n", t);
		tell (s);
		r  = bigBang (num_stars);
		if (r == 0)
		{
			tell ("bigBang failed. Cannot continue.");
			AddTestString (0, 12, "bigBang", 0);
			return 0;
		}
		if (numStars != num_stars)
		{
			tell ("\nFailed: wrong no of stars. Testing of this function will not continue\n");
			AddTestString (0, 12, "bigBang", 0);
			return 0;
		}
		// check stars
		double tolerance = 0.00000001;
		for (int i = 0; i < numStars ; i++)
		{
			if (stars[i] == 0) //  null pointer in stars array
			{
				tell ("\nFailed: null pointer in stars array. Testing of this function will not continue\n");
				AddTestString (0, 12, "bigBang", 0);
				return 0;
			}
		}
		if (t > 0) // if not first iteration
		{
				for (int m = 0; m <numStars ; m++)
					if (fabs(stars[m]->x - prev[m]->x) < tolerance && fabs(stars[m]->y - prev[m]->y) < tolerance)
						num_identical++;
				if (num_identical > 50 ) // more than 50/1000 = 5% stars have same location
				{
					if (!fflag)
					{
						tell ("Failed: more than 50 of stars in same locations.");
						tell (" 3 marks will be deducted\n");
						m = m -3 ;
						fflag = 1;
					}
				}
				// free old array
				for (int m = 0; m <numStars ; m++)
					free (prev[m]);
		}

		if (t < 9) // don't copy last iteration
		{
				// copy this universe to compare in next iteration
				for (int k = 0; k < numStars ; k++)
				{
					prev[k] = (Star *) malloc (sizeof (Star));
					prev[k]->x = stars[k]->x;
					prev[k]->y = stars[k]->y;
				}
		}
	}
	if (m == 12) tell ("Passed\n");
	AddTestString (m, 12, "bigBang", 0);
	return m;
}


// test the closestPair function
int t_closestPair ()
{
	int m=12;
	char s[256];
	Pair *p;
	Pair *q;
	tell ("\n*** Checking function closestPair ***\n");
	tell ("**Note: if your bigBang function is faulty, this function may not pass the tests.**\n");
	tell ("**If you have not implemented bigBang, please leave the 'return -99' statement inside the function's body.\n");
	tell ("  Calling your bigBang function (with n_stars = 10) to see if it is implemented.\n");
	int r = bigBang (10);
	if (r == -99)
	{
		tell ("\nbigBang returned -99 (not implemented). Cannot continue.\n");
		AddTestString (0, 12, "closestPair", 0);
		return 0;
	}
	else
	{
		sprintf (s, "  bigBang returned %i (implemented), checking of closestPair will proceed ...\n", r);
		tell (s);
	}
	time_t t;
	srand((unsigned) time(&t));
	// check for a universe of 1 star only
	tell ("#Checking it for a universe containing 1 star only\n");
	tell ("  Calling your bigBang function with n_stars = 1\n");
	r = bigBang (1);
	if (r == 0)
	{
		tell ("\nbigBang returned 0. Cannot continue.");
		AddTestString (0, 12, "closestPair", 0);
		return 0;
	}
	tell ("  Calling your closestPair\n");
	q = closestPair ();
	if (q!=0)
	{
		tell ("\nFailed: closestPair should return 0,");
		tell (" 1 mark will be deducted\n");
		m = m -1 ;
	}
	for (int i = 2; i <= 3 ; i++)
	{
		sprintf (s, "#Checking it for a universe containing %i stars\n", i);
		tell (s);
		sprintf (s, "  Calling your bigBang function with n_stars = %i stars\n", i);
		tell (s);
		r = bigBang (i);
		if (r == 0)
		{
			tell ("\nbigBang returned 0. Cannot continue.");
			AddTestString (0, 12, "closestPair", 0);
			return 0;
		}
		tell ("  Calling a reference version of closestPair (not yours)\n");
		p = __RclosestPair ();
		if (p == 0)
		{
			tell ("\nFailed: could not find a closest pair. Check your bigBang function. Testing of closestPair will not continue\n");
			AddTestString (0, 12, "closestPair", 0);
			return 0;
		}
		tell ("  Calling your closestPair\n");
		q = closestPair ();
		if (q == 0 || q->h == 0 || q->w == 0)
		{
			tell ("\nFailed: your function returned 0 (null), or null value in h or w. Testing of this function will not continue\n");
			AddTestString (0, 12, "closestPair", 0);
			return 0;
		}
		if ((p->h != q->h && p->w != q->w) && (p->h != q->w && p->w != q->h))
		{
			tell ("\nFailed: your closestPair returned a different pair (error in h or w or both)\n");
			tell (" 1 mark will be deducted\n");
			m = m -1 ;
		}
	}
	// check for large universes
	for (int u= 0; u < 9 ; u++)
	{
		int num_stars = rand () % 100 + (rand() % 10) * 10;
		sprintf (s, "#Checking it for a universe of %i stars (by comparing your closest pair distance with that of a reference function)...\n", num_stars);
		tell (s);
		//sprintf (s, " Calling your bigBang function with n_stars = %i stars.\n", num_stars);
		//tell (s);
		r = bigBang (num_stars);
		if (r == 0)
		{
			tell ("\nyour bigBang returned 0. Cannot continue.\n");
			AddTestString (0, 12, "closestPair", 0);
			return 0;
		}

		for (int t = 0; t < 9 ; t++)
		{
			//tell ("  Calling a reference version of closestPair (not yours)\n");
			p = __RclosestPair ();
			//tell ("  Calling your closestPair\n");
			q = closestPair ();
			if (q == 0 || p == 0) continue;
			if (q == 0 || q->h == 0 || q->w == 0)
			{
				tell ("\nFailed: returned null, or null in h or w. Testing of this function will not continue\n");
				AddTestString (0, 12, "closestPair", 0);
				return 0;
			}
			//tell ("  Comparing distance between closest pair with that of reference function\n");
			if ( fabs(__RpointDistance (p->h->x, p->h->y, p->w->x , p->w->y) - __RpointDistance (q->h->x, q->h->y, q->w->x , q->w->y)) > 0.001  )
			{
				tell ("Failed: closestPair returned wrong pair");
				tell (" 1 mark will be deducted\n");
				m = m -1 ;
				if (m == 0)
				{
					tell ("\nFailed: too many errors. Testing of this function will not continue\n");
					AddTestString (0, 12, "closestPair", 0);
					return 0;
				}
			}
			__RnameStar (q->h, "hf", "hs"); // name the pair so that it cannot be found again
			__RnameStar (q->w, "wf", "ws"); // using a reference nameStar function
		}
	}
	if (m == 12) tell ("Passed\n");
	AddTestString (m, 12, "closestPair", 0);
	return m;
}

// test the findPairByName function
int t_findPairByName ()
{
	int m=4;
	int r;
	int failed = 0;
	Pair *p;
	char s[256];
	char v[256];
	tell ("\n*** Checking function findPairByName ***\n");
	tell ("** Note: if bigBang is faulty, this function may not pass the tests**\n");
	tell ("**If you have not implemented bigBang, please leave the 'return -99' statement inside the function's body.\n");
	tell ("  Calling your bigBang to see if it has been implemented\n");
	r = bigBang (10);
	if (r == -99)
	{
		tell ("bigBang not implemented. Cannot continue.");
		AddTestString (0, 4, "findPairByName", 0);
		return 0;
	}
	int num_stars = 100;
	tell ("  Calling your bigBang to create a universe with 100 stars\n");
	r  = bigBang (num_stars);
	if (r == 0)
	{
		tell ("bigBang failed, check your bigBang function. Cannot continue.");
		AddTestString (0, 4, "findPairByName", 0);
		return 0;
	}
	tell ("#Checking it can find pairs:\n");
	tell ("  creating 30 pairs using reference functions (not yours)...\n");
	for (int t = 0; t < 30 ; t++) // create 30 pairs
	{
		p = __RclosestPair ();
		if (p == 0)
		{
			tell ("Failed to find a pair to name. Check your bigBang function. Cannot continue.");
			AddTestString (0, 4, "findPairByName", 0);
			return 0;
		}
		sprintf (s, "Mr");
		sprintf (v, "Bean %i", t);
		__RnameStar (p->h, s, v);
		sprintf (s, "Irma");
		sprintf (v, "Gobb %i", t);
		__RnameStar (p->w, s, v);
		pairs[numPairs++] = p;
	}
	tell ("#trying to find pairs through husband's (h) name using your findPairByName function\n");
	for (int t = 0; t < 30 ; t++) // find them by husband name
	{
		sprintf (v, "Mr Bean %i", t);
		Pair* p = findPairByName (v);
		if (p == 0)
		{
			tell ("Failed to find a pair\n");
			AddTestString (0, 4, "findPairByName", 0);
			return 0;
		}
	}
	tell ("Passed\n");
	tell ("#trying to find pairs through wife's (w) name using your findPairByName function\n");
	for (int t = 0; t < 30 ; t++) // find them by wife name
	{
		sprintf (v, "Irma Gobb %i", t);
		Pair* p = findPairByName (v);
		if (p == 0)
		{
			tell ("Failed\n");
			AddTestString (0, 4, "findPairByName", 0);
			return 0;
		}
	}
	tell ("Passed\n");
	if (m == 4) tell ("Function Passed\n");
	AddTestString (m, 4, "findPairByName", 0);
	return m;
}

// used by cloneUniverse to clone a star
Star* cloneStar (Star *s)
{
	if (s == 0)
	{
		tell ("Error while trying to clone a star, null pointer passed to function\n");
		return 0;
	}
	Star * p = (Star *) malloc (sizeof (Star));
	p->id = s->id;
	strcpy (p->name, s->name);
	p->named = s-> named;
	p->x = s-> x;
	p-> y = s->y;
	return p;
}


// return 1 if p and s are the same star
int sameStar (Star *p, Star *s)
{
	if (p == 0 || s == 0)
	{
		tell ("Error while trying to compare two stars, one of the stars' pointers is null\n");
		return -5;
	}
	if (p->id != s->id)
	{
		tell ("Error while trying to compare two stars, stars have different id\n");
		return 0;
	}
	if (strcmp (p->name, s->name))
	{
		tell ("Error while trying to compare two stars, stars have different names\n");
		return -1;
	}
	if (p->named != s-> named)
	{
		tell ("Error while trying to compare two stars, stars have different values for the 'named' flag\n");
		return -2;
	}
	if (fabs (p->x - s-> x) > 0.000000001)
	{
		tell ("Error while trying to compare two stars, stars have different values for x\n");
		return -3 ;
	}
	if (fabs (p->y - s-> y) > 0.000000001)
	{
		tell ("Error while trying to compare two stars, stars have different values for y\n");
		return -4 ;
	}
	return 1;
}

// return 1 if two pairs are identical
int samePair (Pair* p, Pair *q)
{
	if (p == 0 || q == 0)
	{
		tell ("Error while trying to compare two pairs, one of the pairs' pointers is null\n");
		return -99;
	}
	if (fabs (q->d - p->d) > 0.000000001)
		return 0;
	if (q->h == 0 || p->h == 0)
	{
		tell ("Error while trying to compare two pairs, h is null in one of the pairs\n");
		return -99;
	}
	if (q->h->id != p->h->id)
	{
		tell ("Error while trying to compare two pairs, h stars have different id\n");
		return -1;
	}
	if (q->w == 0 || p->w == 0)
	{
		tell ("Error while trying to compare two pairs, w is null in one of the pairs\n");
		return -99;
	}
	if (q->w->id != p->w->id)
	{
		tell ("Error while trying to compare two pairs, w stars have different id\n");
		return -2;
	}
	return 1;
}

// used by cloneUniverse
Star* __findStarById (int id)
{
	for (int i = 0; i < _numStars ; i++)
		if (_stars[i]->id == id)
			return _stars[i];
	return 0;

}

// make a deep copy of the universe in memory so that it can later be compared
// with that loaded from file
int cloneUniverse ()
{
	for (int i = 0; i < numStars ; i++) // clone the stars
	{
		if (stars[i] == 0)
		{
			tell ("Fatal error while cloning stars, one of the elements of the stars array is = 0\n");
			return 0;
		}
		Star *cs = cloneStar (stars[i]);
		if (cs == 0)
		{
			return 0;
		}
		_stars[i] = cs;
	}
	_numStars = numStars;

	for (int i = 0; i < numPairs ; i++) // clone the pairs
	{
		if (pairs[i] == 0)
		{
			tell ("Fatal error while cloning pairs, one of the elements of the pairs array is = 0\n");
			return 0;
		}
		Star* hfield = pairs[i]->h;
		if (hfield == 0)
		{
			tell ("Fatal error while cloning pairs, h field = 0\n");
			return 0;
		}
		Star* h = __findStarById (hfield->id);
		if (h == 0)
		{
			tell ("Fatal error while cloning pairs, could not find the h star through its id\n");
			return 0;
		}
		Star* wfield = pairs[i]->w;
		if (wfield == 0)
		{
			tell ("Fatal error while cloning pairs, w field = 0\n");
			return 0;
		}
		Star* w = __findStarById (wfield->id);
		if (w == 0)
		{
			tell ("Fatal error while cloning pairs, could not find the w star through its id\n");
			return 0;
		}
		Pair *q = (Pair *) malloc (sizeof (Pair));
		q->d = pairs[i]->d;
		q->h = h;
		q->w = w;
		_pairs[i] = q;
	}
	_numPairs = numPairs;
	return 1;
}


int sameUniverse ()
{
	int r;
	char s[256];
	if (_numStars != numStars)
	{
		tell ("Cloned universe has different number of stars from restored universe\n");
		return 0;
	}
	for (int i = 0; i < numStars ; i++) // check the stars
	{
		r = sameStar (_stars[i] , stars[i]);
		if (r != 1 )
		{
			sprintf (s, "Wrong star data, code %i\n", r);
			tell (s);
			return 0;
		}
	}

	if (_numPairs != numPairs)
	{
		tell ("Cloned universe has different number of pairs from restored universe\n");
		return 0;
	}
	for (int i = 0; i < numPairs ; i++) // check the pairs
	{
		r = samePair (_pairs[i] , pairs[i]);
		if ( r != 1 )
		{
			sprintf (s, "Wrong pair data, code %i\n", r);
			tell (s);
			return 0;
		}
	}
	return 1;
}

// test saveUniverse and loadUniverse functions
int t_saveLoadUniverse ()
{
	int m=12; // 12 marks for both functions
	int r;
	int failed = 0;
	Pair *p;
	char s[256];
	char v[256];
	tell ("\n*** Checking the two functions saveUniverse and loadUniverse ***\n");
	tell ("**Note: if bigBang is faulty, this function may not pass the tests**\n");
	tell ("**If you have not implemented bigBang, please leave the 'return -99' statement inside the function's body.\n");
	r = bigBang (10);
	if (r == -99)
	{
		tell ("bigBang not implemented. Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Calling your bigBang function to create a new universe with 100 stars...\n");
	r = bigBang (100);
	if (r == 0)
	{
		tell ("bigBang failed. Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Naming 10 pairs using tested versions of closestPair and nameStar functions (not yours)...\n");
	for (int t = 0; t < 10 ; t++)
	{
		p = __RclosestPair ();
		sprintf (s, "Mr");
		sprintf (v, "Bean %i", t);
		__RnameStar (p->h, s, v);
		sprintf (s, "Irma");
		sprintf (v, "Gobb %i", t);
		__RnameStar (p->w, s, v);
		pairs[numPairs++] = p;
	}
	tell ("  Cloning your universe in memory ...\n");
	r = cloneUniverse ();
	if (r == 0)
	{
		tell ("\nCloning failed (check your other functions especially bigBang). Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Calling your saveUniverse function:\n");
	r = saveUniverse ();
	if (r == 0 || r == -99)
	{
		tell ("\nsaveUniverse failed or not implemented. Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Calling your bigBang function to create another universe overwriting existing one...\n");
	r = bigBang (30);
	if (r == 0)
	{
		tell ("\nbigBang failed. Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Naming 6 pairs using tested versions of closestPair and nameStar functions (not yours)...\n");
	for (int t = 0; t < 6 ; t++)
	{
		p = __RclosestPair ();
		sprintf (s, "Mr");
		sprintf (v, "Alalka %i", t);
		__RnameStar (p->h, s, v);
		sprintf (s, "Mrs");
		sprintf (v, "Alalka %i", t);
		__RnameStar (p->w, s, v);
		pairs[numPairs++] = p;
	}

	tell ("  Calling your loadUniverse function:\n");
	r  = loadUniverse ();
	if (r == 0 || r == -99)
	{
		tell ("\nloadUniverse failed or not implemented. Testing will not continue\n");
		AddTestString (0, 12, "saveUniverse and loadUniverse", 1);
		return 0;
	}
	tell ("  Checking universe was restored correctly: ");
	if (!sameUniverse())
	{
		tell ("\nFailed\n");
		m = 0;
	}
	else
		tell ("\nPassed\n");
	AddTestString (m, 12, "saveUniverse and loadUniverse", 1);
	return m;
}

#ifdef TEST
int main (int argc, char* argv[])
{
	FILE* jsonFile;
	int tot = 0;

	if (!Presubmission && stage == 1)
		InitGraderString ();
	if (Presubmission)
	{
		char answer;
		tell ("****************** Disclaimer ********************\n\n");
		tell ("You are provided with this copy of the autograder\n");
		tell ("to help you test your program on your machine.\n");
		tell ("However, please note that\n");
		tell ("this grader may not catch every bug in your code.\n");
		tell ("Even if you score full marks in all functions,\n");
		tell ("your code may still contain bugs that don't cause runtime\n");
		tell ("errors on your machine, but will cause your program to\n");
		tell ("crash on Gradescope.\n");
		tell ("YOUR MARK IS DETERMINED BY WHAT YOU SEE ON GRADESCOPE.\n");
		tell ("Hence, if your program crashes on Gradescope,\n");
		tell ("you should fix it and submit again.\n");
		tell ("Enter y or Y to continue with this grader,\n");
		tell ("or any other letter to quit now\n");
		scanf (" %c", &answer);
		if (answer != 'y' && answer != 'Y')
			exit (0);
	}

	tell ("\t$$$ Checking your functions, behold $$$\n");
	tell ("\t=========================================\n");
	tell ("Started ...\n");

	if (stage == 1)
	{
		tot += t_pointDistance() ;
		tot += t_findStarByXY ();
		tot += t_nameStar ();
		tot += t_bigBang ();
		tot += t_closestPair ();
		tot += t_findPairByName ();
		tot += t_saveLoadUniverse ();
	}

	if (Presubmission && stage == 1)
	{
		printf ("\n---------------------------------------------------------------------\n");
		printf ("\tTotal mark = %i/52\n", tot);
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
