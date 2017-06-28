//
//  main.c
//  switch
//
//  Created by Ram Yadav on 4/23/17.
//  Copyright © 2017 Ram Yadav. All rights reserved.
//

long switch_prob(long x, long n) {
    long result = x;
    switch(n) {
        case 60:
            return 8 * x;
            break;
            
        case 61:
            return x + 75;
            break;
            
        case 62:
           return 8 * x;
            break;
        
        case 63:
            return x >> 3;
            break;
        case 64:
            return (((x << 4) - x) * ((x << 4) - x)) + 75;
            break;
            
        case 65:
           return (x * x ) + 75;
            break;
            
        default:
            x + 75;
            break;
    }
    return result;
}
