#pragma once
#ifndef LIBCBDETECT_GET_IMAGE_PATCH_H
#define LIBCBDETECT_GET_IMAGE_PATCH_H

#include <opencv2/core.hpp>    // for cv::Mat

namespace cbdetect {

    /**
     * Extract a square image patch around a subpixel location via bilinear interpolation.
     *
     * @param img      Input image (CV_64F) to sample from.
     * @param u        Subpixel x-coordinate (column).
     * @param v        Subpixel y-coordinate (row).
     * @param r        Patch radius (half-width).
     * @param img_sub  Output patch of size (2*r+1) x (2*r+1), CV_64F.
     */
    void get_image_patch(const cv::Mat& img,
                         double u,
                         double v,
                         int    r,
                         cv::Mat& img_sub);

    /**
     * Extract a masked image patch around a subpixel location via bilinear interpolation.
     * Only pixels where mask >= epsilon are included in the output vector.
     *
     * @param img      Input image (CV_64F) to sample from.
     * @param mask     Binary mask of same size patch (values >=1e-6 retained).
     * @param u        Subpixel x-coordinate (column).
     * @param v        Subpixel y-coordinate (row).
     * @param r        Patch radius (half-width).
     * @param img_sub  Output single-column CV_64F Mat of selected pixels.
     */
    void get_image_patch_with_mask(const cv::Mat& img,
                                   const cv::Mat& mask,
                                   double         u,
                                   double         v,
                                   int            r,
                                   cv::Mat&       img_sub);

} // namespace cbdetect

#endif // LIBCBDETECT_GET_IMAGE_PATCH_H

