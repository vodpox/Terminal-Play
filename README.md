# Terminal Play

Framework/game engine for terminal/console/CLI games for UNIX like systems and Windows (although [not all features](https://github.com/edve98/Terminal-Play/wiki/Windows) are supported in Windows terminal). Right now it's in late alpha so expect to see some minor changes in the API. 1.0.0 Release should come in the week after Ludum Dare 36.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development. for more in-depth tutorial go to the project's [wiki](https://github.com/edve98/Terminal-Play/wiki).

### Prerequisites

All you need to use this framework is `g++` and `make` (and `mingw` if you want to build for Windows). Even if you don't have these already it shouldn't be too hard to install them. Please follow instructions that are suitable for your OS.

### Installing

Download and build the framework.

```
$ git clone https://github.com/edve98/Terminal-Play.git
$ cd Terminal-Play/
$ make
```

### Building example project

cd into example project's directory and then build it.

```
$ cd examples/simple\ demo/
$ make
```

Now run the example to test it.

```
$ ./game
```

## Authors

* **Edvinas Senda** - *Initial work* - [edve98](https://github.com/edve98)

See also the list of [contributors](https://github.com/edve98/Terminal-Play/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License version 3 - see the [LICENSE](LICENSE) file for details
