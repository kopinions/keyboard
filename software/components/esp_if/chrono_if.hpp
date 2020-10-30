#include "chrono.hpp"
#include "esp_timer.h"

namespace kopinions {
class clock_if : public kopinions::clock {
 public:
  kopinions::time now() override;
  ~clock_if() override = default;
};

kopinions::time clock_if::now() {
  int64_t time = esp_timer_get_time();
  return kopinions::time(time);
}

}  // namespace kopinions
