#pragma once

namespace kopinions::protocols {
class response {};

class interface {};

class generic_payload {};

enum phase_enum { UNINITIALIZED_PHASE = 0, BEGIN_REQ = 1, END_REQ, BEGIN_RESP, END_RESP };

class tlm_phase {
 public:
  tlm_phase();

  tlm_phase(phase_enum standard);
  tlm_phase& operator=(phase_enum standard);

  operator unsigned int() const { return m_id; }
  const char* get_name() const;

 protected:
  // register extended phase
  tlm_phase(const std::type_info& type, const char* name);

 private:
  unsigned int m_id;
};

enum sync_enum { ACCEPTED, UPDATED, COMPLETED };

class sc_time {
 public:
  typedef uint64_t value_type;

  // constructors

  sc_time();
  sc_time(const sc_time&);

  // convert time unit from string
  // "fs"/"SC_FS"->SC_FS, "ps"/"SC_PS"->SC_PS, "ns"/"SC_NS"->SC_NS, ...
  sc_time(double, const char* unit);

  static sc_time from_value(value_type);
  static sc_time from_seconds(double);
  static sc_time from_string(const char* str);

  // deprecated, use from_value(v)
  sc_time(double, bool scale);
  sc_time(value_type, bool scale);

  // assignment operator

  sc_time& operator=(const sc_time&);

  // conversion functions

  value_type value() const;  // relative to the time resolution
  double to_double() const;  // relative to the time resolution
  double to_default_time_units() const;
  double to_seconds() const;
  const std::string to_string() const;

  // relational operators

  bool operator==(const sc_time&) const;
  bool operator!=(const sc_time&) const;
  bool operator<(const sc_time&) const;
  bool operator<=(const sc_time&) const;
  bool operator>(const sc_time&) const;
  bool operator>=(const sc_time&) const;

  // arithmetic operators

  sc_time& operator+=(const sc_time&);
  sc_time& operator-=(const sc_time&);

  friend const sc_time operator+(const sc_time&, const sc_time&);
  friend const sc_time operator-(const sc_time&, const sc_time&);

  sc_time& operator*=(double);
  sc_time& operator/=(double);
  sc_time& operator%=(const sc_time&);

  friend const sc_time operator*(const sc_time&, double);
  friend const sc_time operator*(double, const sc_time&);
  friend const sc_time operator/(const sc_time&, double);
  friend double operator/(const sc_time&, const sc_time&);
  friend const sc_time operator%(const sc_time&, const sc_time&);

  // print function

  void print(::std::ostream& os = std::cout) const;

 private:
  value_type m_value;
};

template <typename TRANS = generic_payload, typename PHASE = tlm_phase>
class fw_nonblocking_transport_if : public virtual interface {
 public:
  virtual sync_enum nb_transport_fw(TRANS& trans, PHASE& phase, sc_time& t) = 0;
};

template <typename TRANS = generic_payload, typename PHASE = tlm_phase>
class bw_nonblocking_transport_if : public virtual interface {
 public:
  virtual sync_enum nb_transport_bw(TRANS& trans, PHASE& phase, time& t) = 0;
};

template <typename TRANS = generic_payload>
class transport_if : public virtual interface {
 public:
  virtual void b_transport(TRANS&) = 0;
};
}  // namespace kopinions::protocols