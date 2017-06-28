//
//  main.c
//  2.64
//
//  Created by Ram Yadav on 4/7/17.
//  Copyright © 2017 Ram Yadav. All rights reserved.
//

int any_odd(unsigned x) {
    //using A(1010, Hexadecimal) 8-A, 32bit
    if ((x & 0xAAAAAAAA) == 1) {
        return 1;
    }
    return 0;
}


