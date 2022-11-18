//
// Created by kxrxh on 11/18/22.
//

#ifndef KIVIDB_CPP_SRC_DATATYPES_CLUSTER_HPP
#define KIVIDB_CPP_SRC_DATATYPES_CLUSTER_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include "Document.hpp"
struct Cluster {
  std::string name;
  std::string path;
  std::vector<Document> document_array;
  unsigned int document_array_size = 0;
  Cluster(std::string name, std::string path) : name(std::move(name)), path(std::move(path)) {};
  Cluster(std::string name, std::string path, std::vector<Document> document_array)
      : name(std::move(name)), path(std::move(path)), document_array(std::move(document_array)) {}
  Cluster() = default;
  // Add document to the document array
  void add_document(const Document &document);
  // Remove document from the document array
  void remove_document(unsigned int index);
  // Return stdout stream
  friend std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
    os << "Cluster_name: " << cluster.name << " ";
    os << "Cluster_path: " << cluster.path << std::endl;
    return os;
  }
};

#endif //KIVIDB_CPP_SRC_DATATYPES_CLUSTER_HPP
