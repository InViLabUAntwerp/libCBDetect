/**
* Copyright 2018, ftdlyc <yclu.cn@gmail.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef LIBCBDETECT_PLOT_BOARDS_H
#define LIBCBDETECT_PLOT_BOARDS_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat, cv::Point2d
#include "config.h" // for Corner, Board, Params

namespace cbdetect {

    /**
     * Draw detected chessboard boards on an image and display it.
     *
     * @param img      Input image (grayscale or color).
     * @param corners  Detected corner positions.
     * @param boards   List of Board models with index maps.
     * @param params   Drawing parameters (e.g., corner type).
     */
    void plot_boards(const cv::Mat& img,
                     const Corner& corners,
                     const std::vector<Board>& boards,
                     const Params& params);

} // namespace cbdetect

#endif // LIBCBDETECT_PLOT_BOARDS_H


