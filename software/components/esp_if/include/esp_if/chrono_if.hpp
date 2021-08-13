#include "esp_timer.h"
#include "vif/chrono.hpp"

namespace kopinions {
class clock_if : public kopinions::clock {
 public:
  kopinions::time now() override;
  ~clock_if() override = default;
};


}  // namespace kopinions
