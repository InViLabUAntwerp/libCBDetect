#pragma once
#ifndef LIBCBDETECT_FILTER_BOARD_H
#define LIBCBDETECT_FILTER_BOARD_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Point2i
#include "config.h" // for Board, Corner, Params

namespace cbdetect {

    /**
     * Find the minimum neighboring energy for a given board position.
     *
     * @param board  Board energy map.
     * @param p      2D board coordinate.
     * @return       Minimum energy among adjacent entries.
     */
    double find_minE(const Board& board,
                     const cv::Point2i& p);

    /**
     * Iteratively remove the worst-fitting corners from a board proposal
     * until energy no longer improves or no proposals remain.
     *
     * @param corners   Original detected corners.
     * @param used      Boolean flags per corner index (to mark removals).
     * @param board     Board model with energy and index maps.
     * @param proposal  List of current board corner proposals.
     * @param energy    Current best energy (updated on success).
     * @param params    Algorithm parameters.
     */
    void filter_board(const Corner&               corners,
                      std::vector<int>&           used,
                      Board&                      board,
                      std::vector<cv::Point2i>&   proposal,
                      double&                     energy,
                      const Params&               params);

} // namespace cbdetect

#endif // LIBCBDETECT_FILTER_BOARD_H
