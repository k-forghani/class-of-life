# Class of Life

## Introduction

This is a program to simply simulate some fundamental biological processes, developed as the midterm project of **Advanced Programming** (**Spring 2023**) course at **Iran University of Science and Technology**. The architecture of the project is based on the [project description](schema/description.pdf) provided by teaching assistants.

## Installation

To compile the project and run the interface, just run `run.sh` with `main` argument:

```bash
chmod +x run.sh
./run.sh main
```

Instead of using the interface, you may run the test and debug the project:

```bash
./run.sh test
```

**Note**: The commands may be a bit different on Windows or macOS.

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

This project was founded by [*Kazem Forghani*](https://github.com/k-forghani) in collaboration with [*Elaheh Razmkhah*](https://github.com/ELrzm).

## License

This project has been released under *MIT License*.