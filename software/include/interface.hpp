#pragma once
class event;
class port_base;
class interface {
 public:
  virtual void register_port(port_base& port_, const char* if_typename_);

  virtual const event& default_event() const;

  virtual ~interface();

 protected:
  interface();

 private:
  // disabled
  interface(const sc_interface&);
  interface& operator=(const sc_interface&);
};
