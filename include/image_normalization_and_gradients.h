#pragma once
#ifndef LIBCBDETECT_IMAGE_NORMALIZATION_AND_GRADIENTS_H
#define LIBCBDETECT_IMAGE_NORMALIZATION_AND_GRADIENTS_H

#include "config.h"   // for Params
#include <opencv2/core.hpp>        // for cv::Mat

namespace cbdetect {

    /**
     * Perform a box (mean) filter on an image.
     *
     * @param img             Input image (CV_64F).
     * @param blur_img        Output blurred image (CV_64F).
     * @param kernel_size_x   Horizontal half-window size.
     * @param kernel_size_y   Vertical half-window size (if negative, equals kernel_size_x).
     */
    void box_filter(const cv::Mat& img,
                    cv::Mat&       blur_img,
                    int            kernel_size_x,
                    int            kernel_size_y = -1);

    /**
     * Normalize an image and compute its gradients, orientations, and weight map.
     *
     * @param img         Input/output image (CV_64F); normalized in-place.
     * @param img_du      Output x-derivative (CV_64F).
     * @param img_dv      Output y-derivative (CV_64F).
     * @param img_angle   Output gradient angle map (CV_64F, range [0, PI)).
     * @param img_weight  Output gradient magnitude map (CV_64F).
     * @param params      Normalization parameters (norm flag, kernel size, etc.).
     */
    void image_normalization_and_gradients(cv::Mat&       img,
                                          cv::Mat&       img_du,
                                          cv::Mat&       img_dv,
                                          cv::Mat&       img_angle,
                                          cv::Mat&       img_weight,
                                          const Params&  params);

} // namespace cbdetect

#endif // LIBCBDETECT_IMAGE_NORMALIZATION_AND_GRADIENTS_H

