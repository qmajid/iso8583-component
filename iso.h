#ifndef __ISO_H__
#define __ISO_H__

#include "composite2003.h"
#include "composite87.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <type_traits>

class Iso {
public:
  Iso() = default;
  virtual ~Iso() = default;

  // template method
  void start() {
    do_process();
    convert();
    check();
  }

  virtual void do_process() = 0;
  virtual void convert() = 0;
  virtual void check() = 0;
};

class Iso2003 : public Iso {
public:
  Iso2003() = default;
  ~Iso2003() = default;

  virtual void do_process() override {
    BitComposite2003 b;
    b.parse();

    b.set_pan("1234567890123");
    std::printf("pan: %s\n", b.get_pan().data());

    b.set_bit(BIT::BIT_PAN, "987654321123456");
    std::printf("pan: %s\n", b.get_bit<std::string>(BIT::BIT_PAN).data());
    b.print();
  }

protected:
  virtual void convert() { std::cout << "call convert in Iso2003\n"; }
  virtual void check() { std::cout << "call check in Iso2003\n"; }
};

class Iso87 : public Iso2003 {
public:
  Iso87() = default;
  ~Iso87() = default;
  virtual void do_process() override {
    BitComposite87 b2;
    b2.parse();
    std::printf("pan2: %s\n", b2.get_pan().data());
    b2.print();
  }

protected:
  virtual void convert() { std::cout << "call convert in Iso87\n"; }
  virtual void check() { std::cout << "call check in Iso87\n"; }
};
#endif // __ISO_H__