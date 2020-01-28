#!/usr/bin/python3

import math 

def truncate(number, digits):
    stepper = pow(10.0, digits)
    return float(math.trunc(stepper * number) / stepper)

cantidad_num = int(input())
med_geo = 1.0
med_arit = 0.0

for i in range(cantidad_num):
    An = float(input()) 
    med_arit = med_arit + An/float(cantidad_num)
    med_geo = med_geo * An**(1/float(cantidad_num))
    
print(truncate(med_arit-med_geo,4))  
