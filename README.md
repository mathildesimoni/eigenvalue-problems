# eigenvalue-problems

This is the final project for the class "Programming Concepts in Scientific Computing" on the implementation of numerical methods for eigenvalue computation.

## Table of Contents
- [Libraries & Requirements](#libraries--requirements)
- [Features](#features)
- [Compilation & Usage](#compilation--usage)
- [Program Flow](#program-flow)
- [Tests](#tests)
- [Limitations & TODOs](#limitations--todos)
- [Authors & Acknowledgement](#authors--acknowledgement)


## Libraries & Requirements

The librairies used in this application are *Eigen*, *GoogleTest* and *yaml-cpp*. They are all part of the repository as submodules.

The requirements to run this application are as follows:

- CMake: Minimum required version: 3.5.0
- C++ Compiler: Support for C++20 standard
- Doxygen (if documentation needs to be generated again) as well as the *graphviz* library for generating UML class diagrams in the documentation.
- Git: for cloning and updating submodules.


## Features

This application is designed to compute the **eigenvalues** of a square matrix $A \in \mathbb{R}^{n \times n}$. The eigenvalue problem is mathematically formulated as:

$$
A \mathbf{v} = \lambda \mathbf{v}
$$

where:
- $A$ is a square matrix
- $\mathbf{v}$ (non-zero) is the **eigenvector**
- $\lambda$ is the **eigenvalue** associated with $\mathbf{v}$

### Supported Methods
The application provides **five numerical methods** for finding eigenvalues.

### 1. **Power Method**
The **Power Method** iteratively finds the **the biggest eigenvalue** $\lambda_{\text{max}}$.

**Algorithm**:
1. Start with an arbitrary non-zero vector $\mathbf{v}_0$.
2. Compute $\mathbf{v}_{k+1} = A \mathbf{v}_k$ and normalize it.
3. Approximate the eigenvalue: $\lambda_k = \frac{\mathbf{v}_k^\top A \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.
4. Repeat until convergence.

**Returns**: The eigenvalue $\lambda_{\text{max}}$.

---

### 2. **Power Method with Shift**
This is a variant of the Power Method that computes the eigenvalue closest to a specified shift $\sigma$. It uses the matrix $A - \sigma I$, where $I$ is the identity matrix.

**Algorithm**:
1. Compute $\mathbf{v}_{k+1} = (A - \sigma I) \mathbf{v}_k$.
2. Normalize $\mathbf{v}_{k+1}$.
3. Approximate the eigenvalue: $\lambda_k = \frac{\mathbf{v}_k^\top A \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.

**Returns**: The eigenvalue $\lambda$ closest to the shift $\sigma$.

---

### 3. **Inverse Power Method**
The **Inverse Power Method** computes the **smallest eigenvalue** $\lambda_{\text{min}}$ by working with the inverse of $A$.

**Algorithm**:
1. Solve $A \mathbf{w} = \mathbf{v}_k$ (i.e. compute $\mathbf{w} = A^{-1} \mathbf{v}_k$).
2. Set $\mathbf{v}_{k+1} = \mathbf{w} / \|\mathbf{w}\|$.
3. Approximate the eigenvalue: $\lambda_k = \frac{\mathbf{v}_k^\top A \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.

**Returns**: The eigenvalue $\lambda_{\text{min}}$.

---

### 4. **Inverse Power Method with Shift**
This is a variant of the Inverse Power Method that computes the eigenvalue closest to a specified shift $\sigma$. It uses the matrix $(A - \sigma I)^{-1}$.

**Algorithm**:
1. Solve $(A - \sigma I) \mathbf{w} = \mathbf{v}_k$.
2. Normalize $\mathbf{w}$: $\mathbf{v}_{k+1} = \mathbf{w} / \|\mathbf{w}\|$.
3. Approximate the eigenvalue: $\lambda_k = \frac{\mathbf{v}_k^\top A \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.

**Returns**: The eigenvalue $\lambda$ closest to the shift $\sigma$.

---

### 5. **QR Method**
The **QR Method** iteratively finds all eigenvalues of the matrix $A$. It is based on the QR decomposition of $A$.

**Algorithm**:
1. Decompose $A_k = Q_k R_k$, where $Q_k$ is orthogonal and $R_k$ is upper triangular.
2. Update $A_{k+1} = R_k Q_k$.
3. Repeat until $A_k$ converges to an upper triangular matrix. The diagonal entries approximate the eigenvalues.

**Returns**: All eigenvalues of $A$.

---

### Summary

| **Method**                     | **Eigenvalue Returned**         |
|---------------------------------|----------------------------------|
| Power Method                   | Largest eigenvalue ($\lambda_{\text{max}}$) |
| Power Method with Shift        | Eigenvalue closest to $\sigma$ |
| Inverse Power Method           | Smallest eigenvalue ($\lambda_{\text{min}}$) |
| Inverse Power Method with Shift| Eigenvalue closest to $\sigma$ |
| QR Method                      | All eigenvalues ($\lambda_1, \lambda_2, \ldots, \lambda_n$) |


## Compilation and Usage

The application can be run using the **CMake framework**. At the root directory, `eigenvalue-problems`, follow these steps to build and run the application:

1. Use the **CMake** framework to configure and build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. The executable `main` is created in the `build/` folder.

3. Run the application using the following command:
    ```bash
    ./main <input_file.yaml>
    ```
    where `<input_file.yaml>` is the configuration file specifying the input, data type, method, and output options.

Alternatively, you can use the **CMake** interface on Visual Studio code to configure, build, and run the program. 

In addition, you can produce the executables for the tests by setting `"Activate tests" ON` in the `CMakeLists.txt` file at the root directory. Similarly, if documentation needs to be generated again, it can be done by setting `"Activate documentation" ON` in the same file.


### User input

The configuration file must be located in the `input/` directory, and you only need to provide the name of the file (not the full path) when running the program. An example of yaml config file is available in the folder `input/`. Below is a summary of the supported configuration options for **input**, **type**, **method**, and **output**.

#### Supported Input Types

| Option  | Description                                  |  `input_args`   |
|---------|----------------------------------------------|-------|
| `file`  | Load the matrix from a file in the `input/matrices/` directory | filename (without the path). Supported file extensions are: `.txt`, `.csv` and `.mtx` | 
| `function` | Generate the matrix using a mathematical function | Name of the function followed by the number of rows and then columns in `input_args`. Supported functions are: `hilbert` (Hilbert matrix), `identity` (Identity matrix). |

Example 1: Matrix is to be created from the file `A.txt`:

```yaml
input:
    type: file
    input_args: 
        - A.txt
```

Example 2: Hilbert matrix with 10 rows and columns is to be created from a function:

```yaml
input:
    type: function
    input_args: 
        - hilbert
        - 10
        - 10
```


#### Supported Types

| Option  | Description                                  |
|---------|----------------------------------------------|
| `int`   | Integer type for matrix elements.            |
| `float` | Floating point type for matrix elements.     |
| `double`| Double precision floating point type for matrix elements. |

#### Supported Methods

For a description of each method, see section on features. For the power method and the inverse power method, a shift can optionally be added.

| Option                             | `method_args`                                  |
|------------------------------------|----------------------------------------------|
| `power_method`                     | maximum number of iterations, tolerance. Optional: shift|
| `inverse_power_method`             | maximum number of iterations, tolerance. Optional: shift|
| `QR_method`                        | maximum number of iterations, tolerance|

Example 1: Use the inverse power method with a shif of 4 to find the smallest eigenvalue. Maximum number of iterations is set to 50000 and tolerance to 10e-6.

```yaml
name: inverse_power_method
    method_args: 
        - 50000
        - 10e-6
        - 4
```

#### Supported Output Types

| Option  | Description                                  |
|---------|----------------------------------------------|
| `print` | Print the results to the console. Do not provide any value in `output_args` (empty - element in the list)|
| `save`  | Save the results to a file in the `output/` directory. Provide the filename (without the path) in `output_args`. Supported file extensions is: `.txt`. Note: if the filename has an incorrect extension, the program saves the results to `output.txt`| 

Example 1: Print eigenvalues on terminal:

```yaml
output:
    type: print
    input_args: 
        - 
```

Example 2: Save eigenvalues in output.txt:

```yaml
output:
    type: save
    input_args: 
        - output.txt
```

### User output

The results of the computation are generated based on the output options specified in the YAML config file (see above).


## Program Flow

The UML diagram of the component of our project can be found in the next figure.

![Alt text](eigenvalue-probem_UML_v1.drawio.png?raw=true "Title")

TODO: Explain the implementation, how the class are linked and the different parts of the program


Note: More information about each function and class can be found in the documentation


## Tests

There are 3 executables used for testing the functionality of the application:

1. **user input parsing tests**: These tests validate the correctness of user input parsing and ensure the program handles invalid inputs properly (`tests/tests_user_input_parsing.cpp`)

2. **matrix generation tests**: These tests ensure that matrices can be generated correctly from functions (e.g., identity, Hilbert) and files (`tests/tests_matrix_generation.cpp`)

3. **solver tests**: TODO (`tests/tests_solver_methods.cpp`)


## Limitations and TODOs

The program is currently limited to square matrices. However, it can be later extended with other methods to compute singular values of rectangular matrices.


## Authors and Acknowledgement

Authors:
- Julie Charlet, MSc in Computational Science and Engineering at EPFL
- Mathilde Simoni  MSc in Computational Science and Engineering at EPFL

We thank the professor Guillaume Anciaux and the TA Gal Pascual for helping during class and the exercise sessions.