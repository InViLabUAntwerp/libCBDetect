#pragma once
#ifndef LIBCBDETECT_FIND_CORNERS_H
#define LIBCBDETECT_FIND_CORNERS_H

#include "config.h"    // for Corner, Params
#include <opencv2/core.hpp>        // for cv::Mat

namespace cbdetect {

    /**
     * Detect and merge corner candidates at sub- and full-resolution.
     *
     * @param img      Input image (grayscale or color).
     * @param corners  Output corner container to fill/merge.
     * @param params   Detection parameters.
     */
    void find_corners(const cv::Mat& img,
                      Corner&      corners,
                      const Params& params);

    /**
     * Refine corner locations to subpixel accuracy.
     *
     * @param img      Input image (grayscale or color).
     * @param corners  Corner container with initial locations.
     * @param params   Refinement parameters.
     */
    void find_subpixel_corners(const cv::Mat& img,
                               Corner&      corners,
                               const Params& params);

    /**
     * Detect corners on a resized image and merge them back.
     *
     * @param img      Input image.
     * @param corners  Corner container to merge results into.
     * @param params   Detection parameters.
     */
    void find_corners_resized(const cv::Mat& img,
                              Corner&      corners,
                              const Params& params);

} // namespace cbdetect

#endif // LIBCBDETECT_FIND_CORNERS_H
