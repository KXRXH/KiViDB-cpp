//
// Created by kxrxh on 11/18/22.
//
#include "Cluster.hpp"
void Cluster::remove_document(unsigned int index) {
  assert(index < document_array_size);
  auto *new_document_array = new Document[document_array_size - 1];
  for (int i = 0; i < index; i++) {
	new_document_array[i] = std::move(document_array[i]);
  }
  for (int i = index + 1; i < document_array_size; i++) {
	new_document_array[i - 1] = std::move(document_array[i]);
  }
  delete[] document_array;
  document_array = new_document_array;
  document_array_size--;
}

void Cluster::add_document(const Document &document) {
  auto *new_document_array = new Document[++document_array_size];
  for (int i = 0; i < document_array_size - 1; i++) {
	new_document_array[i] = std::move(document_array[i]);
  }
  new_document_array[document_array_size - 1] = document;
  delete[] document_array;
  document_array = new_document_array;
}
