#pragma once
#ifndef LIBCBDETECT_NON_MAXIMUM_SUPPRESSION_H
#define LIBCBDETECT_NON_MAXIMUM_SUPPRESSION_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat, cv::Size

#include "config.h"

namespace cbdetect {

    /**
     * Perform non-maximum suppression on a dense response image.
     *
     * @param img     Input response image (CV_64F).
     * @param n       Neighborhood half-size (defines window of size (n+1)x(n+1)).
     * @param tau     Threshold for corner response.
     * @param margin  Margin to ignore image borders.
     * @param corners Output Corner container (positions and radii will be populated).
     */
    void non_maximum_suppression(const cv::Mat& img,
                                 int n,
                                 double tau,
                                 int margin,
                                 Corner& corners);

    /**
     * Perform non-maximum suppression on a sparse set of corner candidates.
     *
     * @param corners  Input/output Corner container (scores and positions).
     * @param n        Neighborhood half-size for suppression.
     * @param img_size Size of the original image.
     * @param params   Detection parameters (corner_type, etc.).
     */
    void non_maximum_suppression_sparse(Corner& corners,
                                        int n,
                                        cv::Size img_size,
                                        const Params& params);

} // namespace cbdetect

#endif // LIBCBDETECT_NON_MAXIMUM_SUPPRESSION_H
