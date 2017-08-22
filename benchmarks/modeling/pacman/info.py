
import os
import glob
import json

from viewer import layout


def main():

    for filename in glob.iglob('data/layouts/*.lay'):
        layout_name = os.path.split(filename)[1][:-4]  # Filenames end with ".lay"

        # Choose a layout
        l = layout.getLayout(os.path.abspath(filename))
        if l is None:
            raise Exception("The layout " + layout_name + " could be found")

        width = l.width
        height = l.height
        pacman_pos = None
        ghost_pos = []
        for is_pacman, pos in l.agentPositions:
            if is_pacman:
                pacman_pos = pos
            else:
                ghost_pos.append(pos)

        assert pacman_pos is not None

        pellets_orig = l.food.asList()
        pellets = [location_id(width, height, p) for p in pellets_orig]
        walls_orig = l.walls.asList()
        walls = [location_id(width, height, w) for w in walls_orig]
        capsules_orig = l.capsules
        capsules = [location_id(width, height, w) for w in capsules_orig]

        info = dict(
            layout=layout_name,
            width=width,
            height=height,
            dimensions="{}x{}".format(width, height),
            size=width*height,
            num_locations=width*height,
            num_ghosts=l.numGhosts,
            num_food=l.food.count(),
            pellets_orig_at=pellets_orig,
            pellets_at=pellets,
            walls_at=walls,
            walls_orig_at=walls_orig,
            pacman_orig_pos=pacman_pos,
            capsules_orig=capsules_orig,
            capsules=capsules,
            ghost_orig_pos=ghost_pos,
            pacman_pos=location_id(width, height, pacman_pos),
            ghost_pos=[location_id(width, height, p) for p in ghost_pos],
        )

        # Serialize the info to json and move on
        output_filename = filename[:-4] + ".json"
        with open(output_filename, 'w') as outfile:
            json.dump(info, outfile, sort_keys=True, indent=2)

    print("Done!")


def location_id(width, height, location):
    x, y = location
    # We need to "invert" the coordinates, miquel starts counting from above,
    # the pacman programmers from below (!!)
    return (height-1-y)*width + (x+1)


if __name__ == '__main__':
    main()
