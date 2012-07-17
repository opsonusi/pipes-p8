// file: tools.h ---------------------------------------------------- 
// header file for the C++ tools library.   
// modified September 2011

#pragma once
// -------------------------------------------------------------------
// Local definitions and portability code.
// Please enter your own system, name, class, and printer stream name.
// -------------------------------------------------------------------
#define NAME    "Opeyemi Sonusi"
#define CLASS   "CS 647"

#include <stdio.h>      // for NULL 
#include <stdlib.h>     // for malloc() and calloc()
#include <string.h>     // The C string library 
#include <math.h>
#include <time.h>		// for time_t, time() and ctime()
#include <ctype.h>      // for isspace() and isdigit() 
#include <limits.h>     // for INT_MAX 
#include <float.h>      // for DOUBLE_MAX, etc. 
#include <stdarg.h>     // for functions with variable # of arguments
#include <vector>       // for growing arrays

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm> // for sort
#include <string>	 // for strings that grow as needed
#include <iostream>	 // for screen and keyboard IO

using namespace std;

// -------------------------------------------------------------------
// Macros to make more convenient use of standard library functions.
// -------------------------------------------------------------------
#define DUMPp(p) "\n"<<hex<<"   " #p " @ "<<(unsigned)&p<<"   value = "<<(unsigned)p<<"   " #p " --> "<<dec<<*p
#define DUMPv(k) "\n"<<hex<<"   " #k " @ "<<(unsigned)&k<<"   value = "<<dec<<k

// -------------------------------------------------------------------
// Portable definitions; these require user to #define name of local system.
// -------------------------------------------------------------------
void    clearscreen( void );
void    bye( void );

// -------------------------------------------------------------------
// Routine screen and process management.-----------------------------
// -------------------------------------------------------------------
void     fbanner( ostream& fout );
#define  banner()  fbanner( cout )
void     delay( int );
void     hold( void );
void     say( const char* format, ... );

// -------------------------------------------------------------------
// I/O Extension. ---------------------------------------------------- 
// -------------------------------------------------------------------
istream&  flush( istream& is );   // Used in cin >>x >>flush;

// -------------------------------------------------------------------
// Error handling. ---------------------------------------------------
// -------------------------------------------------------------------
void    fatal( const char* format, ... );

// -------------------------------------------------------------------
// Time and date. ----------------------------------------------------
// -------------------------------------------------------------------
void   when ( char* date, char* hour );
char*  today( char* date );
char*  oclock( char* hour );

