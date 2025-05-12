/**
 * \file grow_board.h
 * \brief Corner prediction and board growth utilities for cbdetect.
 *
 * Combines the original grow_board declaration with additional helper
 * functions for predicting and assigning chessboard corners as well as
 * utilities to enlarge the current board model.  The interface is kept
 * header‑only so that downstream projects only need to include this file
 * together with <opencv2/core.hpp> and cbdetect/config.h.
 *
 * Copyright 2012 Andreas Geiger (KIT)
 *           2018 ftdlyc <yclu.cn@gmail.com>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef LIBCBDETECT_GROW_BOARD_H
#define LIBCBDETECT_GROW_BOARD_H

#include <vector>
#include <opencv2/core.hpp>   // cv::Point2d, cv::Point2i

#include "config.h"          // Corner, Board, Params (algorithm configuration)

namespace cbdetect {

// ---------------------------------------------------------------------------
// Type definitions (moved here from the original grow_board header)
// ---------------------------------------------------------------------------

/**
 * @enum GrowType
 * @brief Result category returned by grow_board().
 */
enum GrowType : int {
  GrowType_Failure  = 0,  //!< No valid extension found.
  GrowType_Inside   = 1,  //!< Board grew by extending an internal row/column.
  GrowType_Boundary = 2   //!< Board grew by adding a new boundary row/column.
};

// Forward declarations for the core data structures that live in config.h.
// This lets users include only this header and config.h in any order.
struct Corner;  //!< Set of detected chessboard corners.
struct Board;   //!< Current board hypothesis (index, energy, dims, etc.).
struct Params;  //!< Tunable parameters for the cbdetect algorithm.

// ---------------------------------------------------------------------------
// Corner prediction helpers
// ---------------------------------------------------------------------------

/**
 * @brief Predict new chessboard corners by linear or replica prediction.
 *
 * The predictor operates on three predecessor indices (p1–p3) per sequence.
 * If @p p1 is empty, only @p p2 and @p p3 are used for two‑point
 * extrapolation.  The returned vector is always the same length as @p p2.
 *
 * @param corners  The detected corner set (input only).
 * @param p1       Indices of first previous corners (optional).
 * @param p2       Indices of second previous corners.
 * @param p3       Indices of third previous corners.
 * @return         Predicted 2‑D positions for each sequence.
 */
std::vector<cv::Point2d> predict_corners(const Corner&           corners,
                                         const std::vector<int>& p1,
                                         const std::vector<int>& p2,
                                         const std::vector<int>& p3);

/**
 * @brief Assign predicted positions to the nearest unused detected corner.
 *
 * Each prediction is matched via nearest‑neighbour search in image space.
 * If no suitable corner is found within the distance threshold defined by
 * @p params (see @c Params::max_dist), the entry is set to -2.
 *
 * @param corners  Detected corner list.
 * @param used     Vector indicating whether each corner index is already
 *                 used inside the current board (modified in‑place).
 * @param p1       Indices of first previous corners (optional).
 * @param p2       Indices of second previous corners.
 * @param p3       Indices of third previous corners.
 * @return         Corner indices corresponding to the predictions.
 */
std::vector<int> predict_board_corners(const Corner&       corners,
                                       std::vector<int>&   used,
                                       std::vector<int>&   p1,
                                       std::vector<int>&   p2,
                                       std::vector<int>&   p3);

// ---------------------------------------------------------------------------
// Board manipulation helpers
// ---------------------------------------------------------------------------

/**
 * @brief Extend a board model by adding a boundary row or column.
 *
 * The board's index (@c Board::idx) and energy (@c Board::E) matrices are
 * enlarged by one row/column while keeping the existing data aligned.
 *
 * @param board      The board model to expand.
 * @param direction  The side to grow: 0 = top, 1 = left, 2 = bottom, 3 = right.
 * @return           True if any active corners were already on the boundary.
 */
bool add_board_boundary(Board& board,
                        int     direction);

/**
 * @brief Attempt to grow a board in the specified direction.
 *
 * Depending on the @p direction flag, either internal rows/columns are
 * replicated (inside growth) or a new boundary row/column is appended
 * (boundary growth).  The function updates @p board and @p used in‑place
 * and outputs a vector of new board coordinates in @p proposal.
 *
 * @param corners    Detected corners (input).
 * @param used       Flags that mark whether each corner is already used.
 * @param board      Current board model (modified).
 * @param proposal   Proposed board positions added during this call.
 * @param direction  0 = top, 1 = left, 2 = bottom, 3 = right.
 * @param params     Algorithm parameters (see @c Params).
 * @return           A GrowType value indicating success or failure.
 */
GrowType grow_board(const Corner&               corners,
                    std::vector<int>&           used,
                    Board&                      board,
                    std::vector<cv::Point2i>&   proposal,
                    int                         direction,
                    const Params&               params);

} // namespace cbdetect

#endif // LIBCBDETECT_GROW_BOARD_H
