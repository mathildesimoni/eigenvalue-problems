# eigenvalue-problems

This is the final project for the class "Programming Concepts in Scientific Computing" on the implementation of numerical methods for eigenvalue computation.

## Table of Contents
- [Requirements](#requirements)
- [Compilation and Usage](#compilation-and-usage)
- [Program Flow](#program-flow)
- [Features](#features)
- [Tests](#tests)
- [Limitations and TODOs](#limitations-and-todos)
- [Authors and Acknowledgement](#authors_acknowledgement)


<a name="requirements"/>

## Libraries & Requirements

The librairies used in this application are *Eigen*, *GoogleTest* and *yaml-cpp*. They are all part of the repository as submodules.

The requirements to run this application are as follows:

- CMake: Minimum required version: 3.5.0
- C++ Compiler: Support for C++20 standard
- Doxygen (if documentation needs to be generated again) as well as the *graphviz* library for generating UML class diagrams in the documentation.
- Git: for cloning and updating submodules.

<a name="features"/>

## Features

This application is designed to compute the **eigenvalues** of a square matrix $A \in \mathbb{R}^{n \times n}$. The eigenvalue problem is mathematically formulated as:

$$
A \mathbf{v} = \lambda \mathbf{v}
$$

where:
- $A$ is a square matrix
- $\mathbf{v}$ (non-zero) is the **eigenvector**
- $\lambda$ is the **eigenvalue** associated with $\mathbf{v}$

<a name="compilation_and_usage"/>

## Compilation and Usage

=> will need to say to add the inputs in "input/" folder and that the results are generated in the output/ folder. No need to specify the path, only the file name. (the path is taken care of)
write what kind of arguments for each method

Input
all of this in an input.yaml file that needs to be updated

Output
depends on the user args


<a name="program_flow"/>

## Program Flow

The UML diagram of the component of our project can be found in the next figure.

![Alt text](eigenvalue-probem_UML_v1.drawio.png?raw=true "Title")

Explain the implementation, how the class are linked and the different parts of the program

More information about each function and class can be found in the documentation


<a name="tests"/>

## Tests

validating tests
explain how to test?

<a name="limitation_todo"/>

## Limitations and TODOs



<a name="authors_acknowledgement"/>

## Authors and Acknowledgement
