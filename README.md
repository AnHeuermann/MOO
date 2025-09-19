# **MOO: Modelica / Model Optimizer - A Generic Framework for Dynamic Optimization**

This is **MOO: Modelica / Model Optimizer v.0.1.0**, a flexible and extensible
framework for solving optimization problems. **MOO** provides a generic
Nonlinear Programming (NLP) layer with built-in scaling support and a generic
NLP solver interface. While primarily designed for dynamic optimization in the
Modelica ecosystem (General Dynamic Optimization Problems - GDOPs, training of
Physics-enhanced Neural ODEs - PeN-ODEs), it is equally applicable to other
domains, e.g. model predictive control (MPC).

## Working with this repository

Clone with submodules:

```bash
git clone --recurse-submodules git@github.com:AMIT-HSBI/MOO.git
```

## Compilation

**MOO** uses CMake to compile.

### Dependencies

Install with your favorit package manager

- metis

  - Debian / Ubuntu `apt install metis`

- LAPACK

  - Debian / Ubuntu `apt install libblas-dev liblapack-dev gfortran`


### Configure

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
```

Possible configuration arguments:

- `MOO_METIS_LIB`: Location of metis
- `MOO_LAPACK_LIB`: Location of LAPACK
- `MOO_GFORTRAN_LIB`: Location of GNU Fortran

### Build

```bash
cmake --build build --parallel <Nr. of cores> --target all
```

### Test

Add `-DMOO_WITH_GDOPT_EXAMPLE=ON` to the configuration step.

## License

The **Modelica/Model Optimizer (MOO)** is distributed under the **GNU Lesser
General Public License (LGPL) Version 3**. See the full license text for
detailed terms and conditions:
[LGPL-3.0](https://www.gnu.org/licenses/lgpl-3.0.html)
