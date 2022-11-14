//
// Created by kxrxh on 11/15/22.
//

#ifndef KIVIDBCPP_SRC_CORE_CORE_HPP
#define KIVIDBCPP_SRC_CORE_CORE_HPP

#include <string>
#include <filesystem>
#include "../datatypes/ClusterArray.hpp"
namespace KiViDbCore {
class Core {
private:
  // Cluster array
  ClusterArray cluster_array;
  // Database folder's path
  std::string db_folder_name;
  // Checking if the database folder exists
  static bool dirExists(const char *path);
public:
  // Class constructor
  explicit Core(std::string db_folder_name) {
	this->db_folder_name = std::move(db_folder_name);
	if (!this->db_folder_name.ends_with("/")) {
	  this->db_folder_name = this->db_folder_name + "/";
	}
	if (!dirExists(this->db_folder_name.c_str())) {
	  std::filesystem::create_directory(this->db_folder_name);
	}
  }
  // Create a new cluster
  void create_cluster(const std::string &cluster_name);
  // Class destructor
  ~Core() {
	db_folder_name.clear();
  }
};

} // KiviDbCore
#endif //KIVIDBCPP_SRC_CORE_CORE_HPP
