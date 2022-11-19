//
// Created by kxrxh on 11/17/22.
//

#ifndef KIVIDB_CPP_TEST_TESTS_HPP
#define KIVIDB_CPP_TEST_TESTS_HPP
#include "../src/core/core.hpp"
void test1() {
  std::cout << "::Test #1::" << std::endl;
  KiViDbCore::Core core("../database/kividb/", true);
  for (int i = 10; i < 15; i++) {
	std::stringstream ss;
	ss << "Cluster" << i;
	core.create_cluster(ss.str());
  }
  std::string n = "cluster10";
  auto w = core.get_cluster("cluster10");
  auto wn = core.get_cluster(n);
  std::cout << n << '\n';
  std::cout << w;
  std::cout << wn;
  auto d = core.get_all_clusters().size();
  std::cout << d << '\n';
};

void test2() {
  std::cout << "::Test #2::" << std::endl;
  KiViDbCore::Core core("../database/kividb/", true);
  auto ac = core.get_all_clusters();
  std::cout << ac[0];
  ac = core.get_all_clusters();
  std::cout << ac[0];
  Cluster v = ac[ac.size() - 2];
  std::cout << v;
  auto n = ac[1];
  std::cout << n;
};
#endif //KIVIDB_CPP_TEST_TESTS_HPP

void test3() {
  std::cout << "::Test #3::" << std::endl;
  KiViDbCore::Core core("../database/kividb/", true);
  auto ac = core.get_all_clusters();
  for (int i = 0; i < ac.size(); i++) {
	std::cout << ac[i];
  }
  core.delete_cluster("cluster10");
  std::cout << "AFTER" << "\n";
  ac = core.get_all_clusters();
  for (int i = 0; i < ac.size(); i++) {
	std::cout << ac[i];
  }
};

void test4() {
  std::cout << "::Test #4::" << std::endl;
  KiViDbCore::Core core("../database/kividb/", true);
  auto ac = core.get_all_clusters();
  for (int i = 0; i < ac.size(); i++) {
	std::cout << ac[i] << ac[i].document_array_size;
	std::cout << "DATA: " << ac[i].document_array[0].data << "\n";
  }
}