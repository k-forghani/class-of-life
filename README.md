# Class of Life

## Introduction

This is a program to simply simulate some fundamental biological processes, developed as the midterm project of **Advanced Programming** (**Spring 2023**) course at **Iran University of Science and Technology**. The architecture of the project is based on the [project description](schema/description.pdf) provided by teaching assistants.

## Compilation

On Unix-like operating systems, to compile the project and run the interface, just run `run.sh` with `main` argument:

```bash
chmod +x run.sh
./run.sh main
```

Instead of using the interface, you may run the test to debug the project:

```bash
./run.sh test
```

On Windows, to compile the project and run the interface, you can run `main.bat`. Also just run `test.bat` to run the test and debug the project.

**Note**: You can also run these commands to compile the interface of the program:

```bash
g++ -c libs/*.cpp
g++ -c classes/*.cpp
g++ -o main main.cpp *.o
```

Then you can run `main` to use the interface.

## Getting Started

You can read the [documentation](docs/README.md) to find out how to use the program via provided command line interface.

## Schema

<p align="center">
    <img src=schema/modules.drawio.svg><br>
    <span>Figure 1. Modules Schema</span>
</p>

<p align="center">
    <img src=schema/classes.drawio.svg>
    <span>Figure 2. Classes Schema</span>
</p>

<p align="center">
    <img src=schema/classes/Cell.drawio.svg>
    <span>Figure 3. <i>Cell.h</i> & <i>Cell.cpp</i> Schema</span>
</p>

<p align="center">
    <img src=schema/classes/Animal.drawio.svg>
    <span>Figure 4. <i>Animal.h</i> & <i>Animal.cpp</i> Schema</span>
</p>

<p align="center">
    <img src=schema/classes/Interface.drawio.svg>
    <span>Figure 5. <i>Interface.h</i> & <i>Interface.cpp</i> Schema</span>
</p>

## Developers

This project was developed by [*Kazem Forghani*](https://github.com/k-forghani), a student of Computer Science Department of Iran University of Science and Technology, in collaboration with [*Elaheh Razmkhah*](https://github.com/ELrzm).

You can contact via k_forghani@mathdep.iust.ac.ir.

## License

This project has been released under *MIT License*.