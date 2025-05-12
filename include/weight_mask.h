#pragma once
#ifndef LIBCBDETECT_WEIGHT_MASK_H
#define LIBCBDETECT_WEIGHT_MASK_H

#include <unordered_map>
#include <vector>
#include <opencv2/core.hpp>    // for cv::Mat

namespace cbdetect {

    /**
     * Precompute radial weight masks for a set of patch radii.
     * Each mask is a (2*r+1)x(2*r+1) CV_64F image where weights fall off linearly
     * between 0.7 and 1.3 normalized radius.
     *
     * @param radius  List of patch radii.
     * @return        Map from radius to corresponding weight mask.
     */
    std::unordered_map<int, cv::Mat>
    weight_mask(const std::vector<int>& radius);

} // namespace cbdetect

#endif // LIBCBDETECT_WEIGHT_MASK_H

