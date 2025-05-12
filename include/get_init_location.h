#pragma once
#ifndef LIBCBDETECT_GET_INIT_LOCATION_H
#define LIBCBDETECT_GET_INIT_LOCATION_H

#include "config.h"    // for Corner, Params, DetectMethod
#include <opencv2/core.hpp>         // for cv::Mat, cv::Size

namespace cbdetect {

/**
 * Compute the Hessian corner response for each pixel via second derivatives.
 *
 * @param img_in   Input image (CV_64F) to compute response on.
 * @param img_out  Output Hessian response image (CV_64F).
 */
void hessian_response(const cv::Mat& img_in,
                      cv::Mat&       img_out);

/**
 * Rotate an image by a given angle, optionally specifying output size.
 *
 * @param img_in    Input image (any CV type supporting warpAffine).
 * @param angle     Rotation angle in radians.
 * @param img_out   Output rotated image.
 * @param out_size  Desired output image size; if non-positive, computed automatically.
 */
void rotate_image(const cv::Mat& img_in,
                  double          angle,
                  cv::Mat&        img_out,
                  cv::Size        out_size = cv::Size());

/**
 * Perform a localized Radon transform-based corner response.
 *
 * @param img_in   Input image (CV_64F).
 * @param img_out  Output response image (CV_64F).
 */
void localized_radon_transform(const cv::Mat& img_in,
                               cv::Mat&       img_out);

/**
 * Initialize corner locations by template matching, Hessian response, or localized Radon.
 *
 * @param img      Normalized grayscale image (CV_64F).
 * @param img_du   x-derivative image (CV_64F).
 * @param img_dv   y-derivative image (CV_64F).
 * @param corners  Output Corner container to fill initial locations.
 * @param params   Detection parameters (radius, thresholds, method).
 */
void get_init_location(const cv::Mat& img,
                       const cv::Mat& img_du,
                       const cv::Mat& img_dv,
                       Corner&        corners,
                       const Params&  params);

} // namespace cbdetect

#endif // LIBCBDETECT_GET_INIT_LOCATION_H

