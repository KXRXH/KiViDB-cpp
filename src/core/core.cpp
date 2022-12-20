//
// Created by kxrxh on 11/15/22.
//
#include <fstream>
#include "core.hpp"

// Check if the cluster exists
bool KiViDbCore::Core::cluster_exists(const std::string &cluster_name) const {
  // Check if the cluster exists
  return std::filesystem::exists(db_folder_name + cluster_name);
}

// Check if the document exists
bool KiViDbCore::Core::document_exists(const std::string &cluster_name, const std::string &document_name) const {
  return std::filesystem::exists(db_folder_name + cluster_name + "/" + document_name);
}

// Create a new cluster
void KiViDbCore::Core::create_cluster(const std::string &cluster_name) {
  // Check if cluster already exists
  if (!cluster_exists(cluster_name)) {
    std::string cluster_path = db_folder_name + cluster_name;
    if (!cluster_path.ends_with("/")) {
      cluster_path += "/";
    }
    std::filesystem::create_directory(cluster_path);
    cluster_array.append(Cluster{cluster_name, cluster_path});
  }
}

// Get Cluster by name
Cluster KiViDbCore::Core::get_cluster(const std::string &cluster_name) const {
  if (cluster_exists(cluster_name)) {
    for (int i = 0; i < cluster_array.size(); i++) {
      if (cluster_array[i].name == cluster_name) {
        return cluster_array[i];
      }
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
    // Get number of files in the Cluster directory
    unsigned int number_of_files = 0;
    for (const auto &_ : std::filesystem::directory_iterator(cluster_path)) {
      number_of_files++;
    }
    std::vector<Document> _doc_vector(number_of_files);
    for (int i = 0; const auto &document : std::filesystem::directory_iterator(cluster_path)) {
      // Read Document content
      std::ifstream document_content_file(document.path());
      std::string document_content;
      document_content_file >> document_content;
      // Create Document object
      _doc_vector[i++] = Document(document.path().filename(), document_content);
    }
    cluster_array.append(Cluster{cluster_name, cluster_path, _doc_vector});
  }
}

// Getting copy of cluster array
ClusterArray KiViDbCore::Core::get_all_clusters() const {
  return cluster_array.copy();
}

// Delete a cluster by its name
void KiViDbCore::Core::delete_cluster(const std::string &cluster_name) {
  if (cluster_exists(cluster_name)) {
    for (int i = 0; i < cluster_array.size(); i++) {
      if (cluster_array[i].name == cluster_name) {
        std::filesystem::remove_all(cluster_array[i].path);
        cluster_array.remove(i);
        return;
      }
    }
  }
}

// Get the document by its name
Document KiViDbCore::Core::get_document(const std::string &cluster_name, const std::string &document_name) const {
  std::string document_path = db_folder_name + cluster_name + "/" + document_name;
  if (document_exists(cluster_name, document_name)) {
    for (const auto &entry : std::filesystem::directory_iterator(db_folder_name + cluster_name + "/")) {
      if (entry.path().filename() == document_name) {
        // Read Document content
        std::ifstream document_content_file(entry.path());
        std::string document_content;
        document_content_file >> document_content;
        return Document{document_name, document_content};
      }
    }
  }
  return Document{"", ""};
}

// Create a new document
void KiViDbCore::Core::create_document(const std::string &cluster_name,
                                       const std::string &document_name,
                                       const std::string &document_content) {
  std::string document_path = db_folder_name + cluster_name + "/" + document_name;
  if (!document_exists(cluster_name, document_name)) {
    // Create file
    std::ofstream document_file(document_path);
    document_file << document_content;
    document_file.close();
    // Adding document to document array for given cluster
    this->get_cluster(cluster_name).add_document(Document{document_name, document_content});
  }
}

// Updating document content
void KiViDbCore::Core::update_document(const std::string &cluster_name,
                                       const std::string &document_name,
                                       const std::string &document_content) {
  if (document_exists(cluster_name, document_name)) {
    std::string document_path = db_folder_name + cluster_name + "/" + document_name;
    // Erase file content and write new one
    std::ofstream file(document_path);
    file << document_content;
    file.close();            // Close the file
    update_cluster_array(); // Update cluster array (document arrays too)
  }
}

// Delete a document by its name
void KiViDbCore::Core::delete_document(const std::string &cluster_name, const std::string &document_name) {
  if (document_exists(cluster_name, document_name)) {
    std::string document_path = db_folder_name + cluster_name + "/" + document_name;
    std::filesystem::remove(document_path);
    // Remove document from document array for given cluster
    this->get_cluster(cluster_name).remove_document(document_name);
  }
}