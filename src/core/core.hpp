//
// Created by kxrxh on 11/15/22.
//

#ifndef KIVIDBCPP_SRC_CORE_CORE_HPP
#define KIVIDBCPP_SRC_CORE_CORE_HPP

#include <sys/stat.h>
#include <string>
#include <filesystem>
#include <iostream>
#include "../datatypes/ClusterArray.hpp"
#include "../datatypes/Document.hpp"

namespace KiViDbCore {
class Core {
private:
  // Cluster array
  ClusterArray cluster_array = ClusterArray();
  // Database folder's path
  std::string db_folder_name;

  // Updating Cluster array
  void update_cluster_array();

public:
  [[nodiscard]] bool cluster_exists(const std::string &cluster_name) const;

  [[nodiscard]] bool document_exists(const std::string &cluster_name, const std::string &document_name) const;

  // Class constructor
  explicit Core(std::string db_folder_name) {
    this->db_folder_name = std::move(db_folder_name);
    if (!this->db_folder_name.ends_with("/")) {
      this->db_folder_name = this->db_folder_name + "/";
    }
    if (!std::filesystem::exists(this->db_folder_name)) {
      std::filesystem::create_directory(this->db_folder_name);
      return;
    }
    update_cluster_array();
  }

  // CLUSTER OPERATIONS:
  // 1. Get all clusters in the database
  [[nodiscard]] ClusterArray get_all_clusters() const;

  // 2. Create a new Cluster
  void create_cluster(const std::string &cluster_name);

  // 3. Get Cluster by name
  [[nodiscard]] Cluster get_cluster(const std::string &cluster_name) const;

  // 4. Delete Cluster by name
  void delete_cluster(const std::string &cluster_name);

  // DOCUMENT OPERATIONS:
  // 1. Create a new Document
  void create_document(const std::string &cluster_name,
                       const std::string &document_name,
                       const std::string &document_content);

  // 2. Get Document by name
  [[nodiscard]] Document get_document(const std::string &cluster_name, const std::string &document_name) const;

  // 3. Update Document by name
  void update_document(const std::string &cluster_name,
                       const std::string &document_name,
                       const std::string &document_content);

  // 4. Delete Document by name
  void delete_document(const std::string &cluster_name, const std::string &document_name);

  // Class destructor
  ~Core() {
    db_folder_name.clear();
  }
};

} // KiViDbCore
#endif //KIVIDBCPP_SRC_CORE_CORE_HPP
