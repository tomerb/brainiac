#include <pybind11/pybind11.h>

#include "brain.h"

namespace py = pybind11;

PYBIND11_MODULE(brainiac, m) {
    py::class_<brainiac::Brain, std::unique_ptr<brainiac::Brain, py::nodelete>>(m, "brain")
        .def_static("instance",
                    &brainiac::Brain::Instance,
                    py::return_value_policy::reference)
        .def("start", &brainiac::Brain::Start)
        .def("stop", &brainiac::Brain::Stop);
}
