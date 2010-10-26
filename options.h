//////////////////////////////////////////////////////////////////////////////
//
// options.h, 09/11/00, Ilja Friedel
//
//////////////////////////////////////////////////////////////////////////////
//
// This file contains options to change the behavior of the program package
// libseq.
//
//////////////////////////////////////////////////////////////////////////////
//
// Status: Warnings to do, return_no_nulls to do
//
//////////////////////////////////////////////////////////////////////////////

#ifndef OPTIONS_INCLUDED
#define OPTIONS_INCLUDED

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// global options - affect all files
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//#define DEBUG_INTERNAL
// makes several additional runtime tests for checking own integrity
// status:  ok
// default: off
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define DEBUG_EXTERNAL
// makes additional runtime tests checking the integrity of arguments
// passed to functions
// status:  ok
// default: on for development, off for final runs
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//#define DESTRUCTOR
// prints the name of every called destructor
// status:  check
// default: off
//////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////////
#define RETURN_NO_NULLS
#define EPSILON 1e-20
// if defined, a sequence will never return a 0.0, but a small EPSILON
// instead 
// status:  *** to do ***
// default: RETURN_NO_NULLS off, EPSILON 1e-20
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define WARNINGS_INTERNAL
//#define WARNINGS_EXTERNAL
// status: gives some information
// default: WARNINGS_EXTERNAL on
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define USE_DRAND48 
// default random number generator
// status: no other options right now, see digit_gen.h
// default: on
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Permutation.h, Permutation.C  - no options
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Ring.h, Ring.C - no options
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Polynomial.h, Polynomial.C
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define MAX_POLY_LEN 128
// handles the maximum degree of a polynomial
// in case of an overflow (multiplication) an error is reported
// status: ok
// default: 128
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define TABLE_LENGTH 1000
// This constant sets the length of the table for the sieve. The sieve
// is used for finding irreducible, monic polynomials. 
// TABLE_LENGTH depends on the dimension of the Niederreiter sequence.
// For small dimensions the creation of a C_matrix is faster with smaller
// TABLE_LENGTH
// status: ok
// default: 1000 
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// C_matrix.h, C_matrix.C
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// VectorRing.h, VectorMatrix.h - no options
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// DigitalSequence.h, DigitalSequence*.C
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define MAX_BUFFER_LEN 100
// Maximum length (in vectors) of the buffer for the digits of the
// digital sequence. Used in *medium_base.C and *advanced.C
// status: ok
// default: 100
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// RandomizedTSSequence.h, RandomizedTSSequence*.C
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//#define RANDOMIZED_QUICKSORT
// If defined, the quicksort will be randomized. This might be important
// sometimes (using presorted sequences), but is normaly a waste of time.
// status: ok
// default: off
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//#define RTSS_TEST
// An additional debugging level forcreating randomized sequences
// status: internal
// default: off
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// LatinSupercube.h, LatinSupercube.C - no options
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#endif