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
    parser.add_argument('--cats', required=False, type=int, help='Number of cats', default=1)
    parser.add_argument('--view', required=False, type=int, help='Cats view range', default=2)
    parser.add_argument('--eight_connected', required=False, action='store_true', help = 'Grid is 8-connected')


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
    obj_list_text = ' '.join([ 'n_{}_{}'.format(i,j) for i,j in coords ])
    idx = lambda i, j : i * args.dimension + j

    cat_list_text = ' '.join( 'cat_{}'.format(i) for i in range(0,args.cats))
    cat_view_ranges_text = '\n'.join( [ '(= (view_range cat_{}) {})'.format(i,args.view) for i in range(0,args.cats)] )
    cat_slots_text = '\n'.join( [ '(= (slot cat_{}) {})'.format(i,i) for i in range(0,args.cats)] )
    cat_escaped_text = '\n'.join( [ '(exit (location cat_{}))'.format(i) for i in range(0,args.cats)] )

    if args.eight_connected :
        dirs = [ (-1,0), (1,0), (0,1), (0,-1), (-1,-1), (-1,1), (1,1), (1,-1) ]
    else :
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
        exit_coords = []
        for i in range(args.exits) :
            k,l = t[i]
            exit_coords.append((k,l))
            exits.append( '(exit n_{}_{})'.format(k,l))
        exit_predicates_text = '\n'.join( [ '\t\t{}'.format(e) for e in exits ] )

        # determine cats initial locations
        cat_locations_text = []
        for i in range(0, args.cats) :
            k,l = random.choice([ c for c in coords if c not in exit_coords])
            cat_locations_text += [ '(= (location cat_{}) n_{}_{})'.format(i,k,l ) ]
        cat_locations_text = '\n'.join(cat_locations_text)

        instance_filename = 'grid_{}_{}_{}_{}_{}.pddl'.format(args.dimension, args.exits, permutation_index,args.cats,len(dirs))
        # load template
        instance_text = string.Template( template_text )
        # replace values
        mappings = {}
        mappings['N'] = args.dimension
        mappings['k'] = permutation_index
        mappings['objects'] = obj_list_text
        mappings['cats'] = cat_list_text
        mappings['exit_predicates'] = exit_predicates_text
        mappings['edge_predicates'] = edge_predicates_text
        mappings['cats_locations'] = cat_locations_text
        mappings['cats_view_range'] = cat_view_ranges_text
        mappings['cats_slots'] = cat_slots_text
        mappings['escaped_predicates'] = cat_escaped_text
        mappings['num_nodes'] = args.dimension * args.dimension
        mappings['max_distance_value'] = args.dimension * args.dimension * args.cats
        mappings['num_exits'] = args.exits
        mappings['num_cats'] = args.cats
        mappings['connections'] = len(dirs)

        with open( instance_filename, 'w') as output :
            print( instance_text.substitute(mappings), file=output )

        permutation_index += 1

if __name__ == '__main__' :
    main()
