#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Student Name: Ethan Hodge
Student ID: 1124633
Due Date: 21 09 2021
Course: CIS*2520 Instructor: Kremer
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/


unsigned char checksum(char *string);

void caesar(char *string, int rshift);

void char2bits(char c, unsigned char bits[8]);

void bits2str(int bitno, unsigned char *bits, char *bitstr);

void ushort2bits(unsigned short s, unsigned char bits[16]);

void short2bits(short s, unsigned char bits[16]);

short bits2short(char *bits);

//helper function used to calculate short exponents similar to pow(double, double)
short power(short x, short y);

//helper function to fill in string from old to newStr
void fillStr(char from, char to, char *oldStr, char *newStr);

//bonus
void spff(char *sign, char *exponent, char *significand, float *src);

