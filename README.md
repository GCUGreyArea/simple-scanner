# Simple Scanner

## Dependencies

1. [Google test](https://github.com/google/googletest) framework.
2. [Google benchmark](https://github.com/google/benchmark) framework

These can be installed in Linux by running sudo `sudo apt install libgtest-dev`
and `sudo apt install libbenchmark-dev` respectively. On MacOS the commands are
`brew install googletest` and `brew install google-benchmark`.

Or they can be built from source

## Building the project

The project has been designed and tested on MacOS but should build and function
correctly on Linux. If you are running Windows 10 or 11 please build this
project in WSL2 using the latest Ubuntu distro.

```bash
$ git clone https://github.com/GCUGreyArea/simple-scanner.git
$ cd simple-scanner
$ make test benchmark project
$ ./build/producer_consumer
```

## Updating the project

If you already have the code

```bash
$ cd ring_buffer
$ git pull
$ make clean test benchmark project
$ ./build/simple_scanner
```

## Building and running unit tests and benchmarks

Unit tests and benchmarks are built in the standard build. Test are provided in
the `test` directory and benchmarks in the `benchmark` directory. These can
either be run from the command line or through the makefile.

```bash
$ ./test/build/test_simple_scanner

OR

$ make test
```

```bash
$ ./benchmark/build/benchmark_simple_scanner

OR

make benchmark
```

## Optional code documentation

Optional code documentation is also available through
[Doxygen](https://doxygen.nl/manual/starting.html). Both `Doxygen` and
`graphviz` need to be installed.

Doxygen can be [installed from source](https://doxygen.nl/manual/install.html)
on either MacOS or Linux.

On Linux run `sudo apt-get install doxygen graphviz` On MacOS run `brew install
doxygen` and `brew install graphviz`


```bash
$ make docs
```

The resulting HTML pages will be available in `docs/output/html`

## License 

This software is licensed under the `GNU GENERAL PUBLIC LICENSE` version 3.

Please read the [license](LICENSE.TXT) before using this software or integrating
it into your project
