
# Purely Declarative Action Representations are Overrated: Classical Planning with Simulators (IJCAI 2017)

This is the online repository for the publication

    Francès, Guillem, Ramı́rez, Miquel, Lipovetzky, Nir, and Geffner, Hector. [Purely declarative action representations are overrated: Classical planning with simulators](2017-ijcai-planning-with-simulators.pdf). In _Proceedings of the 26th International Joint Conference on Artificial Intelligence_, 2017. [https://doi.org/10.24963/ijcai.2017/600](https://doi.org/10.24963/ijcai.2017/600).


## Planner Source Code

The different variations of the `BFWS(R)` algorithm presented in the paper are implemented in an extension of the [`FS` planner](https://github.com/aig-upf/fs), a classical planner that works with the Functional STRIPS planning language, as described in the paper.
This extension is still under active development, but a tarball with the [source code](code/fs-planner-2017-ijcai.tgz) is provided here for reproducibility purposes. As some parts of the code are still experimental, please do not hesitate to contact the authors in case you have
troubles installing or running the planner.

### Installation Instructions

The planner currently requires that a certain number of dependencies be installed in the system:

1. A modified version of the [LAPKT Planning Toolkit](http://lapkt.org/), [available here as a tarball](code/lapkt-installation.tgz).

1. The [Gecode CSP Solver](http://www.gecode.org/) (tested with version 4.4.0 only). The recommended way to install it is on `~/local`, i.e. by running `./configure --prefix=~/local` before the actual compilation.

1. The [Clingo ASP solver](https://github.com/potassco/clingo) (optional, but used in the paper experiments). Precompiled packages are
available for several platforms. The `clingo`


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











This documentation covers a number of practical issues related to the use of the `FS` planner. The planner, however, has
been used and described in a number of academic publications that [can be found here](http://gfrances.github.io/pubs/),
the most recent of which are [[Francès and Geffner, 2015]](#ref-frances-modeling-2015) and [[Francès and Geffner, 2016a]](#ref-frances-existential-2016)
and [[Francès and Geffner, 2016b]](#ref-frances-effective-2016).

1. [Installation](#installation)
    1. [Docker Image](#docker-image)
    1. [Manual Installation](#manual-installation)
1. [Usage](#usage)
1. [Credits](#credits)
1. [References](#references)



## <a name="references"></a>Installation

### <a name="docker-image"></a>Docker Image

The fastest and recommended way to get started with the planner is by grabbing the ready-to-use Docker image and running it interactively.

In order to do so, you need to [have Docker installed on your machine](https://docs.docker.com/engine/installation),
and then you can pull the image with

```shell
docker pull aigupf/fs
```

Once the image is in your computer, you can log into a fully-functioning Docker container where the planner
and all its software dependencies are already installed for you:


```shell
docker run -it aigupf/fs
python3 preprocessor/runner.py --tag test --instance $FSBENCHMARKS/benchmarks/counters-fn/instance_5.pddl --run --driver=smart
```


### <a name="manual-installation"></a>Manual Installation

Alternatively, you can perform a full installation of the planner and all its dependencies from source.
To begin with, you will need the following software components:

1. The [LAPKT Planning Toolkit](http://lapkt.org/), which provides the base search algorithms used with our heuristics.
You should use the branch `v2_work`, as explained [here](https://github.com/miquelramirez/LAPKT-public/blob/v2-work/aptk2/README.md).

1. The [Gecode CSP Solver](http://www.gecode.org/) (tested with version 4.4.0 only). The recommended way to install it is on `~/local`, i.e. by running `./configure --prefix=~/local` before the actual compilation.


Once you have installed these projects locally, your system needs to be configured with the following environment variables,
e.g. by setting them up in your  `~/.bashrc` configuration file:


```shell
export LAPKT_PATH="${HOME}/projects/code/lapkt"
export LAPKT2_PATH="${LAPKT_PATH}/aptk2"
export FS_PATH="${HOME}/projects/code/fs"

# Local C++ library installations
export LD_LIBRARY_PATH=$LIBRARY_PATH:/usr/local/lib
if [[ -d ${HOME}/local/lib ]]; then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/local/lib
fi

# LAPKT and FS libraries
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${FS_PATH}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LAPKT2_PATH}/lib
```

Once all this is set up, you can build the project library by doing

```shell
cd $FS_PATH
scons
```

You can run `scons debug=1` to build the debug version of the library, or `scons edebug=1` to build an extremely-verbose debug version.


## <a name="usage"></a>Usage

`FS` is invoked through a high-level Python script which parses any FSTRIPS problem specification and generates certain data which is necessary for the
main planner module to run. The main Python preprocessing script is `$FS_PATH/preprocessor/runner.py`, and can be invoked like
(replace `$BENCHMARKS` by an appropriate directory):

```shell
python3 runner.py --tag foo --instance $BENCHMARKS/fn-simple-sokoban/instance_6.pddl --run --driver=smart
```

Where `instance_6.pddl` is a Functional STRIPS (or standard STRIPS) instance file, and
`foo` is an arbitrary name that will be used to determine the output directory where the executable solver, related data, and results will be left, which in this case will be
`$FS_PATH/generated/test/fn-simple-sokoban/instance_6`. Read below for further details on the semantics of the `--run` and `--driver` options.
If externally-defined symbols are used, the parsing process involves the automatic generation of a bunch of C++ classes that
is then compiled and linked against the binary solver.
If `--run` is not used, only the parsing stage is run, in which case all files necessary to run the solver are left on the abovementioned directory, and nothing else is done.
If that is the case, we can run the automatically generated `solver.bin` executable from that directory (add the `-h` flag for further options :

```shell
cd $FS_PATH/generated/test/fn-simple-sokoban/instance_6
./solver.bin
```

Note that only the non-debug executable is built by default, but you can invoke the `generator.py` script with flags `--debug` and `--edebug` to control the debug level
of the resulting executable.


Once the planner for a particular problem instance has been compiled, and we are about to run it on the particular planner directory,
a number of options can be specified on the command line, the most prominent of them being the search driver.


### Search Driver

The planner is pre-configured with a number of "search drivers" that specify the global search strategy
(search algorithm plus heuristic, if necessary) that will be followed in the search for a plan.
The `--driver` command-line option is thus mandatory; for instance, to use the planner with the `smart` driver we would invoke
`./solver.bin --driver=smart`. The following are the main available drivers:

* `lite`: The lite driver is a greedy best-first search which works with the _non-constrained_ RPG heuristics, i.e. computes the _standard_
h_FF and h_MAX heuristics, the only difference being that it can work with the more compact Functional STRIPS encodings, thus not being restricted to
predicative STRIPS.

* `native`: The native driver implements a greedy best-first search coupled with a _constrained_ RPG heuristic that can be
either the h_FF (heuristic=hff) or the h_MAX heuristic (heuristic=hmax). The particularity of this driver is that the CSPs into which
the computation of the heuristic is mapped are not solved by Gecode, but rather by a native, hand-coded simplified approach which might yield some performance gain, since it avoids the overhead of interacting with Gecode. The downside of this approach is that only a certain subset of
FSTRIPS is accepted (namely, that which results in very simple CSPs), and only approximated CSP resolution is used.

* `standard`: A greedy best-first search with one of the two _constrained_ RPG heuristics, which is computed with a 1-CSP-per-ground-action model.

* `smart`: The smart driver implements a greedy best-first search coupled with a _constrained_ RPG heuristic that can be
either the h_FF (heuristic=hff) or the h_MAX heuristic (heuristic=hmax). When it comes to computing the heuristic, though,
this driver does not need to work on a "1-CSP-per-ground-action" basis --- the limitation of this being that
the number of ground actions, and thus of CSPs, is exponential in the number of parameters of the action schemas.
Instead, this driver works on a "1-CSP-per-action-effect" basis, but the grounding is "smart", i.e. it only grounds as much as necessary
so that the effect head is a state variable. Among other things, this means that the number of CSPs is now
exponential only in the number of action parameters in the head of the effect, which will tipically be smaller.
The `smart` driver accepts conditional effects.

* `lifted`: The lifted driver implements a fully-lifted greedy-best first search, meaning that actions are never grounded, but instead
the constraint-based nature of the planner are used to model the task of deciding which actions are applicable in a given state as a particular CSP which is then solved whenever we need to expand a node during the search. This can yield a benefit in problems with a huge number
of ground actions, which usually will not work well with traditional planners that ground all the action schemas, as they will never go beyond the grounding phase.

* `smart_lifted`: This driver conducts a fully-lifted search as the `lifted` driver above,
This is thus equivalent to the `smart` driver above, but using lifted search as in the `lifted` driver.

* `unreached_atom`: An experimental driver which performs a greedy best-first search on a version of the constrained RPG heuristics which is computed
in a somewhat different manner that iterates through atoms that have not yet been reached in the RPG, trying to achieve them one by one.
Seems to perform better than other options in some domains, but not in general.

* `iw`: Iterated Width search.

* `bfws`: A Greedy best-first search with a novelty-based heuristic. Namely, the search favors states with
(1) lower novelty, (2) higher number of satisfied goal atoms, if novelty is equal, and (3) lower accumulated cost, the two
first factors being equal.

* `bfs`: A blind, standard breadth-first search.



