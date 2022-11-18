//
// Created by kxrxh on 11/18/22.
//
#include "Cluster.hpp"
void Cluster::remove_document(unsigned int index) {
  // Check if the index is out of range
  assert(index < document_array.size());
  // Remove element from the document array
  document_array.erase(document_array.begin() + index);
}

void Cluster::add_document(const Document &document) {
  // Add document to the document array
  document_array.push_back(document);
}
