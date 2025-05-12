#pragma once
#ifndef LIBCBDETECT_FILTER_CORNERS_H
#define LIBCBDETECT_FILTER_CORNERS_H

#include <opencv2/core.hpp>    // for cv::Mat
#include "config.h" // for Corner, Params

namespace cbdetect {

    /**
     * Filter corner candidates by zero-crossings and orientation modes.
     *
     * @param img        Normalized grayscale image (CV_64F).
     * @param img_angle  Gradient angle map (CV_64F).
     * @param img_weight Gradient magnitude/weight map (CV_64F).
     * @param corners    Corner container with positions, radii, etc.; filtered in place.
     * @param params     Detection parameters (corner type, thresholds, etc.).
     */
    void filter_corners(const cv::Mat& img,
                        const cv::Mat& img_angle,
                        const cv::Mat& img_weight,
                        Corner&        corners,
                        const Params&  params);

} // namespace cbdetect

#endif // LIBCBDETECT_FILTER_CORNERS_H
