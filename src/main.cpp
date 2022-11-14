#include <iostream>
#include "core/core.hpp"

int main() {
  KiViDbCore::Core core("../database/kividb/");
  core.newCluster("cluster1");
  return 0;
}
