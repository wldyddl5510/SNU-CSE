//--------------------------------------------------------------
// 
//  4190.308 Computer Architecture (Fall 2018)
//
//  Project #1: 64-bit Arithmetic using 32-bit integers
//
//  September 18, 2018
//
//  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
//  Systems Software & Architecture Laboratory
//  Dept. of Computer Science and Engineering
//  Seoul National University
//
//--------------------------------------------------------------

#include <stdio.h>
#include "pa1.h"

#define max(a,b) {a > b ? a : b}
#define min(a,b) {a > b ? b : a}

// NOTE!!!!!
// You should use only 32-bit integer operations inside Uadd64(), Usub64(), 
// and Umul64() functions. 


// Uadd64() implements the addition of two 64-bit unsigned integers.
// Assume that A and B are the 64-bit unsigned integer represented by
// a and b, respectively. In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A + B), respectively.

HL64 Uadd64 (HL64 a, HL64 b)
{
	HL64 x; //result
	x.hi = 0;
	unsigned int low_sum = a.lo + b.lo;
	x.lo = low_sum;
	unsigned int low_max = max(a.lo, b.lo);
	if(low_sum <= low_max) {
		x.hi++;
	}
	unsigned int high_sum = a.hi + b.hi;
	x.hi = x.hi + high_sum;
	return x;
}

// Usub64() implements the subtraction between two 64-bit unsigned integers.
// Assume that A and B are the 64-bit unsigned integer represented by
// a and b, respectively. In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A - B), respectively.

HL64 Usub64 (HL64 a, HL64 b)
{
	HL64 x; //result
	x.hi = 0;
	//- whole b. how? use bitwise not
	HL64 c; //unsigned ver. of -b
	if(b.lo != 0) {
		c.hi = ~b.hi;
		c.lo = (~b.lo) + 1;
	}
	else {
		c.lo = b.lo;
		c.hi = (~b.hi) + 1;
	}
	unsigned int low_sum = a.lo + c.lo;
	x.lo = low_sum;
	unsigned int low_max = max(a.lo, c.lo);
	if(low_sum < low_max) { //overflow in low pt.
		x.hi++;
	}
	x.hi = x.hi + a.hi + c.hi;
	return x;
}

// Usub64() implements the multiplication of two 64-bit unsigned integers.
// Assume that a' and b' are the 64-bit unsigned integer represented by
// a and b, respectively.  In the following example, x.hi and x.lo should
// have the upper and lower 32 bits of (A * B), respectively.

HL64 Umul64 (HL64 a, HL64 b)
{
	HL64 x;
	x.lo = 0;
	x.hi = 0;
	HL64 temp; // temp = (2^i)*larger ;
	HL64 larger;
	HL64 smaller;
	unsigned int choose_larger = max(a.hi, b.hi);
	if(choose_larger == a.hi) {
		larger = a;
		smaller = b;
	}
	else {
		larger = b;
		smaller = a;
	}
	//decompose smaller to series of 2^r
	unsigned int bit_compare = 1; // for decomposition
	
	for(int i = 0; i < 32 ; i++) { // decompose smaller by bitwise -> low pt.
		if((smaller.lo & bit_compare) == 1) {
			unsigned int before_shift_low = larger.lo;
			temp.lo = (larger.lo << i);
			temp.hi = ((larger.hi << i) | (before_shift_low >> (32 - i)));
		}
		x = Uadd64(x, temp); // result = previous result + (2^i * larger)
		bit_compare << 1; //loop condition
	}
	bit_compare = 1; //reset
	for(int i = 0; i < 32 ; i++) { // decompose smaller by bitwise -> hi pt.
		if((smaller.hi & bit_compare) == 1) {
			unsigned int before_shift_low = larger.lo;
			temp.lo = (larger.lo << (i + 32));
			temp.hi = ((larger.hi << (i + 32)) | (before_shift_low >> i));
		}
		x = Uadd64(x, temp); // result = previous result + (2^i * larger)
		bit_compare << 1; //loop condition
	}
	return x;
}




