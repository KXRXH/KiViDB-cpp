//
// Created by kxrxh on 12/27/22.
//
#include "ClusterArray.hpp"

void ClusterArray::append(const Cluster &cluster) {
  // Create a new Cluster array
  cluster_array.push_back(cluster);
}

void ClusterArray::remove(unsigned int index) {
  // Check if the index is out of range
  assert(index < cluster_array.size());
  // Remove element from the Cluster array`
  cluster_array.erase(cluster_array.begin() + index);
}
unsigned int ClusterArray::size() const {
  return this->cluster_array.size();
}

void ClusterArray::clear() {
  cluster_array.clear();
}

ClusterArray ClusterArray::copy() const {
  ClusterArray copy_of_cluster_array;
  for (const auto &cluster : cluster_array) {
    copy_of_cluster_array.append(cluster);
  }
  return copy_of_cluster_array;
}

Cluster ClusterArray::operator[](unsigned int index) const {
  return cluster_array[index];
}