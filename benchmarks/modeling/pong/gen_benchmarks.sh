#!/bin/bash
./generator.py --template template_small --pucks 1 --hits 2 --num 10
./generator.py --template template_small --pucks 2 --hits 2 --num 10
./generator.py --template template_small --pucks 4 --hits 2 --num 10
./generator.py --template template_small --pucks 8 --hits 2 --num 10

./generator.py --template template_atari_2600 --pucks 1 --hits 2 --num 10
./generator.py --template template_atari_2600 --pucks 2 --hits 2 --num 10
./generator.py --template template_atari_2600 --pucks 4 --hits 2 --num 10
./generator.py --template template_atari_2600 --pucks 8 --hits 2 --num 10
