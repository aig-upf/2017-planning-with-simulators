#!/usr/bin/python3

import random
import string
import sys
import os
import itertools

def parse_arguments() :
    import argparse

    parser = argparse.ArgumentParser(description='Grid-shaped Predator & Prey Instance Generator')
    parser.add_argument('--dimension', required=True, type=int, help='Grid dimension')
    parser.add_argument('--predators', required=False, type=int, help='Number of predators', default=2)
    parser.add_argument('--preys', required=False, type=int, help='Number of preys', default=1)

    args = parser.parse_args()
    return args

def main() :

    if not os.path.exists('template') :
        raise SystemExit("Could not find instance template!")
    random.seed(3829113021)

    template_text = None
    with open( 'template') as instream :
        template_text = instream.read()

    args = parse_arguments()

    coords = [ t for t in itertools.product(range(0,args.dimension),range(0,args.dimension))]
    pos_list_text = ' '.join([ 'n_{}_{}'.format(i,j) for i,j in coords ])
    pos_coords_list = []
    for i in range(0,len(coords)) :
        x, y = coords[i]
        pos_coords_list += [ '\t(= (x n_{}_{}) {})'.format(y,x,x) ]
        pos_coords_list += [ '\t(= (y n_{}_{}) {})'.format(y,x,y) ]
    pos_coords_list = '\n'.join(pos_coords_list)
    idx = lambda i, j : i * args.dimension + j

    pred_list_text = ' '.join( 'pred_{}'.format(i) for i in range(0,args.predators))
    pred_slots_text = '\n'.join( [ '\t(= (slot pred_{}) {})'.format(i,i) for i in range(0,args.predators)] )

    pred_dx_init_list = '\n'.join( [ '\t(= (dx pred_{}) 0)'.format(i) for i in range(0,args.predators)] )
    pred_dy_init_list = '\n'.join( [ '\t(= (dy pred_{}) 0)'.format(i) for i in range(0,args.predators)] )

    preys_obj_list = ' '.join( [ 'prey_{}'.format(i) for i in range(args.preys)])
    trapped_preys =  '\n'.join( '(@trapped (location prey_{}))'.format(i) for i in range(args.preys))


    permutation_index = 1
    #permutations = [ t for t in itertools.permutations( coords, args.preys)]
    #sampled_permutations = random.sample(permutations, 10)


    for i in range(1,10):
        # determine initial locations
        preys_locations_text = []
        preys_locs = random.sample(coords, args.preys)
        for i in range(args.preys) :
            k,l = preys_locs[i]
            preys_locations_text += ['\t(= (location prey_{}) n_{}_{})'.format(i,k,l)]
        preys_locations_text = '\n'.join(preys_locations_text)

        predators_locations_text = []
        for i in range(0, args.predators) :
            k,l = random.choice([ c for c in coords if c not in preys_locs])
            predators_locations_text += [ '(= (location pred_{}) n_{}_{})'.format(i,k,l ) ]
        predators_locations_text = '\n'.join(predators_locations_text)

        instance_filename = 'grid_{}_{}_{}_{}.pddl'.format(args.dimension, args.predators, args.preys, permutation_index)
        # load template
        instance_text = string.Template( template_text )
        # replace values
        mappings = {}
        mappings['N'] = args.dimension
        mappings['num_preds'] = args.predators
        mappings['num_preys'] = args.preys
        mappings['pos_obj_list'] = pos_list_text
        mappings['preds_obj_list'] = pred_list_text
        mappings['preys_obj_list'] = preys_obj_list
        mappings['min_x'] = 0
        mappings['max_x'] = args.dimension-1
        mappings['min_y'] = 0
        mappings['max_y'] = args.dimension-1
        mappings['position_coordinates'] = pos_coords_list

        mappings['preys_locations'] = preys_locations_text
        mappings['predators_locations'] = predators_locations_text
        mappings['predators_slots'] = pred_slots_text

        mappings['predators_dx_init'] = pred_dx_init_list
        mappings['predators_dy_init'] = pred_dy_init_list

        mappings['trapped_preys'] = trapped_preys

        with open( instance_filename, 'w') as output :
            print( instance_text.substitute(mappings), file=output )

        permutation_index += 1

if __name__ == '__main__' :
    main()
