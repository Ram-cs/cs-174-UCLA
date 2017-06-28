/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    /* compress value to single bit */
    //right shifting 16 bits
    int shift = (x >> 16);
    int ban_g = shift | x;
    
    //shifting from 1-8 bits and adding with privious value as we go along
    ban_g = (ban_g >> 1) | ban_g;
    ban_g = (ban_g >> 2) | ban_g;
    ban_g = (ban_g >> 4) | ban_g;
    ban_g = (ban_g >> 8) | ban_g;
    
    ban_g = ban_g ^ 0x1;
    return (ban_g & 0x1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    //getting the mask
    int m1 = (~0 ^ 0xEE);
    int m2 = ((m1 << 8) ^ 0x11);
    int m3 = ((m2 << 8) ^ 0x11);
    int mask = ((m3 << 8) ^ 0x11);
    
    //getting LSB for each heaxa bits in 32 bits: 0001 0001 0001 .....0001 (mask)
    int LSb4bits = x & mask;
    
    //found shift
    int shift = (((((x >> 1) & mask) + LSb4bits) + (mask & (x >> 2))) + (mask & (x >> 3)));
    
    // int shift = (((((LSb4bits + ((x >> 1) & mask)) + (x >> 2) & mask)) + ((x >> 3) & mask)));
    
    //getting each four bits binary through shifting and adding as go along
    //to find first four bits of bianry, anding and shifting with 15
    
    int bits_count = (shift) & (0xf);
    
    //each time we are getting right most hex bit count and added up at the as we shift right
    bits_count += ((shift >> 4)& 0xf);
    bits_count += ((shift >> 8)& 0xf);
    bits_count += ((shift >> 12)& 0xf);
    bits_count += ((shift >> 16)& 0xf);
    bits_count += ((shift >> 20)& 0xf);
    bits_count += ((shift >> 24)& 0xf);
    bits_count += ((shift >> 28)& 0xf);
    return bits_count;
}
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    /* De Morgans Law as discussed in the class*/
    return ~(~x & ~y);
    
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    //setting to get the mask
    int m = (((~(!!(n & 32)) + 1)) & x)|(x & ((1<< (n))-1));
    //got the mask
    int mask = m | (m << (n));
    //have 4 different shifting  n*16, n*8, n*4, n*2
    int shift_bit;
    
    //as going through shifting, adding up the bits that appears on the way
    shift_bit = n * 16;
    mask += ((mask << shift_bit) * (((shift_bit - 32) >> 31) & 0x1));
    shift_bit = n * 8;
    mask +=((mask << shift_bit) * (((shift_bit - 32) >> 31) & 0x1));
    shift_bit = n * 4;
    mask +=((mask << shift_bit) * (((shift_bit - 32) >> 31) & 0x1));
    shift_bit =  n * 2;
    mask += ((mask << shift_bit) * (((shift_bit - 32) >> 31) & 0x1));
    
    return mask;
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
int fitsBits(int x, int n)
{
    //getting sign by shifting right
    int mask = (x >> 31);
    //getting fitsBits from this operation
    return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
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
    //first did left 3 shifts and then,using this did right shifts
    //anded with 15 to get the desired answer
    return (x >> (n << 3)) & 0xFF ;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //getting sign
    int mask = ~(0x0) & (1 << 31);
    //getting difference, ~n = -n -1
    int diff = y + (~x + 1);
    //getting MSB with shifting
    int MSB = !((~(y ^ x)) >> 31);
    //XOR two operator to get the answer
    return (((!MSB) & (!(diff & mask))) ^ (((mask & x) >> 31) & MSB));
    
    
    
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    //getting the sign
    int x_sign = x & ((1 << 31) & ~(0x0));
    //XOR with shifting of sign to get the answer
    return !((x_sign >> 31 ^ !x)) ;
    
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n)
{
    //getting the mask first and shift and or with x
    int mask = ~(~((~n + n) << n) << (32 + (~n + 1)));
    return  mask & (x >> n);
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /*minimum = 0x80000000*/
    /*shifting bits by 31 in 32bits yields 1000 0000 0000 0000 0000 0000 0000 0000*/
    /*which is minimum*/
    return 1 << 31;
}
