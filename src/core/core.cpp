//
// Created by kxrxh on 11/15/22.
//
#include <fstream>
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
  std::string cluster_path = db_folder_name + cluster_name;
  if (!cluster_path.ends_with("/")) {
	cluster_path += "/";
  }
  if (!is_directory_exists(cluster_path.c_str())) {
	std::filesystem::create_directory(cluster_path);
	cluster_array.append(Cluster{cluster_name, cluster_path});
  }
}

// Get cluster by name
Cluster KiViDbCore::Core::get_cluster(const std::string &cluster_name) const {
  for (int i = 0; i < cluster_array.size(); i++) {
	if (cluster_array[i].name == cluster_name) {
	  return cluster_array[i];
	}
  }
  return Cluster{"", ""};
}

void KiViDbCore::Core::update_cluster_array() {
  cluster_array.clear();
  for (const auto &cluster : std::filesystem::directory_iterator(db_folder_name)) {
	std::string cluster_name = cluster.path().filename();
	std::string cluster_path = cluster.path();
	if (!cluster_path.ends_with("/")) {
	  cluster_path += "/";
	}
	// Get number of files in the cluster directory
	unsigned int number_of_files = 0;
	for (const auto &_ : std::filesystem::directory_iterator(cluster_path)) {
	  number_of_files++;
	}
	auto* _doc_array = new Document[number_of_files];
	for (int i = 0; const auto &document : std::filesystem::directory_iterator(cluster_path)) {
	  // Read document content
	  std::ifstream document_content_file(document.path());
	  std::string document_content;
	  document_content_file >> document_content;
	  // Create document object
	  _doc_array[i++] = Document{document.path().filename(), document_content};
	}
	cluster_array.append(Cluster{cluster_name, cluster_path, _doc_array, number_of_files});
  }
}

ClusterArray KiViDbCore::Core::get_all_clusters() const {
  return cluster_array.copy();
}
void KiViDbCore::Core::delete_cluster(const std::string &cluster_name) {
  for (int i = 0; i < cluster_array.size(); i++) {
	if (cluster_array[i].name == cluster_name) {
	  std::filesystem::remove_all(cluster_array[i].path);
	  cluster_array.remove(i);
	  return;
	}
  }
}
Document KiViDbCore::Core::get_document(const std::string &cluster_name, const std::string &document_name) const {
  std::string document_path = db_folder_name + cluster_name + "/" + document_name;
  if (!is_directory_exists(document_path.c_str())) {
	return Document{"", ""};
  }
  for (const auto &entry : std::filesystem::directory_iterator(db_folder_name + cluster_name + "/")) {
	if (entry.path().filename() == document_name) {
	  return Document{document_name, document_path};
	}
	return Document{"", ""};
  }
}
void KiViDbCore::Core::create_document(const std::string &cluster_name, const std::string &document_name, const std::string &document_content) {
  std::string document_path = db_folder_name + cluster_name + "/" + document_name;
  if (!is_directory_exists(document_path.c_str())) {
	std::filesystem::create_directory(document_path);
  }
  this->get_cluster(cluster_name).add_document(Document{document_name, document_content});

}
