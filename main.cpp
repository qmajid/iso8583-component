#include "iso.h"
#include <iostream>
#include <stdio.h>

int main() {
  std::printf("------------------2003------------------\n");
  Iso2003 iso2003;
  iso2003.start();

  std::printf("------------------87------------------\n");
  Iso87 iso87;
  iso87.start();

  return 0;
}