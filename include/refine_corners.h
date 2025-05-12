#pragma once
#ifndef LIBCBDETECT_REFINE_CORNERS_H
#define LIBCBDETECT_REFINE_CORNERS_H

#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat, cv::Point2d
#include "config.h" // for Corner, Params

namespace cbdetect {

/**
 * Estimate two dominant edge orientations around corners using gradient histograms.
 *
 * @param img_angle   Gradient angle map (CV_64F) around the corner.
 * @param img_weight  Gradient magnitude map (CV_64F) around the corner.
 * @return            A 2×2 matrix of edge direction unit vectors, or empty if invalid.
 */
std::vector<std::vector<double>> edge_orientations(cv::Mat& img_angle,
                                                   cv::Mat& img_weight);

/**
 * Estimate three dominant edge orientations around corners (Monkey Saddle case).
 *
 * @param img_angle   Gradient angle map (CV_64F) around the corner.
 * @param img_weight  Gradient magnitude map (CV_64F) around the corner.
 * @return            A 3×2 matrix of edge direction unit vectors, or empty if invalid.
 */
std::vector<std::vector<double>> edge_3_orientations(cv::Mat& img_angle,
                                                     cv::Mat& img_weight);

/**
 * Refine corner positions and orientations to subpixel accuracy via gradient-based fitting.
 *
 * @param img_du     x-derivative image (CV_64F).
 * @param img_dv     y-derivative image (CV_64F).
 * @param img_angle  Gradient angle map (CV_64F).
 * @param img_weight Gradient magnitude map (CV_64F).
 * @param corners    Corner container with initial positions and radii (updated in-place).
 * @param params     Refinement parameters (corner_type, polynomial_fit flag, thresholds).
 * @param choose     Output flags per corner index indicating successful refinement.
 */
void refine_corners(const cv::Mat& img_du,
                    const cv::Mat& img_dv,
                    const cv::Mat& img_angle,
                    const cv::Mat& img_weight,
                    Corner&        corners,
                    const Params&  params,
                    std::vector<int>& choose);

} // namespace cbdetect

#endif // LIBCBDETECT_REFINE_CORNERS_H