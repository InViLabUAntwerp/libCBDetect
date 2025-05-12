#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "Checkerboard.cpp"

namespace py = pybind11;
using arrayd = py::array_t<double, py::array::c_style | py::array::forcecast>;

static void array_to_image(Checkerboard &cb, arrayd a, int h, int w) {
    auto b = a.request();
    cb.array_to_image(static_cast<int>(b.size), static_cast<double *>(b.ptr), h, w);
}

static void array_norm_to_image(Checkerboard &cb, arrayd a, int h, int w) {
    auto b = a.request();
    cb.array_norm_to_image(static_cast<int>(b.size), static_cast<double *>(b.ptr), h, w);
}

static void get_corners(Checkerboard &cb, arrayd u, arrayd v) {
    auto bu = u.request(), bv = v.request();
    if (bu.size != bv.size) throw std::runtime_error("u and v must have same length");
    cb.GetCorners(static_cast<int>(bu.size), static_cast<double *>(bu.ptr),
                  static_cast<int>(bv.size), static_cast<double *>(bv.ptr));
}

static void get_board_corners(Checkerboard &cb, arrayd u, arrayd v) {
    auto bu = u.request(), bv = v.request();
    if (bu.size != bv.size) throw std::runtime_error("u and v must have same length");
    cb.GetBoardCorners(static_cast<int>(bu.size), static_cast<double *>(bu.ptr),
                       static_cast<int>(bv.size), static_cast<double *>(bv.ptr));
}

static void get_direction_u(Checkerboard &cb, arrayd u, arrayd v) {
    auto bu = u.request(), bv = v.request();
    if (bu.size != bv.size) throw std::runtime_error("u and v must have same length");
    cb.GetDirection_U(static_cast<int>(bu.size), static_cast<double *>(bu.ptr),
                      static_cast<int>(bv.size), static_cast<double *>(bv.ptr));
}

static void get_direction_v(Checkerboard &cb, arrayd u, arrayd v) {
    auto bu = u.request(), bv = v.request();
    if (bu.size != bv.size) throw std::runtime_error("u and v must have same length");
    cb.GetDirection_V(static_cast<int>(bu.size), static_cast<double *>(bu.ptr),
                      static_cast<int>(bv.size), static_cast<double *>(bv.ptr));
}

static void get_score(Checkerboard &cb, arrayd s) {
    auto bs = s.request();
    cb.GetScore(static_cast<int>(bs.size), static_cast<double *>(bs.ptr));
}

PYBIND11_MODULE(Checkerboard, m) {
    m.doc() = "C++ Checkerboard detector wrapped with pybind11";

    py::class_<Checkerboard>(m, "Checkerboard")
        .def(py::init<>())

        .def("array_to_image",        &array_to_image,
             py::arg("image"), py::arg("height"), py::arg("width"))
        .def("array_norm_to_image",   &array_norm_to_image,
             py::arg("image"), py::arg("height"), py::arg("width"))
        .def("load_image",            &Checkerboard::load_image,
             py::arg("filename"))
        .def("find_corners",          &Checkerboard::find_corners)
        .def("find_board_from_corners", &Checkerboard::find_board_from_corners)
        .def("refine_corners",        &Checkerboard::refine_corners)
        .def("plot_corners",          &Checkerboard::plot_corners)
        .def("plot_boards",           &Checkerboard::plot_boards)

        .def("get_corners",           &get_corners,           py::arg("u"), py::arg("v"))
        .def("get_board_corners",     &get_board_corners,     py::arg("u"), py::arg("v"))
        .def("get_direction_u",       &get_direction_u,       py::arg("u"), py::arg("v"))
        .def("get_direction_v",       &get_direction_v,       py::arg("u"), py::arg("v"))
        .def("get_score",             &get_score,             py::arg("score"))

        .def_readwrite("rows",                        &Checkerboard::rows)
        .def_readwrite("cols",                        &Checkerboard::cols)
        .def_readwrite("number_of_boards",            &Checkerboard::number_of_boards)
        .def_readwrite("number_of_corners",           &Checkerboard::number_of_corners)
        .def_readwrite("show_processing",             &Checkerboard::show_processing)
        .def_readwrite("show_debug_image",            &Checkerboard::show_debug_image)
        .def_readwrite("show_grow_processing",        &Checkerboard::show_grow_processing)
        .def_readwrite("norm",                        &Checkerboard::norm)
        .def_readwrite("polynomial_fit",              &Checkerboard::polynomial_fit)
        .def_readwrite("norm_half_kernel_size",       &Checkerboard::norm_half_kernel_size)
        .def_readwrite("polynomial_fit_half_kernel_size",
                                                  &Checkerboard::polynomial_fit_half_kernel_size)
        .def_readwrite("init_loc_thr",                &Checkerboard::init_loc_thr)
        .def_readwrite("score_thr",                   &Checkerboard::score_thr)
        .def_readwrite("strict_grow",                 &Checkerboard::strict_grow)
        .def_readwrite("overlay",                     &Checkerboard::overlay)
        .def_readwrite("occlusion",                   &Checkerboard::occlusion);
}

