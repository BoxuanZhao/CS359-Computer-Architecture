/* 
 *Lab of Computer Architecture 
 * 
 * Zhengtian Xu  5140309178
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
 

int bitAnd(int x, int y) {
/*
 * According to the De Morgan's laws, 
 * the operation And equals to the combination
 * of the operation Or and Not
 */
	return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */


int getByte(int x, int n) {
/*
 * The number x has 4 bytes, so 
 * I shift n to the left by three 
 * bits to find the starting bit 
 * of the byte. And then shift x to
 * the right by the number above and 
 * extract the byte.
 */
	int shiftNumber;
	int newx;

	shiftNumber = n << 3;
	newx = x >> shiftNumber;
	return newx & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/*
 * The most left bit represents the sign
 * of x, so I drop the sign and
 * do the following operation.
 */ 
	/* Make the left n number is 1*/
	int number;

	number = (1 << 31) >> n;
	/* I can't use minus operation, so first right shift n bits and then 
	   left shift one bit */ 
	number = number << 1;
	/* Use Not function for number because we want to maintain the last (32-n) bits */
	number = ~number;
	/* Shift x to the right by n bits without the sign bit */
	return (x >> n) & number;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/* Split it in 4 numbers a group repeatedly and 
 * calculate the number of 1. Use the 
 * method which called Divide and Conquer.
 * Then I shrink the length using the same 
 * method.
 */
	/* Construct the constants. */
    int result;
    int const1;
    int const2;
    int const3;
    int const4;
    int const5;

    /* 0x55555555 */
    const1 = (0x55) | (0x55 << 8);
    const1 = const1 | (const1 << 16);

    /* 0x33333333 */
    const2 = (0x33) | (0x33 << 8);
    const2 = const2 | (const2 << 16);

    /* 0x0f0f0f0f */
    const3 = (0x0f) | (0x0f << 8);
    const3 = const3 | (const3 << 16);

    /* 0x00ff00ff */
    const4 = (0xff) | (0xff << 16);

    /* 0x0000ffff */
    const5 = (0xff) | (0xff << 8);


    /* add every two bits */
    result=(x & const1)+((x >> 1) & const1);

    /* add every four bits */
    result=(result & const2) + ((result >> 2) & const2);

    /* add every eight bits */
    result=(result+(result>>4))&const3;

    /* add every sixteen bits */
    result=(result + (result >> 8)) & const4;

    /* add every thirty two bits */
    result=(result + (result >> 16)) & const5;
    return result;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*
 * The function '!' represents that if the number is
 * 0, then return 1, or return 0.
 */
	int negative;
	int signDifference;
	int result;
	/* First I find the negative number of x using two complement */
	negative = ~x + 1;
	/* If the sign bit is different, then return 0. Or return 1 */
	signDifference = (negative | x) >> 31;
	result = ~signDifference;
	/* To make the return number is one bit. */
	return (result & 0x01);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* The minimum two's complement integer is 11111111... */
	return (0x01 << 31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int fitsBits(int x, int n) {
/* 
 * By shifting bits left (n-1) bits to see whether the number left is 
 * all 0s or 1s can know whether this figure is an n-bit twos complement.
 */
	int shift;
	int newx;

	/* Shift (n-1) bits which is n + 1 - 2 */ 
	shift = n + 0x01 + (~0x01);
	/* Shift x to the left by 'shift' bits and shift back again to see if the number left is all 0s or 1s */
	newx = (x >> shift);
 	return (!newx) ^ (!(~newx)); 
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
/*
 * Right shift is division by 2^n, 
 * but add bias=(1<<n)+(-1) if x<0 
 */
	int sign;
	int m;
	int low;

	/* Check the sign bit to see if x is negative */
	sign =!!(x >> 31);
	m = (1 << n) + ~0;
	low = m & x;
	return (x >> n) + ((!!low) & sign);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* return the two's complement number of x */
	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int sign;
	int zero;
	/* Check whether the sign bit is 0 but drop the number 0 */
	sign = !!(x >> 31);
	/* If x = 0, then zero = 1 */
	zero = !x;
	/* Correct answer is sign = 0 and zero = 0 */
	return !(sign | zero);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
 
int isLessOrEqual(int x, int y) {
	int signx;
	int signy;
	int same;
	int sameSign;
	int notSameSign;

	signx = !!(x >> 31);
	signy = !!(y >> 31);
	/* Check whether x and y are the same sign*/
	same = !(signx ^ signy);
	/* If same, then check (x-y)'s sign. Otherwise if sign of x represents positive, return 0, or return 1 */
	sameSign = ((x + ~y) >> 31);
	notSameSign = signx;
	return (same & sameSign) | ((!same) & notSameSign);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int flag;
	int shift1;
	int shift2;
	int shift3;
	int shift4;
	int shift5;

	/* Whether x's left 16 bits has 1 */
	flag = !!(x >> 16);
	/* If has, then shift x to the right by 16 bits */
	shift1 = flag << 4;
	x = x >> shift1;

	/* Whether x's left 8 bits has 1 */
	flag = !!(x >> 8);
	/* If has, then shift x to the right by 8 bits */
	shift2 = flag << 3;
	x = x >> shift2;

	/* Whether x's left 4 bits has 1 */
	flag = !!(x >> 4);
	/* If has, then shift x to the right by 4 bits */
	shift3 = flag << 2;
	x = x >> shift3;

	/* Whether x's left 2 bits has 1 */
	flag = !!(x >> 2);
	/* If has, then shift x to the right by 2 bits */
	shift4 = flag << 1;
	x = x >> shift4;

	flag = !!(x >> 1);
	shift5 = flag;
	/* Return the sum which means the index of first "1" from left */
	return shift1 + shift2 + shift3 + shift4 + shift5;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	unsigned result;
	unsigned tmp;

	/* Reverse the sign */
	result = uf ^ 0x80000000;
	/* Extract the exponent and mantissa */
	tmp = uf & 0x7fffffff;
	/* Check NAN */
	if (tmp > 0x7f800000) return uf;
	else return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/*
 * The sign bit is the same as the sign bit of the integer.
 * The exponent part is the position of the leftmost one in the integer.
 * The significand part is 23 bits, so it is 23 bits from the begining of the leftmost 1 to the right.
 */
	unsigned sign;
	unsigned exponent;
	unsigned significand;
	unsigned G, R, S;  /* Rounding */

	if (!x) return 0;
	if (x < 0) {sign = 0x80000000; x = ~x + 1;}
	else sign = 0;
	exponent = 31;

	while (!(x & 0x80000000) && exponent){
		x = x << 1;
		exponent = exponent + (~1+1);
	}
	exponent = (exponent + 127) << 23;
	significand = (x >> 8) + 0x00800000;
	/* do the rounding */
	G = (x & 0x01ff) >> 8;
	R = (x & 0x0ff) >> 7;
	S = !!(x & 0x7f);

	return sign + exponent + significand + ((R&&S) || (G&&R));
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned exp;
	unsigned sign;
	/* Extract the exponent */
	exp = uf & 0x7f800000;
	/* Extract the sign bit */
	sign = uf & 0x80000000;
	/* Check the exponent */
	if (exp){
		if (exp != 0x7f800000) uf = uf + 0x00800000;
	}
	else
		uf = (uf << 1) | sign;
	return uf;
}
