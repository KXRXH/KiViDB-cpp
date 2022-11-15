//
// Created by kxrxh on 11/15/22.
//
#include "core.hpp"

bool KiViDbCore::Core::is_directory_exists(const char *path) {
  struct stat info{};
  if (stat(path, &info) != 0) {
	return false;
  } else if (info.st_mode & S_IFDIR) {
	return true;
  }
  return false;
}

void KiViDbCore::Core::create_cluster(const std::string &cluster_name) {
  std::string cluster_path = db_folder_name;
  if (!cluster_name.ends_with("/")) {
	cluster_path = db_folder_name + "/";
  }
  cluster_path += cluster_name;
  if (!is_directory_exists(cluster_path.c_str())) {
	std::filesystem::create_directory(cluster_path);
	cluster_array.append(Cluster{cluster_name.c_str(), cluster_path.c_str()});
  }
}
