//--------------------------------------------------------------
// 
//  4190.308 Computer Architecture (Fall 2018)
//
//  Project #2: TinyFP (8-bit floating point) Representation
//
//  October 16, 2018
//
//  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
//  Systems Software & Architecture Laboratory
//  Dept. of Computer Science and Engineering
//  Seoul National University
//
//--------------------------------------------------------------

#include <stdio.h>
#include "pa2.h"

#define abs(x) x >= 0 ? x : -x
#define signbit_cal(x) x < 0 ? (1<<7) : 0


/* 
	* int -> tinyfp
	* int 0 -> +0.0
	* int which exceeds tinyfp should be inf or -inf
	* round to even
	* bias = 7
*/
tinyfp int2tinyfp(int x)
{
	short res;
	if (x == 0) {
		res = 0;
		return res;
	}
	short sign = signbit_cal(x);
	int findexp = 1 << 30;
	int i = 31;
	while (findexp & x == 0) {
		findexp = findexp >> 1;
		i--;
	} // 0000Vけけけけけけ... V = i腰属
	int x_true_exp = i - 1;
	//蒋拭 1聖 薦暗馬壱, 3bit拭 限秩陥.
	//round to even
	int x_frac = ((x << (32 - x_true_exp)) >> 26); // けけけけけ (length = i - 1) : V皐壱 5鯵
	short res_frac = x_true_exp;
	int mid = ((7 << 2) & x_frac) + 2; //11200 & けけけけけ + 2 = けけけ00 + 2 = けけけ10
	if (x_frac > mid) //けけけけけ けけけ10
		x_frac += 4;
	else if (x_frac == mid) {
		if (x_frac & 4 != 0) //G = 1
			x_frac += 4; //round to even
	}
	if (x_frac >= 32) { //re normalize
		res_frac = 0;
		res_exp++;
	}
	else
		res_frac = x_frac >> 2;
	if (res_exp < 0 && res_exp >= 15) {
		//Nan, +- inf
		res_exp = 15;
	}
	short res = sign | (res_exp << 3) | res_frac;
	return res;
}

/*
	* drop fractional pt (ex. 1.5 -> 1)
	* inf || -inf -> TMin in int
	* +NaN || -Nan -> TMin
*/
int tinyfp2int(tinyfp x)
{
	//case of Tmin -> when exp = 1111
	int res;
	short x_exp = (x << 1) >> 4;
	if (x_exp == 15)
		res = -2147483648;
	//o.w.
	else if (x_exp < 7)
		res = 0;
	else {
		short signbit = x & (1 << 7); //positive -> 0; negative -> != 0
		if (x_exp < 14) {
				res = 1;
		}
		else {
			short x_frac = x & 7;
			if (x_frac == x) {// 240
				res = 240;
			}
			else {
				res = 240;
			}
		}
		if (signbit != 0)
			res = -res;
	}
	return res;
}


tinyfp float2tinyfp(float x)
{
	if (x == 0)
		return 0;
	short sign = signbit_cal(x);
	int exp_compare = 255 << 23;
	int x_exp = (x | exp_compare) >> 23;
	int res_exp = e_exp - 127 + 7;

	int digit5 = 31 << 18;
	int x_frac = (digit5 | x) >> 18;
	int mid = ((7 << 2) & x_frac) + 2; //11200 & けけけけけ + 2 = けけけ00 + 2 = けけけ10
	if (x_frac > mid) //けけけけけ けけけ10
		x_frac += 4;
	else if (x_frac == mid) {
		if (x_frac & 4 != 0) //G = 1
			x_frac += 4; //round to even
	}
	short res_frac;
	if (x_frac >= 32) { //re normalize
		res_frac = 0;
		res_exp++;
	}
	else
		res_frac = x_frac >> 2;

	if (res_exp < 0 && res_exp >= 15) {
		//Nan, +- inf
		res_exp = 15;
	}
	short res = sign | (res_exp << 3) | res_frac;
	return res;
}

/*
* +Nan, -Nan 左糎
* +inf, -inf 左糎
* +0, -0 左糎
*/

float tinyfp2float(tinyfp x)
{
	int sign = x & (1 << 7);
	//case1. +-inf
	short inf_signed = sign | (15 << 3);
	if (x == inf_signed) 
		return (sign << 24) | (255 << 23);
	//case2. +- NaN
	short nan_signed = 15 << 3 | x;
	if (x == nan_signed)
		return (sign << 24) | (255 << 23) | x;
	//case3. general
	int x_exp = (x & (15 << 3)) >> 3;
	int x_true_exp = x_exp - 7;
	int res_exp = (x_true_exp + 127) >> 23;
	int x_frac = (x & 7) << 20;
	short res = sign | res_exp | x_frac;
	return res;
}

