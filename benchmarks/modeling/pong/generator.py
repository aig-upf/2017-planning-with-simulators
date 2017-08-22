#!/usr/bin/python3

import random
import string
import sys
import os
import itertools

def parse_arguments() :
    import argparse

    parser = argparse.ArgumentParser(description='Grid-shaped Blocker Instance Generator')
    parser.add_argument('--template', required=True,  help='Template to use')
    parser.add_argument('--pucks', type=int, help='Number of pucks in play', default = 1)
    parser.add_argument('--hits', type=int, help='Number of hits per puck', default = 1)
    parser.add_argument('--num', type=int, help='Number of instances to generate', default = 10)

    args = parser.parse_args()
    return args

def main() :

    args = parse_arguments()

    if not os.path.exists(args.template) :
        raise SystemExit("Could not find template file '{}'!".format(args.template))
    print("Using template: {}".format(args.template))
    random.seed(3829113021)

    template_text = None
    with open( args.template ) as instream :
        template_text = instream.read()

    puck_obj_list = ' '.join( 'p_{}'.format(i) for i in range(args.pucks))

    goals = []
    for i in range(args.pucks) :
        goals += [ '(> (hits r0_obs p_{}) {})'.format(i,args.hits) ]
    goals = '\n'.join(goals)

    # pucks start moving always away from the paddle
    velocity_vectors = 'v_1_1 v_1_m1 '.split()
    X = range(2,50)
    Y = range(10,20)

    for i in range(1,args.num) :

        # puck data
        #        (= (x p0) 60)
        #        (= (y p0) 10)
        #        (= (v_vec p0) v_1_1)
        #        (= (acceleration p0) 1)
        #;; obstacles
        #       (= (hits r0_obs p0) 0)
        #       (= (hits top p0) 0)
        #       (= (hits bottom p0) 0)
        #       (= (hits right p0) 0)
        pucks_data = []
        for j in range(args.pucks) :
            pucks_data += [ '(= (x p_{}) {})'.format(j,random.choice(X)) ]
            pucks_data += [ '(= (y p_{}) {})'.format(j,random.choice(Y)) ]
            pucks_data += [ '(= (v_vec p_{}) {})'.format(j,random.choice(velocity_vectors)) ]
            pucks_data += [ '(= (acceleration p_{}) 1)'.format(j) ]
            pucks_data += [ '(= (hits r0_obs p_{}) 0)'.format(j)]
            pucks_data += [ '(= (hits top p_{}) 0)'.format(j)]
            pucks_data += [ '(= (hits bottom p_{}) 0)'.format(j)]
            pucks_data += [ '(= (hits right p_{}) 0)'.format(j)]
        pucks_data = '\n'.join(pucks_data)

        instance_filename = '{}_{}_{}_{}.pddl'.format(args.template.replace('template_',''),args.pucks,args.hits,i)
        # load template
        instance_text = string.Template( template_text )
        # replace values
        mappings = {}
        mappings['puck_object_list'] = puck_obj_list
        mappings['pucks_data'] = pucks_data
        mappings['paddle_center'] = 10
        mappings['paddle_radius'] = 5
        mappings['goals'] = goals
        with open( instance_filename, 'w') as output :
            print( instance_text.substitute(mappings), file=output )




if __name__ == '__main__' :
    main()
