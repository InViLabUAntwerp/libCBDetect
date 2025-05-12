#pragma once
#ifndef LIBCBDETECT_FIND_MODES_MEANSHIFT_H
#define LIBCBDETECT_FIND_MODES_MEANSHIFT_H

#include <vector>
#include <utility>

namespace cbdetect {

    /**
     * Identify histogram modes via a Gaussian-mean-shift approximation on a circular histogram.
     *
     * @param hist   Input histogram values.
     * @param sigma  Gaussian smoothing bandwidth.
     * @return       Vector of (bin_index, mode_value) pairs sorted descending by mode_value.
     */
    std::vector<std::pair<int, double>> find_modes_meanshift(
        const std::vector<double>& hist,
        double sigma);

} // namespace cbdetect

#endif // LIBCBDETECT_FIND_MODES_MEANSHIFT_H

