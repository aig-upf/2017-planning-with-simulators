

This is the online repository for the following publication:

Guillem Francès, Miquel Ramı́rez, Nir Lipovetzky and Hector Geffner. [Purely declarative action representations are overrated: Classical planning with simulators](2017-ijcai-planning-with-simulators.pdf). In _Proceedings of the 26th International Joint Conference on Artificial Intelligence_, 2017. [https://doi.org/10.24963/ijcai.2017/600](https://doi.org/10.24963/ijcai.2017/600).

Source code for the planner as well as the benchmarks used in the paper are described next.


## Planner Source Code

The different variations of the `BFWS(R)` algorithm presented in the paper are implemented in an extension of the [`FS` planner](https://github.com/aig-upf/fs), a classical planner that works with the Functional STRIPS planning language, as described in the paper.
This extension is still under active development, but a tarball with the [source code](code/fs-planner-2017-ijcai.tgz) is provided here for reproducibility purposes. As some parts of the code are still experimental, please do not hesitate to contact the authors in case you have
troubles installing or running the planner.

### Installation Instructions

The planner currently requires that a certain number of dependencies be installed in the system:

1. A modified version of the [LAPKT Planning Toolkit](http://lapkt.org/), [available here as a tarball](code/lapkt-installation.tgz).

1. The [Gecode CSP Solver](http://www.gecode.org/) (tested with version 4.4.0 only). The recommended way to install it is on `~/local`, i.e. by running `./configure --prefix=~/local` before the actual compilation.

1. The [Clingo ASP solver](https://github.com/potassco/clingo) (optional, but used in the paper experiments). Precompiled packages are
available for several platforms.


Once you have installed these projects locally or globally, your system needs to be configured with the following environment variables,
e.g. by setting them up in your  `~/.bashrc` configuration file:


```shell
# Local C++ library installations
if [[ -d /usr/local/lib ]]; then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
fi
if [[ -d ${HOME}/local/lib ]]; then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/local/lib
fi

# LAPKT and FS libraries
export LAPKT="${HOME}/projects/code/lapkt-installation"  # Path where the LAPKT code is located
export FS_PATH="${HOME}/projects/code/fs"  # Path where the FS planner code is located

# Clingo C++ Library
export GRINGO_PATH="${HOME}/lib/clingo-5.1.0-linux-x86_64" # Path where the gringo binary is located

# LAPKT and FS libraries
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${FS_PATH}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LAPKT}/lib

```

Once all this is set up, you can build the project library by doing

```shell
cd $FS_PATH
./build.py -pd
```

Which will build both the production and debug versions of the library.


## <a name="usage"></a>Usage

`FS` is invoked through a high-level Python script which parses any FSTRIPS problem specification and generates certain data which is necessary for the main planner module to run. The main Python preprocessing script is `$FS_PATH/run.py`, and can be invoked like
(replace `$BENCHMARKS` by an appropriate directory):

```shell
./run.py --instance $PAPERBENCHMARKS/modeling/pacman/smallclassic.pddl --driver sbfws --options bfws.rs=none
```

When externally-defined symbols are used, as in the example above, the parsing process involves the automatic generation of a bunch of C++ classes that is then compiled and linked against the binary solver.
By default, the production library is invoked, but you can add the flag `--debug` to invoke the debug version, for troubleshooting.


## Benchmarks

The problems used in the paper to benchmark our planner include `PDDL` domains from the last two International Planning Competitions (IPC),
along with a novel set of benchmarks that illustrates the modeling possibilities afforded by externally-defined procedures (and, to a lesser extent, function symbols), which can be efficiently dealt with by the BFWS algorithm presented in the paper.

The IPC benchmarks include all instances from the last planning competition (IPC 2014),
along with all instances from IPC 2011 domains that did not appear again in IPC 2014,
with the exception of the `Parcprinter`, `Tidybot` and `Woodworking` domains, which produced parsing errors.
The exact versions of the domains used [can be found here](benchmarks/ipc). Some domains have are slight modifications
of the official version that correct minor syntactic bugs, so this is the set of benchmarks that should be used 
for reproducibility purposes.

The novel benchmarks, in turn, [can be found here](benchmarks/ipc), and include the following domains

* `Pong`: A single-player version of the [Pong](https://en.wikipedia.org/wiki/Pong) arcade, where the agent controls a paddle and aims at hitting a certain number of times each of the pucks in the game, which follow their own dynamics. The encoding uses procedures to track collisions between the puck and walls or the paddle, and to update the velocity and direction of the puck.

* `Pacman`: A version of the well-known [Pac-Man](https://en.wikipedia.org/wiki/Pac-Man) game, where in each state of the game ghosts move (deterministically) to the adjacent cell that is closest to the pac-man location, in terms of Manhattan distances (ties broken by following a fixed order among possible directions). A Python script is provided to generate planning instances corresponding to all of the map layouts from the [Berkeley Pacman Project](http://ai.berkeley.edu/project_overview.html).

* `Predator and Prey`: A game of predators and preys. Prey agents follow a deterministic strategy that moves them as far as possible from the predators, whereas the predators’ task is to catch some prey.

* `Blocker`: A turn-taking Trapping game from [Ivankovic and Haslum, 2015](https://www.aaai.org/ocs/index.php/IJCAI/IJCAI15/paper/viewPaper/10971) where the main agent or blocker aims at trapping an opponent, the cat. This is done by blocking one node at a time on the graph in which the two creatures move until no path to an exit node exists for the cat. The deterministic strategy followed by the cat, that directs it to the closest available exit, is modeled with an external procedure that computes the exit node that the cat should move to, for any given state of the game.

* `Helper`: The reverse of `Blocker`, in which the objective of the agent is to guide the cat to an exit by switching on and off the light on certain graph nodes, knowing that the cat will move deterministically to the closest illuminated cell within its limited view range,
ties broken by following an arbitrary, fixed order.


## Bibtex Reference

	@inproceedings{frances2017action,
		author = "Franc{\`e}s, G. and Ram\'{i}rez, M. and Lipovetzky, N. and Geffner, H.",
		title = "Purely Declarative Action Representations are Overrated: Classical Planning with Simulators",
		booktitle = "Proc. 26th Int. Joint Conf. on Artificial Intelligence",
		pages = "4294--4301",
		year = "2017"
	}

