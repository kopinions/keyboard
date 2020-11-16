#pragma once

namespace kopinions::protocols {
class response {};

class payload {};

class interface {};

template <typename RX=response, typename TX = payload>
class fw_if : public virtual interface {
  virtual RX write(TX& tx) = 0;
};

template <typename RX=response, typename TX = payload>
class bw_if : public virtual interface {
  virtual RX read(TX& tx) = 0;
};

template <typename RX=response, typename TX = payload, typename fw = fw_if<TX>, typename bw = bw_if<TX>>
class channel: public virtual fw_if<RX, TX>, public virtual bw_if<RX, TX> {
 public:
  void send(TX& tx){

  };
};
}  // namespace kopinions::protocols