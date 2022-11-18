//
// Created by kxrxh on 11/18/22.
//

#ifndef KIVIDB_CPP_SRC_DATATYPES_DOCUMENT_HPP
#define KIVIDB_CPP_SRC_DATATYPES_DOCUMENT_HPP
#include "iostream"

struct Document {
  std::string name;
  std::string data;
  Document() = default;
  Document(std::string name_, std::string data_) {
	name = std::move(name_);
	data = std::move(data_);
  }
  friend std::ostream &operator<<(std::ostream &os, const Document &document) {
	os << "Document name: " << document.name << "\n";
	os << "Document data: " << document.data << "\n";
	return os;
  }
};
#endif //KIVIDB_CPP_SRC_DATATYPES_DOCUMENT_HPP
