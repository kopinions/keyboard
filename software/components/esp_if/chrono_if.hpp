#include "chrono.hpp"

namespace kopinions {
class clock_if : public kopinions::clock {
 public:
  kopinions::time now() override { return kopinions::time(0); }
  ~clock_if() override = default;
};
}  // namespace kopinions
