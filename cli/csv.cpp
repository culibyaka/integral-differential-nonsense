#include "csv.hpp"
#include <format>
#include <idn/common/assert.hpp>
#include <iostream>

namespace idn::cli {

void GenerateCSVReport(ArrayCref xs, ArrayCref ys) {
  IDN_ASSERT(xs.size() == ys.size());

  std::cout << "x,f\n";
  for (auto i = 0; i < xs.size(); ++i) {
    std::cout << std::format("{},{}\n", xs[i], ys[i]);
  }
}

}  // namespace idn::cli