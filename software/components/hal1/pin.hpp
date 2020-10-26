#pragma once
class pin {
 public:
  enum class id { GPIO0, GPIO1 };
  enum class mode_t {
    INPUT,
    OUTPUT,
    INOUT,
  };

  enum class capability_t {
    WEAK,
    STRONGER,
    MEDIUM,
    STRONGEST,
  };
  struct opt {
    mode_t mode;
    capability_t cap;
  };
  enum class status { HIGH, LOW };

 private:
  id m_id;
};
