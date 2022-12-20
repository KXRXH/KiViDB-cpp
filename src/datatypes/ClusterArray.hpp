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
  // Class constructor
  explicit ClusterArray() = default;

  // Append a new Cluster to the Cluster array
  void append(const Cluster &cluster) {
    // Create a new Cluster array
    cluster_array.push_back(cluster);
  }

  // Remove element from Cluster array by its index
  void remove(unsigned int index) {
    // Check if the index is out of range
    assert(index < cluster_array.size());
    // Remove element from the Cluster array`
    cluster_array.erase(cluster_array.begin() + index);
  }

  // Get cluster_array size
  [[nodiscard]] unsigned int size() const {
    return cluster_array.size();
  }

  // Clear cluster_array
  void clear() {
    cluster_array.clear();
  }

  // Return cluster_array copy
  [[nodiscard]] ClusterArray copy() const {
    ClusterArray copy_of_cluster_array;
    for (const auto &cluster : cluster_array) {
      copy_of_cluster_array.append(cluster);
    }
    return copy_of_cluster_array;
  }

  // Class destructor
  ~ClusterArray() {
    cluster_array.clear();
  }

  // Overloading the [] operator
  [[nodiscard]] Cluster operator[](unsigned int index) const {
    return cluster_array[index];
  }
};

#endif //KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
