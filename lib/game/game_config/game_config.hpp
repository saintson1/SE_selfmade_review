#ifndef _game_config_HPP_
#define _game_config_HPP_

#include<vector>
#include<cstdint>

#include <event.hpp>
#include <lsm_container.hpp>

namespace battleship {

struct GameConfig final : public ExecuteAdditionalArgument {
 public:
  using FieldSize = uint64_t;
  using CountType = uint64_t;

 public:
  GameConfig() = default;
  GameConfig(FieldSize w, FieldSize h);
  ~GameConfig() override;

 public:
  bool IsValid();

 public:
  FieldSize field_w_ = 0;
  FieldSize field_h_ = 0;
  std::vector<CountType> ship_counts_ = {0, 0, 0, 0};
};

} // battleship

#endif // _GAME_CONFIG_HPP_