#include <pybind11/pybind11.h>

#include "brain.h"

namespace py = pybind11;

PYBIND11_MODULE(brainiac, m) {
    /*py::class_<brainiac::Brain>(m, "brain")
        .def_static("instance", &brainiac::Brain::Instance)
        .def("start", &brainiac::Brain::Start);*/

    /*    py::class_<brainiac::Brain>(m, "brain")
        .def_static("instance", [](py::object) { return brainiac::Brain::Instance(); )},
        py::return_value_policy::reference_internal);*/

    py::class_<brainiac::Brain, std::unique_ptr<brainiac::Brain, py::nodelete>>(m, "brain")
        .def(py::init([](){ return std::unique_ptr<brainiac::Brain, py::nodelete>(&brainiac::Brain::Instance()); }))        .def("start", &brainiac::Brain::Start);
}
