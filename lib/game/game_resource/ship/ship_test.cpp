#include "ship.hpp"

#include <array>
#include <string>
#include <cstdint>
#include <map>

#include <lsm_container.hpp>

void PrintShip(const battleship::Ship& ship) {
  std::cout <<
    "coords: " << ship.GetRootCoord().first << " " << ship.GetRootCoord().second << "\n" <<
    "length: " << ship.GetLenght() << "\n" <<
    "rotate: " << (ship.IsRotate() ? "true" : "false") << "\n" <<
    "is live: " << (ship.IsLive() ? "true" : "false") << "\n";
};

// #define LSM_COMPATIBILITY_TEST
#define HIT_TEST

int main (int, char**) {
  using namespace battleship;

#ifdef LSM_COMPATIBILITY_TEST
  LsmContainer<100, std::map<uint64_t, Ship>> cont("path", {});

  for (int i = 0; i < 1000; i++) {
    cont.Add({i, Ship{i, i + 1,
      (i % 2) == 0, static_cast<char>((i % 4) + 1)}});
  }

  std::array<int64_t, 5> rem_key_cont = {0, 50, 100, 500, 999};

  for (auto&& key : rem_key_cont) {
    auto get = cont.Find(0).first;
    if (auto find_res = cont.Find(key);
      find_res.second) {
      std::cout << std::to_string(key) << ", find correct" << "\n";
      PrintShip(find_res.first);
    }
    cont.Remove(key);
    if (auto find_res = cont.Find(key);
      !find_res.second) {
      std::cout << std::to_string(key) << ", remove correct" << "\n" <<
        "=======================\n" << std::endl;
    }
  }

  std::cout << "test done" << std::endl;
#endif // LSM_COMPATIBILITY_TEST

#ifdef HIT_TEST
/*
  Ship sh1 = {0, 0, 0, 1};
  if (!sh1.Hit(0, 0)) {
    std::cout << "uncorrect hit" << std::endl;
  }
  if (sh1.IsLive()) {
    std::cout << "uncorrect live" << std::endl;
  }

  std::cout << "\n\n========================================\n\n";
*/

/*
  Ship sh12 = {1, 1, 0, 1};
  if (sh12.Hit(0, 0) || sh12.Hit(0, 1) || sh12.Hit(0, 2) ||
      sh12.Hit(1, 0)            ||             sh12.Hit(1, 2) ||
      sh12.Hit(2, 0) || sh12.Hit(2, 1) || sh12.Hit(2, 2)
    ) {
    std::cout << "uncorrect hit" << std::endl;
  }

  if (!sh12.IsLive()) {
    std::cout << "uncorrect live" << std::endl;
  }

  std::cout << "\n\n========================================\n\n";
*/
  Ship sh4 = {1, 1, 0, 4};

  if (
    !sh4.Hit(0, 0) && !sh4.Hit(1, 0) && !sh4.Hit(2, 0) && !sh4.Hit(3, 0) && !sh4.Hit(4, 0) && !sh4.Hit(5, 0) &&
    !sh4.Hit(0, 1) && sh4.Hit(1, 1) && sh4.Hit(2, 1) && sh4.Hit(3, 1) && sh4.Hit(4, 1) && !sh4.Hit(5, 1) &&
    !sh4.Hit(0, 2) && !sh4.Hit(1, 2) && !sh4.Hit(2, 2) && !sh4.Hit(3, 2) && !sh4.Hit(4, 2) && !sh4.Hit(5, 2) &&
    !sh4.Hit(99, 1) && !sh4.Hit(1, 99) && !sh4.Hit(99, 99) && !sh4.Hit(99, 99)
  ) {
    std::cout << "uncorrect hit" << std::endl;
  }

  if (sh4.IsLive()) {
    std::cout << "uncorrect live" << std::endl;
  }

  Ship sh42 = {1, 1, 1, 4};

  if (
    !sh42.Hit(0, 0) && !sh42.Hit(0, 1) && !sh42.Hit(0, 2) && !sh42.Hit(0, 3) && !sh4.Hit(0, 4) && !sh42.Hit(0, 5) &&
    !sh42.Hit(1, 0) &&  sh42.Hit(1, 1) &&  sh42.Hit(1, 2) &&  sh42.Hit(1, 3) &&  sh4.Hit(1, 4) && !sh42.Hit(1, 5) &&
    !sh42.Hit(2, 0) && !sh42.Hit(2, 1) && !sh42.Hit(2, 2) && !sh42.Hit(2, 3) && !sh4.Hit(2, 4) && !sh42.Hit(2, 5) &&
    !sh42.Hit(1, 99) && !sh42.Hit(99, 1) && !sh42.Hit(99, 99) && !sh42.Hit(99, 99)
  ) {
    std::cout << "uncorrect hit" << std::endl;
  }

  if (sh42.IsLive()) {
    std::cout << "uncorrect live" << std::endl;
  }

  std::cout << "hit test done" << std::endl;
#endif // HIT_TEST
  return 0;
}