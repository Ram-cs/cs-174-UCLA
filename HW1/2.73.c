//
//  main.c
//  2.73
//
//  Created by Ram Yadav on 4/8/17.
//  Copyright © 2017 Ram Yadav. All rights reserved.
//

int saturating_add(int x, int y) {
    int sum = x + y;
    int size = (sizeof(int) << 3) - 1;
    
    //when condition return 1 (true), 0 when condition false
    int x_negative_mask = (x >> size);
    int y_negative_mask = (y >> size);
    int z_negative_mask = (sum >> size);
    
    int positive_over = ~x_negative_mask & ~y_negative_mask & z_negative_mask;
    int negative_over = x_negative_mask& y_negative_mask & ~z_negative_mask;
  
    return (positive_over & INT_MAX) | (negative_over & INT_MIN);
}
