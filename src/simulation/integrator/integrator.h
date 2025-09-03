// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This file is part of MOO - Modelica / Model Optimizer
// Copyright (C) 2025 University of Applied Sciences and Arts
// Bielefeld, Faculty of Engineering and Mathematics
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef MOO_INTEGRATOR_H
#define MOO_INTEGRATOR_H

#include <base/util.h>
#include <base/fixed_vector.h>
#include <base/trajectory.h>

namespace Simulation {

enum class JacobianFormat {
    DENSE,
    COO,
    CSC
};

using ODEFunction = std::function<void(f64 t, const f64* x, const f64* u, const f64* p, const f64* w, f64* dxdt, void* user_data)>;
using JacobianFunction = std::function<void(f64 t, const f64* x, const f64* u, const f64* p, const f64* w, f64* J, void* user_data)>;

class Integrator {
public:
    Integrator(ODEFunction ode_fn,
               std::vector<f64> dense_output_grid,
               f64* x_start_values,
               int x_size,
               void* user_data,
               f64* parameters,
               int p_size,
               ControlTrajectory* controls,
               ControlTrajectory* data,
               JacobianFunction jac_fn,
               JacobianFormat jfmt,
               int* row,
               int* col,
               int nnz);

    virtual ~Integrator() = default;

    std::unique_ptr<Trajectory> simulate();

    void get_ode(f64 t, f64* x, f64* out);
    void get_dense_jacobian(f64 t, f64* x, f64* out);
    // f64* get_sparse_jacobian(f64 t, f64* x);

    ODEFunction ode_func;
    JacobianFunction jac_func;

    std::vector<f64> dense_output_grid;

    std::unique_ptr<Trajectory> output;

    f64* x_start_values;

    void set_controls_only(f64 t);

    FixedVector<f64> u;
    FixedVector<f64> w;

    int x_size;
    int u_size;
    int w_size;
    int p_size;

private:
    virtual int internal_simulate() = 0;

    void set_inputs(f64 t);

    void* user_data;

    JacobianFormat jac_fmt;

    ControlTrajectory* internal_controls;
    ControlTrajectory* internal_data;
    f64* parameters;

    f64 last_t;

    FixedVector<f64> sparse_jac;
    int* i_row;
    int* j_col;
    int nnz;
};

} // namespace Simulation

#endif // MOO_INTEGRATOR_H
