#ifndef __COMPOSITE87_H__
#define __COMPOSITE87_H__

#include "composite2003.h"

struct BitComposite87 : public BitComposite2003 {
  virtual void parse() {
    BitComposite2003::parse();

    register_bit<std::string>(BIT_4, "4444555566667777");
  }

  virtual std::string get_pan() { return get_bit<std::string>(BIT_4); }

  virtual void print() {
    int index = 0;
    // for (auto &&e : items)
    std::cout << "bit[1][int] = " << items_map[BIT_1]->get<int>() << "\n";
    std::cout << "bit[2][char] = " << items_map[BIT_2]->get<char>() << "\n";
    std::cout << "bit[3][std::string] = " << items_map[BIT_3]->get<std::string>() << "\n";
    std::cout << "bit[4][std::string] = " << items_map[BIT_4]->get<std::string>() << "\n";
  }
};

#endif  // __COMPOSITE87_H__