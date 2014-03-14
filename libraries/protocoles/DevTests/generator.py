#! /usr/bin/python

import random as R

f = open('ctm', 'w')

for i in range(1, 1000):
    f.write(str(R.randint(0,1)) + "\n")


f.close()
