#!/usr/bin/python
import os
import itertools

if __name__ == '__main__' :

    cmd_template = './generator.py --dimension {} --predators {} --preys {}'
    dimensions = [4,8]
    predators = [2,3]
    preys = [1,2,4,8]
    for N, predators, preys in itertools.product(dimensions,predators,preys) :
        os.system( cmd_template.format(N, predators, preys))
