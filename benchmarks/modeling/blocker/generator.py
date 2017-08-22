#!/usr/bin/python3

import random
import string
import sys
import os
import itertools

def parse_arguments() :
    import argparse

    parser = argparse.ArgumentParser(description='Grid-shaped Blocker Instance Generator')
    parser.add_argument('--dimension', required=True, type=int, help='Grid dimension')
    parser.add_argument('--exits', required=False, type=int, help='Number of exit nodes', default=1)

    args = parser.parse_args()
    return args

def main() :

    if not os.path.exists('template') :
        raise SystemExit("Could not find instance template!")

    template_text = None
    with open( 'template') as instream :
        template_text = instream.read()

    args = parse_arguments()

    coords = [ t for t in itertools.product(range(0,args.dimension),range(0,args.dimension))]
    obj_list_text = ' '.join([ 'n_{}_{}'.format(i,j) for i,j in coords ])
    idx = lambda i, j : i * args.dimension + j

    dirs = [ (-1,0), (1,0), (0,1), (0,-1)]
    edges = []
    for i in range(0,args.dimension) :
        for j in range(0, args.dimension) :
            for di, dj in dirs :
                k = i + di
                if k < 0 or k >= args.dimension : continue
                l = j + dj
                if l < 0 or l >= args.dimension : continue
                predicate = '(edge n_{}_{} n_{}_{})'.format(i,j,k,l)
                edges.append(predicate)
    edge_predicates_text = '\n'.join(['\t\t{}'.format(e) for e in edges])

    possible_exits = [ (0,0), (0,args.dimension-1), (args.dimension-1,0), (args.dimension-1,args.dimension-1)]

    permutation_index = 1
    for t in itertools.permutations( possible_exits, args.exits) :
        exits = []
        for i in range(args.exits) :
            k,l = t[i]
            exits.append( '(exit n_{}_{})'.format(k,l))
        exit_predicates_text = '\n'.join( [ '\t\t{}'.format(e) for e in exits ] )


        instance_filename = 'grid_{}_{}_{}.pddl'.format(args.dimension, args.exits, permutation_index)
        # load template
        instance_text = string.Template( template_text )
        # replace values
        mappings = {}
        mappings['N'] = args.dimension
        mappings['k'] = permutation_index
        mappings['objects'] = obj_list_text
        mappings['exit_predicates'] = exit_predicates_text
        mappings['edge_predicates'] = edge_predicates_text
        mappings['cat_initial_location'] = 'n_{}_{}'.format(int(args.dimension/2),int(args.dimension/2))
        mappings['num_nodes'] = args.dimension * args.dimension
        mappings['num_exits'] = args.exits

        with open( instance_filename, 'w') as output :
            print( instance_text.substitute(mappings), file=output )

        permutation_index += 1

if __name__ == '__main__' :
    main()
