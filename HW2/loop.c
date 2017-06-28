//
//  main.c
//  loop
//
//  Created by Ram Yadav on 4/24/17.
//  Copyright © 2017 Ram Yadav. All rights reserved.
//

long loop(long x, long n)
{
    long result = 0 ;
    long mask;
    for (mask = 1; mask != 0 ; mask = mask << n) {
        result |= (mask & x);
    }
    return result;
}
