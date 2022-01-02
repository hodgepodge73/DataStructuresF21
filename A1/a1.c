#include "a1.h"
#include "get_bits.h"

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


unsigned char checksum(char *string){
    unsigned char sum = 0;
    //Cycle through each char in string
    for (long i = 0; i<strlen(string); i++){
        //non editing method of locating number.
        //Maybe put an if (isalpha())
        if (isupper(string[i])){
            sum += string[i] - 'A';
            sum = sum % 26;
        }
        else if (islower(string[i])){
            sum += string[i] - 'a';
            sum = sum % 26;
        }
    }
    //printf("%d", sum);
    return sum;
}

void caesar(char *string, int rshift){
    for (long i = 0; i < strlen(string); i++){
        //the isupper ensures non uppercase are ignored
        if (isupper(string[i])){
            string[i] += rshift - 'A';
            string[i] = string[i]%26 + 'A';
        }
    }
}

void char2bits(char c, unsigned char bits[8]){
    for (int i = 0; i < 8; i++){
        bits[i] = get_bits8(i, i+1, &c);
    }
}

void bits2str(int bitno, unsigned char *bits, char *bitstr){
    for (int i = 0; i < bitno; i++){
        bitstr[i] = bits[i] + '0';
    }
    bitstr[bitno] = '\0';
}

void ushort2bits(unsigned short s, unsigned char bits[16]){
    for (int i = 0; i < 16; i++){
        bits[i] = get_bits16(i, i+1, &s);
    }
}

void short2bits(short s, unsigned char bits[16]){
    for (int i = 0; i < 16; i++){
        bits[i] = get_bits16(i, i+1, &s);
    }
}

short bits2short(char *bits){
    short sum = 0;
    //deal with neg
    sum += (bits[0]-'0') * power(2,15) * (-1);

    for (int i = 1; i < strlen(bits); i++){
        sum += (bits[i]-'0') * power(2, 15 - i); 
    }
    return sum;
}

short power(short x, short y){
    if (y == 0){
        return 1;
    }
    else if (y > 0) {
        return x * power(x, y -1);
    }
    return -1;
}

void spff(char *sign, char *exponent, char *significand, float *src){
    char master[33];
    for (int i = 0; i < 32; i++){
        master[i] = get_bits32(i, i+1, src) + '0';
    }
    master[32] = '\0';
    //parse string according to IEEE 
    //Note how to convert back: first is sign * 2 ^ (exponent value - 127) * (Mantissa)
    //Mantissa is = 1 + sum(2^(N-23)*b) or  = sum(2^(N-23)*b) where N is position of bit relative to 23
    //and b is the bit value
    fillStr(0, 1, master, sign);
    fillStr(1, 9, master, exponent);
    fillStr(9, 32, master, significand);
}

void fillStr(char from, char to, char *oldStr, char *newStr){
    for (int i = 0; i < to-from; i++){
        newStr[i] = oldStr[from+i];
    }
    newStr[to-from] = '\0';
}

