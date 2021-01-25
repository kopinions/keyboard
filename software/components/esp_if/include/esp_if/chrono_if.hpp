#include "chrono.hpp"
#include "esp_timer.h"

namespace kopinions {
class clock_if : public kopinions::clock {
 public:
  kopinions::time now() override;
  ~clock_if() override = default;
};


}  // namespace kopinions
