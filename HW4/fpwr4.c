#include <math.h>
#include <stdio.h>

#ifdef NAN
#endif

#ifdef INFINITY
#endif

float fpwr2(int x) {
  unsigned exp, frac;
  unsigned u;
  
  if (x < -74) {
      /* Too small. Return 0.0 */
    exp = 0;
    frac = 0;
  } else if (x < -63) {
      /* Denormalized result */
    exp = 0;
    frac = 1 << (x + 149);
  } else if (x < 64) {
      /* Normalized result. */
    exp = x + 127;
    frac = 0;
  } else {
      /* Too big. Return +oo */
    exp = 255;
    frac = 0;
  }
  
  u = exp << 23 | frac;
  return u2f(u);
}

float u2f(unsigned u) {
  int bias = 127; //exponent has 8 digit 2^(8-1) - 1
  float f = 0.0;
  int i;
  int e = 0;
  int temp = 0; //Check for NAN, INFINITY or normalize
  
  //This if statement is denormalized
  if (!((u >> 23) & 0xFF)) {
    for (i = 1; i < 24; i++) {
      if (!!((u >> (i-1)) & 1)) {
        f += pow(2, -(24 - i));
      }
    }
    
    //if fraction is 0
    if (f == 0)
      return 0.0;
    
    return pow(2, (1-bias)) * f;
  }
  
  //Check for all 1's in exp
  for (i = 23; i < 31; i++) {
    if (!((u >> i) & 1)) {
      temp = 1;
      break;
    }
  }
  
  //If temp equals 0, mean the fraction is either NAN or INFINITY
  //since the exp is all 1
  if (temp == 0) {
    for (i = 1; i < 24; i++) {
      //Check if there is a non zero in the fraction
      if (!!((u>>(i-1)) & 1)) {
        return NAN;
      }
    }
    return INFINITY;
  }
  
  //after this, we only have normalized value
  //calculation for normalization
  for (i = 1; i < 24; i++) {
    if (!!((u >> (i - 1)) & 1)) {
      f += pow(2, -(24 - i));
    }
  }
  
  f += pow(2, 0);
  
  for (i = 0; i < 8; i++) {
    if (!!((u >> (i + 23)) & 1)) {
      e += pow(2, i);
    }
  }
  
  return pow(2, (e - bias)) * f;
}



