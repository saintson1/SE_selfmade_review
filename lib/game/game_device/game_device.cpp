#include "game_device.hpp"
#include "ship_coordinates/ship_coordinates.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>

#include <game_strategies/shot_strategy/order_shot_strategy/order_shot_strategy.hpp>
#include <game_config/game_config.hpp>
#include <ship/ship.hpp>
#include <config_validator/config_validator.hpp>
#include <game_resource/shot/shot.hpp>

#ifndef LABA5_TASK
#define LABA5_TASK
#endif // LABA5_TASK

namespace battleship {

GameDevice::GameDevice(GameDevice&& value) :
  cfg_(std::move(value.cfg_)), ship_cont_(std::move(value.ship_cont_)),
    role_(value.role_), oponent_hit_cont_(std::move(value.oponent_hit_cont_)),
      hit_cont_(std::move(value.hit_cont_)), state_(value.state_),
        shot_strategy_device_(std::move(value.shot_strategy_device_))
          { value.role_ = Role::NOT_INIT; };

GameDevice& GameDevice::operator=(GameDevice&& value) {
  if (this == &value)
    return *this;

  cfg_ = std::move(value.cfg_);
  ship_cont_ = std::move(value.ship_cont_);
  role_ = value.role_;
  state_ = value.state_;
  value.state_ = State::PREPARATION;
  value.role_ = Role::NOT_INIT;
  hit_cont_ = std::move(value.hit_cont_);
  oponent_hit_cont_ = std::move(value.oponent_hit_cont_);
  shot_strategy_device_ = std::move(value.shot_strategy_device_);

  return *this;
};

GameDevice::~GameDevice() {  };

GameDevice::Status GameDevice::GetStatus() {
  if (state_ == State::PREPARATION)
    return Status::IN_PROCESS;

  for (size_t ind = 0, end_ind = cfg_.ship_counts_.size();
    ind != end_ind; ++ind) {
    if (cfg_.ship_counts_[ind] != hit_cont_[ind])
      break;
    if (ind + 1 == end_ind && cfg_.ship_counts_[ind] == hit_cont_[ind]) {
      return Status::BOT_WIN;
    }
  }

  for (size_t ind = 0, end_ind = cfg_.ship_counts_.size();
    ind != end_ind; ++ind) {
    if (cfg_.ship_counts_[ind] != oponent_hit_cont_[ind])
      break;
    if (ind + 1 == end_ind && cfg_.ship_counts_[ind] == oponent_hit_cont_[ind]) {
      return Status::OPONENT_WIN;
    }
  }

  return Status::IN_PROCESS;
};

bool GameDevice::Configurate(std::vector<std::shared_ptr<ConfigValidatorBase>> validators) {
  if (!validators.size())
    return false;
  if (!cfg_.IsValid())
    return false;

  std::shared_ptr<ConfigValidatorBase> validator;
  for (auto&& validator_elem : validators) {
    if (validator_elem->IsValid()) {
      validator = validator_elem;
      break;
    }
  }

  if (!validator) {
    return false;
  }

  ship_cont_ = validator->Place();

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

ShotState GameDevice::TakeShot(const std::pair<uint64_t, uint64_t>& coord) {
  ShotState shot_res = ShotState::MISS;

  ship_cont_.Modify(SinglShipCoord{coord}, [&coord, &shot_res, this](Ship& ship) {
    if (!ship.IsLive()) {
      shot_res = ShotState::KILL;
      return;
    }
    if (ship.Hit(coord.first, coord.second)) {
      shot_res = ShotState::HIT;
    } else {
      state_ = State::BOT_MOVE;
    }

    if (!ship.IsLive()) {
      ++oponent_hit_cont_[ship.GetLenght() - 1];
      shot_res = ShotState::KILL;
    }
  });

  if (shot_res == ShotState::MISS) {
    state_ = State::BOT_MOVE;
  }

  return shot_res;
};

std::pair<uint64_t, uint64_t> GameDevice::GiveShot() {
  state_ = State::OPONENT_MOVE;
  return shot_strategy_device_->GetShot();;
};

void GameDevice::TakeShotResult(ShotState shot_res) {
  shot_strategy_device_->GetResult(shot_res);
  if (shot_res == ShotState::KILL) {
    for (size_t ind = 0, end_ind = cfg_.ship_counts_.size();
      ind != end_ind; ++ind) {
      if (hit_cont_[ind] != cfg_.ship_counts_[ind]) {
        ++hit_cont_[ind];
        break;
      }
    }
  }

  if (shot_res == ShotState::KILL || shot_res == ShotState::HIT) {
    state_ = State::BOT_MOVE;
  }
};

bool GameDevice::Load(const std::string& str_path) {
  static constexpr std::string_view load_error_description = "battleship load fail:\n";
  std::filesystem::path file_path(str_path);

  try {
    if (std::filesystem::exists(file_path.parent_path()))
      std::filesystem::create_directories(file_path.parent_path());
  } catch (std::filesystem::filesystem_error& ex) {
    std::cerr << load_error_description;
    std::cout << file_path << std::endl;
    std::wcerr << ex.what() << std::endl;
    return false;
  } catch (std::error_code& ex) {
    std::cerr << load_error_description;
    std::cout << file_path << std::endl;
    std::wcerr << "error code: "<< ex.value() << std::endl;
    return false;
  } catch (...) {
    std::cerr << load_error_description;
    std::cout << file_path << std::endl;
    return false;
  }

  std::fstream file;

  file.open(file_path, std::ios::in | std::ios::beg | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << load_error_description;
    std::cout << file_path << " file cannot be open" <<  std::endl;
    return false;
  }

#ifndef LABA5_TASK
  char ch_buff;
  file.read(reinterpret_cast<char*>(&cfg_.field_w_), sizeof(cfg_.field_w_));
  file.get(ch_buff);
  file.read(reinterpret_cast<char*>(&cfg_.field_h_), sizeof(cfg_.field_h_));
  file.put(ch_buff);
#else
  file >> cfg_.field_w_ >> cfg_.field_h_;
#endif // LABA5_TASK
  auto sizes_cont = ship_cont_.Size();

  while (!file.eof()) {
    std::pair<uint64_t, uint64_t> root_coord;
    int32_t lenght;
    bool rotate;
#ifndef LABA5_TASK
    file.read(reinterpret_cast<char*>(&lenght), sizeof(lenght));
    file.get(ch_buff);
    file.get(ch_buff);
    if (ch_buff == 'v') {
      rotate = true;
    } else if (ch_buff == 'h') {
      rotate = false;
    } else {
      return false;
    }
    file.get(ch_buff);
    file.read(reinterpret_cast<char*>(&root_coord.first), sizeof(root_coord.first));
    file.get(ch_buff);
    file.read(reinterpret_cast<char*>(&root_coord.second), sizeof(root_coord.second));
    file.put(ch_buff);

    if (ch_buff != '\n') {
      return false;
    }
#else
    std::string rotate_status;
    file >> lenght >> rotate_status >> root_coord.first >> root_coord.second;
    if (rotate_status == "v") {
      rotate = true;
    } else if (rotate_status == "h") {
      rotate = false;
    } else {
      return false;
    }
#endif // LABA5_TASK
    if (lenght <= cfg_.ship_counts_.size() && lenght != 0) {
      Ship ship{root_coord.first, root_coord.second, rotate, lenght};
      ++cfg_.ship_counts_[lenght - 1];
      ship_cont_.Add({ship.CreateCoordinates(), ship});
    }
  }

  return true;
};

void GameDevice::Reset() {
  role_ = Role::NOT_INIT;
  state_ = State::PREPARATION;
  cfg_ = GameConfig{};
  shot_strategy_device_ = nullptr;

  ship_cont_ = {"battleship", {}};
  oponent_hit_cont_.clear();
  hit_cont_.clear();
};

} // battleship