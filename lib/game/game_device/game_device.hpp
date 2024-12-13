#ifndef _GAME_DEVICE_HPP_
#define _GAME_DEVICE_HPP_

#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include <event_device.hpp>

#include <game_config/game_config.hpp>
#include <config_validator/config_validator.hpp>

#include <game_resource/shot/shot.hpp>
#include <game_resource/ship/ship.hpp>
#include <game_resource/ship_coordinates/ship_coordinates.hpp>
#include <game_strategies/shot_strategy/shot_strategy.hpp>
#include <game_strategies/shot_strategy/order_shot_strategy/order_shot_strategy.hpp>
#include <game_strategies/config_strategy/config_strategy.hpp>

#include <event_device.hpp>

#include <lsm_container.hpp>

#define LABA5_TASK

namespace battleship {

class GameDevice final : public ExecuteAdditionalArgument  {
 public:
  enum State { PREPARATION, BOT_MOVE, OPONENT_MOVE };
  enum Role { NOT_INIT, SLAVE, MASTER };
  enum Status { IN_PROCESS, OPONENT_WIN, BOT_WIN };
 public:
  GameDevice() = default;
  GameDevice(const GameDevice& value) = default;
  GameDevice(GameDevice&& value);
  GameDevice& operator=(GameDevice&& value);
  ~GameDevice();

 public:
  inline GameConfig& GetConfig() { return cfg_; };
  inline void SetRole(Role role) { role_ = role; };
  inline Role GetRole() { return role_;  };
  inline State GetState() { return state_; };

  Status GetStatus();

 public:
  template<IsInheritor<ShotStrategyBase> ShotStrategyType>
  void SetShotStrategy();

  void TakeShotResult(ShotState shot_res);

 public:
  template<bool IsRenewableSession = false>
  bool Dump(const std::string& str_pdath);

  bool Load(const std::string& str_path);

 public:
  ShotState TakeShot(const std::pair<uint64_t, uint64_t>& coord);
  std::pair<uint64_t, uint64_t> GiveShot();

 public:
  bool Configurate(std::vector<std::shared_ptr<ConfigValidatorBase>> validators);

  template<IsConfigStrategy CfgStrategyType>
  bool Configurate();

  void Reset();

 private:
  Role role_ = Role::NOT_INIT;
  State state_ = State::PREPARATION;
  GameConfig cfg_;
  std::shared_ptr<ShotStrategyBase> shot_strategy_device_ = nullptr;

  ShipContainerType ship_cont_ = {"battleship", {}};
  std::vector<uint64_t> oponent_hit_cont_;
  std::vector<uint64_t> hit_cont_;
};

template<bool IsRenewableSession>
bool GameDevice::Dump(const std::string& str_path) {
  static constexpr std::string_view dump_error_description = "battleship dump fail:\n";
  std::filesystem::path file_path(str_path);

  try {
    if (!std::filesystem::exists(file_path.parent_path()))
      std::filesystem::create_directories(file_path.parent_path());
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << dump_error_description;
    std::cout << file_path << std::endl;
    std::wcerr << ex.what() << std::endl;
    return false;
  } catch (std::error_code& ex) {
    std::cerr << dump_error_description;
    std::cout << file_path << std::endl;
    std::wcerr << "error code: "<< ex.value() << std::endl;
    return false;
  } catch (...) {
    std::cerr << dump_error_description;
    std::cout << file_path << std::endl;
    return false;
  }

  std::fstream file;

  file.open(file_path, std::ios::out | std::ios::beg | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << dump_error_description;
    std::cout << file_path << " file cannot be open" <<  std::endl;
    return false;
  }

#ifndef LABA5_TASK
  file.write(reinterpret_cast<char*>(&cfg_.field_w_), sizeof(cfg_.field_w_));
  file.put(' ');
  file.write(reinterpret_cast<char*>(&cfg_.field_h_), sizeof(cfg_.field_h_));
  file.put('\n');
#else
  file << cfg_.field_w_ << ' ' << cfg_.field_h_ << '\n';
#endif // LABA5_TASK

  auto sizes_cont = ship_cont_.Size();
  decltype(ship_cont_) buff_cont{"battleship", {}};

  for (auto&& size : sizes_cont) {
    auto tmp_cont = ship_cont_.Upload();
    for (auto&& elem : tmp_cont) {
      auto root_coord = elem.second.GetRootCoord();
      auto lenght= elem.second.GetLenght();
      auto rotate = elem.second.IsRotate();

#ifndef LABA5_TASK

      file.write(reinterpret_cast<char*>(&lenght), sizeof(lenght));
      file.put(' ');
      if (rotate) {
        file.put('v');
      } else {
        file.put('h');
      }
      file.put(' ');
      file.write(reinterpret_cast<char*>(&root_coord.first), sizeof(root_coord.first));
      file.put(' ');
      file.write(reinterpret_cast<char*>(&root_coord.second), sizeof(root_coord.second));
      file.put('\n');
#else
    file << lenght << ' ' << (rotate ? 'v' : 'h') 
      << ' ' << root_coord.first << ' ' << root_coord.second << '\n';
#endif // LABA5_TASK
    }

    if constexpr (IsRenewableSession) {
      buff_cont.AddCont(std::move(tmp_cont));
    }
  }

  if constexpr (IsRenewableSession) {
    ship_cont_ = std::move(buff_cont);
  }

  return true;
};

template<IsConfigStrategy CfgStrategyType>
bool GameDevice::Configurate() {
  auto [cfg, ships] = CfgStrategyType::Get();
  cfg_ = std::move(cfg);
  ship_cont_ = std::move(ships);
  if (role_ == Role::MASTER)
    state_ = State::OPONENT_MOVE;
  if (role_ == Role::SLAVE)
    state_ = State::BOT_MOVE;
  hit_cont_ = std::vector<uint64_t>(cfg_.ship_counts_.size());
  oponent_hit_cont_ = std::vector<uint64_t>(cfg_.ship_counts_.size());

  if (!shot_strategy_device_.get())
    SetShotStrategy<OrderShotStrategy>();

  return true;
};

template<IsInheritor<ShotStrategyBase> ShotStrategyType>
void GameDevice::SetShotStrategy() {
  shot_strategy_device_ = std::make_shared<ShotStrategyType>(cfg_);
};

} // battleship

#endif // _GAME_DEVICE_HPP_