#ifndef __BIT_H__
#define __BIT_H__

#include <cstring>
#include <iostream>
#include <optional>
#include <stdio.h>
#include <string>
#include <tuple>
#include <type_traits>

typedef long long iscINT16;
typedef long iscINT8;
typedef int iscINT4;
typedef short iscINT2;
typedef char iscINT1;

enum class DataType : uint8_t { CHAR = 0, INT, STRING, INVALID, IRANSYSTEM };

enum BIT : uint8_t {
  BIT_1 = 1,
  BIT_2 = 2,
  BIT_3 = 3,
  BIT_PAN = 3,
  BIT_4 = 4,
  BIT_5 = 5,
  BIT_6 = 6,
  BIT_7 = 7,
  BIT_8 = 8,
  BIT_9 = 9,
  BIT_10 = 10,
};

struct Component {
public:
  virtual ~Component() = default;

  void SetParent(Component *parent) { this->parent_ = parent; }
  Component *GetParent() const { return this->parent_; }
  virtual bool IsComposite() const { return false; }

protected:
  Component *parent_;
};
//------------------------------------------------------ BIT
struct BitComponent : public Component {
  BitComponent() = default;

  template <typename T> BitComponent *set(T value) {
    std::get<T>(storage) = value;

    if constexpr (std::is_same_v<T, char>) {
      dt_ = DataType::CHAR;
    }
    if constexpr (std::is_same_v<T, int>) {
      dt_ = DataType::INT;
    }
    if constexpr (std::is_same_v<T, std::string>) {
      dt_ = DataType::STRING;
    }

    return this;
  }

  BitComponent *min(int min) {
    min_ = min;
    return this;
  }

  BitComponent *max(int max) {
    max_ = max;
    return this;
  }

  BitComponent *len(int len) {
    len_ = len;
    return this;
  }

  bool check() {
    switch (dt_) {
    case DataType::CHAR:
      break;
    case DataType::INT:
      if (std::get<int>(storage) < min_ || std::get<int>(storage) > max_) {
        return false;
      }
      break;
    case DataType::STRING:
      if (std::get<std::string>(storage).length() < len_) {
        return false;
      }
      break;
    }
    return true;
  }

  template <typename T> T get() { return std::get<T>(storage); }

  void print() {
    switch (dt_) {
    case DataType::CHAR:
      std::cout << "print " << name_ << ":" << std::get<char>(storage) << "\n";
      break;
    case DataType::INT:
      std::cout << "print " << name_ << ":" << std::get<int>(storage) << "\n";
      break;
    case DataType::STRING:
      std::cout << "print " << name_ << ":" << std::get<std::string>(storage)
                << "\n";
      break;
    }
    std::cout << "print " << name_ << ": this data type not registerd\n";
  }

private:
  std::string name_;
  std::tuple<char, int, std::string, iscINT2, iscINT8, iscINT16> storage = {
      '\0', 0, "", 0, 0, 0};
  int min_ = -1;
  int max_ = -1;
  int len_ = -1;
  DataType dt_;
};

#endif // __BIT_H__