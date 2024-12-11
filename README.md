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
- [References] (#references)


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
The application provides **three numerical methods** for finding eigenvalues.

### 1. **Power Method**
The **Power Method** iteratively finds the **the largest eigenvalue** (in absolute norm) $\lambda_{\text{max}}$. This method assumes that $A$
has a distinct dominant eigenvalue. Optionally, a shift $\mu$ can be chosen to speed up convergence. In this case, the algorithms finds the dominant eigenvalue $\lambda_{\text{mu, max}}$ of $(A - \mu I)$, where $I$ is the identity matrix. The algorithm returns $\lambda = \lambda_{\text{mu, max}} + \mu$.

**Algorithm**:
1. Start with an arbitrary non-zero vector $\mathbf{v}_0$.
2. Compute $\mathbf{v}_{k+1} = (A - \mu I) \mathbf{v}_k$ and normalize it.
3. Approximate the eigenvalue using Rayleigh quotient: $\lambda_k = \frac{\mathbf{v}_k^\top (A - \mu I) \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.
4. Repeat until the stopping criterion $\frac{|\lambda_k - \lambda_{k-1}|}{\lambda_k} < \text{tol}$ is met.

**Returns**: The eigenvalue $\lambda_{\text{max}}$.

---

### 2. **Inverse Power Method**
The **Inverse Power Method** computes the **smallest eigenvalue** $\lambda_{\text{min}}$ by working with the inverse of $A$. Optionally, a shift $\mu$ can be specified when an approximation of the eigenvalue is known. In this case, the algorithm computes the eigenvalue of $(A - \mu I)$ and returns $\lambda = \lambda_{\text{mu, max}} + \mu$, which is the eigenvalue closest to the specified shift $\mu$.

**Algorithm**:
1. Solve $(A - \mu I) \mathbf{w} = \mathbf{v}_k$ (i.e. compute $\mathbf{w} = (A - \mu I)^{-1} \mathbf{v}_k$).
2. Set $\mathbf{v}_{k+1} = \mathbf{w} / \|\mathbf{w}\|$.
3. Approximate the eigenvalue using Rayleigh quotient: $\lambda_k = \frac{\mathbf{v}_k^\top (A - \mu I) \mathbf{v}_k}{\mathbf{v}_k^\top \mathbf{v}_k}$.
4. Repeat until the stopping criterion $\frac{|\lambda_k - \lambda_{k-1}|}{\lambda_k} < \text{tol}$ is met.

**Returns**: The eigenvalue $\lambda_{\text{min}}$.

---

### 3. **QR Method**
The **QR Method** iteratively finds all eigenvalues of the matrix $A$. It is based on the QR decomposition of $A$.

**Algorithm**:
1. Decompose $A_k = Q_k R_k$, where $Q_k$ is orthogonal and $R_k$ is upper triangular.
2. Update $A_{k+1} = R_k Q_k$.
3. Repeat until $A_k$ converges to an upper triangular matrix. The diagonal entries approximate the eigenvalues.

**Returns**: All eigenvalues of $A$.

#### 3.1 QR Decomposition
The QR method for finding eigenvalues relies on the QR decomposition of $A$. Householder's method is reliable algorithm for computing $Q$ and $R$, given $A \in \mathbb{R}^{n \times m}$, with $n \geq m$. It relies on the Householder transformation. Let $w \in \mathbb{R}^n$ with $w^T w = 1$. The $n \times n$ matrix

$  P = I - 2 w w^T $

is the Householder transformation. This projection matrix is used to consecutively orthogonalize columns of A against previously processed columns, until A has all orthogonal columns. At each step, the norm of the processed column is stored in the diagonal of the upper-triangular matrix $R$, and the difference between the orthogonalized vector and the processed columns is store in the upper triangle of $R$.

**Algorithm**:
1. Initialize:
- Set $Q$ to the identity matrix of size $n$: $Q=In$​.
- Set $R$ to the input matrix $A$: $R=A$.
2. Iterate over columns $k$ of $R$ (from 0 to $n−1$):
- Extract the subvector $x$ from the $k$-th column of $R$, starting from the kk-th row: $x = R[k:n,k]$.
- Initialize $v=x$, then modify the first entry of $v$ to include the Householder term:
- $v_0=v_0+\text{sign}(x_0)\times∣∣x∣∣$.
- Normalize $v$
3. Apply Householder transformation:
- Update the trailing submatrix of $R$ (from $k$-th row and column onward):
- $R[k:n,k:n]=R[k:n,k:n]−2⋅v⋅(v^T R[k:n,k:n])$.
- Update the corresponding block of $Q$:
- $Q[:,k:n]=Q[:,k:n]−2⋅(Q[:,k:n]⋅v)⋅v^T$.
4. Repeat until all columns $k$ are processed.
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
| `power_method`                     | tolerance, maximum number of iterations, shift|
| `inverse_power_method`             | tolerance, maximum number of iterations, shift|
| `QR_method`                        | maximum number of iterations, tolerance|

In the case where no `method_args` are provided, or if some are missing, default values are applied. Those default values are.

| Argument                           | Default value  |
|------------------------------------|----------------|
| tolerance                          |$10^{-6}$       |
| maximum number of iterations       |10000           |
| shift                              |0.0             |

Example 1: Use the inverse power method with a shif of 1.2 to find the eigenvalue closest to that. Maximum number of iterations is set to 50000 and tolerance to 10e-6.

```yaml
name: inverse_power_method
    method_args: 
        - 50000
        - 10e-6
        - 1.2
```

Example 2: The power method will be run with the default values of tolerance of $10^{-6}$, maximum number of iteration of 10000 and no shift 
as no `method_args` are secified.

```yaml
name: power_method
    method_args: 
        - 
        -
        - 
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

![Alt text](doc/UML_final.drawio.png?raw=true "Title")

The program flow is divided in three main parts:
1. Process user input
2. Solve eigenvalue problem
2. Output result

User input is done through a _yaml_ config file. The user can choose whether to pass a file containing the matrix (in either txt, mtx or csv format) or to specify the name and size of a predefined matrix from a given function. For now the matrix from functions implemented are the identity and the Hilbert matrices.

The config file is first parsed in the file `main.cpp`. Based on the user arguments, a factory class `MatrixGeneratorFactory` will instantiate the correct child class, derived from the abstract `MatrixGenerator`class. The `generate_matrix` method of the children of this class return a pointer to matrix $A$ in the main flow.

Then, based on user input, the class `SolverFactory` instantiate the desired solver class, which is a child of the abstract class `AbstractIterativeSolver`, with either specified or default method arguments (_tolerance_, _maxIter_ and _shift_)

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

## References

1. Andrilli, S. & Hecker, D. (1993) Elementary linear algebra. [International student ed.]. Boston: PWS-KENT.
2. Burden, R. L. & Faires, J. D. (1989) Numerical analysis. 4th ed. Boston: PWS-KENT.
3. Dede, L. (2015) Numerical analysis and computational mathematics. Class notes for EPFL's course MATH-456 thaught by Laura Grigori.
4. Grigori, L. (2023) Class notes of EPFL's course MATH-505: HPC for numerical methods and data analysis.


