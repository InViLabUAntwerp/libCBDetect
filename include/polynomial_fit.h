#pragma once
#ifndef LIBCBDETECT_POLYNOMIAL_FIT_H
#define LIBCBDETECT_POLYNOMIAL_FIT_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat, cv::Point2d
#include "config.h" // for Corner, Params

namespace cbdetect {

/**
 * Build a Gaussian smoothing kernel.
 *
 * @param kernel  Output square kernel (CV_64F).
 * @param sigma   Gaussian standard deviation.
 */
void create_gaussin_filter_kernel(cv::Mat& kernel,
                                  double sigma);

/**
 * Build a conical smoothing kernel.
 *
 * @param kernel  Output square kernel (CV_64F).
 * @param r       Radius of the cone filter.
 * @return        Number of zero-valued entries in the kernel.
 */
int create_cone_filter_kernel(cv::Mat& kernel,
                              int r);

/**
 * Fit a quadratic surface to grayscale intensities and refine corner locations
 * assuming a saddle point shape.
 *
 * @param img      Smoothed input image (CV_64F).
 * @param r        Half-kernel size for fitting region.
 * @param corners  Corner container to refine (positions updated in-place).
 */
void polynomial_fit_saddle(const cv::Mat& img,
                           int r,
                           Corner& corners);

/**
 * Fit a cubic surface to grayscale intensities and refine corner locations
 * assuming a monkey-saddle point shape.
 *
 * @param img      Smoothed input image (CV_64F).
 * @param r        Half-kernel size for fitting region.
 * @param corners  Corner container to refine (positions updated in-place).
 */
void polynomial_fit_monkey_saddle(const cv::Mat& img,
                                  int r,
                                  Corner& corners);

/**
 * Dispatch to the appropriate polynomial fit based on corner type.
 *
 * @param img      Input image (after normalization).
 * @param corners  Corner container to refine.
 * @param params   Detection parameters (corner_type, kernel sizes).
 */
void polynomial_fit(const cv::Mat& img,
                    Corner&        corners,
                    const Params&  params);

} // namespace cbdetect

#endif // LIBCBDETECT_POLYNOMIAL_FIT_H