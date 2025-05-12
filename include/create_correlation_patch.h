#pragma once
#ifndef LIBCBDETECT_CREATE_CORRELATION_PATCH_H
#define LIBCBDETECT_CREATE_CORRELATION_PATCH_H

#include <vector>
#include <opencv2/core.hpp>  // for cv::Mat

namespace cbdetect {

    /**
     * Build a set of 4 directional correlation kernels from two angles.
     *
     * @param template_kernel  Sized radius*2+1, will be filled with 4 mats.
     * @param angle_1          First normal direction (radians).
     * @param angle_2          Second normal direction (radians).
     * @param radius           Radius of the patch.
     */
    void create_correlation_patch(std::vector<cv::Mat>& template_kernel,
                                  double angle_1,
                                  double angle_2,
                                  int    radius);

    /**
     * Build a set of 6 directional correlation kernels from three angles.
     *
     * @param template_kernel  Sized radius*2+1, will be filled with 6 mats.
     * @param angle_1          First normal direction (radians).
     * @param angle_2          Second normal direction (radians).
     * @param angle_3          Third normal direction (radians).
     * @param radius           Radius of the patch.
     */
    void create_correlation_patch(std::vector<cv::Mat>& template_kernel,
                                  double angle_1,
                                  double angle_2,
                                  double angle_3,
                                  int    radius);

} // namespace cbdetect

#endif // LIBCBDETECT_CREATE_CORRELATION_PATCH_H
