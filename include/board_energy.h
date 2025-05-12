#pragma once
#ifndef LIBCBDETECT_BOARD_ENERGY_H
#define LIBCBDETECT_BOARD_ENERGY_H

#include "config.h"    // for Corner, Board, Params
#include <opencv2/core.hpp>        // for cv::Point3i

namespace cbdetect {

    /**
     * Compute the energy-minimizing 3D board pose from detected corners.
     *
     * @param corners  Detected corner observations.
     * @param board    Board model to be updated.
     * @param params   Algorithm parameters.
     * @return         Optimal board pose as an integer 3D point.
     */
    cv::Point3i board_energy(const Corner& corners,
                             Board& board,
                             const Params& params);

} // namespace cbdetect

#endif // LIBCBDETECT_BOARD_ENERGY_H
