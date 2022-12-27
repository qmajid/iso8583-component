#ifndef __COMPOSITE2003_H__
#define __COMPOSITE2003_H__

#include <stdio.h>

#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "bit.h"

struct BitComposite2003 : public Component {  // BASE
  BitComposite2003() {}

  virtual void parse() {
    register_bit<int>(BIT_1, 20, 1, 100);
    register_bit<char>(BIT_2, 'X');
    register_bit<std::string>(BIT_3, "majid");
    register_bit<iscINT2>(BIT_4, 1, 1, 100);
    register_bit<iscINT8>(BIT_5, 120, 100, 120);
    register_bit<iscINT16>(BIT_6, 1500, 1000, 10000);
    register_bit<char>(BIT_7, 'A');
    register_bit<char>(BIT_8, 'B');
    register_bit<std::string>(BIT_9, "hello", 1, 10);
    register_bit<std::string>(BIT_10, "shetab", -1, -1, 5);
  }

  //------------------------------- MAIN BIT OPERATIONS
  template <class T>
  T get_bit(int number) {
    auto it = items_map.find(number);
    if (it == items_map.end()) {
      // not exist this field in map
      T value;
      return value;
    }
    return items_map[number]->get<T>();
  }

  template <class T>
  void set_bit(int number, T value) {
    items_map[number]->set<std::string>(value);
  }

  //------------------------------- WRAPPER BIT OPERATIONS
  virtual std::string get_pan() { return get_bit<std::string>(BIT::BIT_PAN); }

  virtual void set_pan(const std::string &value) { items_map[BIT::BIT_PAN]->set<std::string>(value); }

  //------------------------------- COMPONENT FUNCTIONS
  virtual bool IsComposite() const override { return true; }

  //-------------------------------
  //-------------------------------
  //-------------------------------
  template <class T>
  void register_bit(int bit_number, T value, int min = -1, int max = -1, int len = -1) {
    auto p = std::make_unique<BitComponent>();
    p->set<T>(value)->min(min)->max(max)->len(len);
    p->SetParent(this);

    auto it = items_map.find(bit_number);
    if (it != items_map.end()) {
      // already exist,update
      it->second = std::move(p);
    } else {
      items_map.insert(std::make_pair(bit_number, std::move(p)));
    }

    // std::cout << "insert = " << bit_number << ":" << value << "\n";
  }

  virtual void print() {
    int index = 0;
    std::cout << "bit[1][int]= " << items_map[BIT_1]->get<int>() << "\n";
    std::cout << "bit[2][char] = " << items_map[BIT_2]->get<char>() << "\n";
    std::cout << "bit[3][std::string] = " << items_map[BIT_3]->get<std::string>() << "\n";
    std::cout << "bit[4][iscINT2] = " << items_map[BIT_4]->get<iscINT2>() << "\n";
  }

 protected:
  std::unordered_map<int, std::unique_ptr<BitComponent>> items_map;
};
#endif  // __COMPOSITE2003_H__