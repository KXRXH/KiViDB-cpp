#include <iostream>
#include "core/core.hpp"

int main() {
  KiViDbCore::Core core("../database/kividb/");
  for (int i = 10; i < 100; i++) {
	std::stringstream ss;
	ss << "cluster" << i;
	core.create_cluster(ss.str());
  }
  return 0;
}
