#pragma once
#include <vector>

namespace idn::cli {

using Array = std::vector<float>;
using ArrayRef = Array&;
using ArrayCref = const Array&;

void GenerateCSVReport(ArrayCref xs, ArrayCref ys);

}  // namespace idn::cli