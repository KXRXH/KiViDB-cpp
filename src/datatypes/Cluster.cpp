//
// Created by kxrxh on 11/18/22.
//
#include "Cluster.hpp"

// Remove by index
void Cluster::remove_document(unsigned int index) {
  // Check if the index is out of range
  assert(index < document_array.size());
  // Remove element from the Document array
  document_array.erase(document_array.begin() + index);
}

// Remove document by index
void Cluster::remove_document(const std::string &document_name) {
  for (unsigned int i = 0; i < document_array.size(); i++) {
	if (document_array[i].name == document_name) {
	  document_array.erase(document_array.begin() + i);
	  return;
	}
  }
}

// Add Document to the Document array
void Cluster::add_document(const Document &document) {
  // Add Document to the Document array
  document_array.push_back(document);
}
