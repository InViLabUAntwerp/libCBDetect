#pragma once
#ifndef LIBCBDETECT_SCORE_CORNERS_H
#define LIBCBDETECT_SCORE_CORNERS_H

#include <opencv2/core.hpp>    // for cv::Mat, cv::Point2d
#include "config.h" // for Corner, Params

namespace cbdetect {

/**
 * Compute a composite gradient and intensity correlation score for a corner.
 * Uses two direction vectors.
 *
 * @param img         Image patch around corner (CV_64F).
 * @param img_weight  Gradient magnitude patch (CV_64F).
 * @param v1          First edge direction unit vector.
 * @param v2          Second edge direction unit vector.
 * @return            Non-negative corner confidence score.
 */
double corner_correlation_score(const cv::Mat&           img,
                                const cv::Mat&           img_weight,
                                const cv::Point2d&       v1,
                                const cv::Point2d&       v2);

/**
 * Compute a composite gradient and intensity correlation score for a corner.
 * Uses three direction vectors (MonkeySaddle case).
 *
 * @param img         Image patch around corner (CV_64F).
 * @param img_weight  Gradient magnitude patch (CV_64F).
 * @param v1          First edge direction unit vector.
 * @param v2          Second edge direction unit vector.
 * @param v3          Third edge direction unit vector.
 * @return            Non-negative corner confidence score.
 */
double corner_correlation_score(const cv::Mat&           img,
                                const cv::Mat&           img_weight,
                                const cv::Point2d&       v1,
                                const cv::Point2d&       v2,
                                const cv::Point2d&       v3);

/**
 * Score all corners in-place by computing patch responses.
 *
 * @param img      Normalized image (CV_64F).
 * @param img_weight  Gradient magnitude image (CV_64F).
 * @param corners  Corner container; scores updated in corners.score.
 * @param params   Scoring parameters (corner_type, radius, thresholds).
 */
void sorce_corners(const cv::Mat&     img,
                   const cv::Mat&     img_weight,
                   Corner&            corners,
                   const Params&      params);

/**
 * Remove corners whose score is below a threshold.
 *
 * @param tau      Score threshold.
 * @param corners  Corner container to prune (positions, orientations, and scores updated).
 * @param params   Pruning parameters (corner_type).
 */
void remove_low_scoring_corners(double          tau,
                                Corner&         corners,
                                const Params&   params);

} // namespace cbdetect

#endif // LIBCBDETECT_SCORE_CORNERS_H