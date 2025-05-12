#pragma once
#ifndef LIBCBDETECT_INIT_BOARD_H
#define LIBCBDETECT_INIT_BOARD_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Point2d
#include "config.h" // for Corner, Board

namespace cbdetect {

    /**
     * Find the best neighboring corner in a specified direction.
     *
     * @param corners   Detected corners with positions.
     * @param used      Flags per corner index (skips used corners).
     * @param idx       Index of reference corner in corners.p.
     * @param v         Unit direction vector to search along.
     * @param min_dist  Output minimal distance metric found.
     * @return          Index of the best neighbor in corners.p.
     */
    int directional_neighbor(const Corner&            corners,
                             const std::vector<int>&  used,
                             int                      idx,
                             const cv::Point2d&       v,
                             double&                  min_dist);

    /**
     * Initialize a 3×3 chessboard hypothesis from detected corners.
     *
     * @param corners  Detected corners with positions and orientations.
     * @param used     Flags marking used corner indices (modified in place).
     * @param board    Output Board model; index map becomes 3×3 on success.
     * @param idx      Index of the central corner to seed the board.
     * @return         True if a valid initial board was found; false otherwise.
     */
    bool init_board(const Corner&         corners,
                    std::vector<int>&     used,
                    Board&                board,
                    int                   idx);

} // namespace cbdetect

#endif // LIBCBDETECT_INIT_BOARD_H