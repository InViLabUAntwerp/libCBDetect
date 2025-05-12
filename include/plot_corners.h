#pragma once
#ifndef LIBCBDETECT_PLOT_CORNERS_H
#define LIBCBDETECT_PLOT_CORNERS_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat, cv::Point2d
#include "config.h" // for Corner

namespace cbdetect {

    /**
     * Overlay detected corner points on an image and display it.
     *
     * @param img      Input image (grayscale or color).
     * @param corners  List of 2D corner locations.
     * @param title    Window title for display.
     */
    void plot_corners(const cv::Mat& img,
                      const std::vector<cv::Point2d>& corners,
                      const char* title);

    /**
     * Overlay corner orientations and indices on an image and display it.
     *
     * @param img      Input image (grayscale or color).
     * @param corners  Corner data including positions and direction vectors.
     */
    void plot_corners(const cv::Mat& img,
                      const Corner& corners);

} // namespace cbdetect

#endif // LIBCBDETECT_PLOT_CORNERS_H
