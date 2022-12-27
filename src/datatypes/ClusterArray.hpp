//
// Created by kxrxh on 11/15/22.
//
#ifndef KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
#define KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP

#include "Cluster.hpp"
#include "cassert"

class ClusterArray {
private:
  std::vector<Cluster> cluster_array;
public:
  explicit ClusterArray() = default;

  // Append a new Cluster to the Cluster array
  void append(const Cluster &cluster);

  // Remove element from Cluster array by its index
  void remove(unsigned int index);

  // Get cluster_array size
  [[nodiscard]] unsigned int size() const;

  // Clear cluster_array
  void clear();

  // Return cluster_array copy
  [[nodiscard]] ClusterArray copy() const;

  // Overloading the [] operator
  [[nodiscard]] Cluster operator[](unsigned int index) const;

  ~ClusterArray() {
    cluster_array.clear();
  }
};

#endif //KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
