#include <cassert>

//
// Created by kxrxh on 11/15/22.
//

#ifndef KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
#define KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
struct Cluster {
  std::string name;
  std::string path;
  Cluster(const std::string name, std::string path) : name(std::move(name)), path(std::move(path)) {};
  Cluster() = default;
  // Return stdout stream
  friend std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
	os << "Cluster_name: " << cluster.name << " ";
	os << "Cluster_path: " << cluster.path << std::endl;
  }
};

class ClusterArray {
private:
  bool _debug = false;
  unsigned int cluster_array_size;
  Cluster *cluster_array_data;
public:
  // Class constructor
  ClusterArray() {
	cluster_array_size = 0;
	cluster_array_data = nullptr;
  }
  explicit ClusterArray(bool debug_) : ClusterArray() {
	_debug = debug_;
	if (_debug) {
	  std::cout << "[DEBUG] ClusterArray constructor called" << std::endl;
	}
  }
  // Append a new cluster to the cluster array
  void append(Cluster cluster) {
	cluster_array_size++;
	// Create a new cluster array
	auto *new_cluster_array_data = new Cluster[cluster_array_size];
	for (int i = 0; i < cluster_array_size - 1; i++) {
	  new_cluster_array_data[i] = std::move(cluster_array_data[i]);
	}
	// Append the new cluster
	new_cluster_array_data[cluster_array_size - 1] = std::move(cluster);
	// Deleting old cluster array data
	delete[] cluster_array_data;
	// Assigning new cluster array data
	cluster_array_data = new_cluster_array_data;
  }
  // Remove element from cluster array by its index
  void remove(unsigned int index) {
	assert(index < cluster_array_size);
	// Create a new cluster array
	auto *new_cluster_array_data = new Cluster[cluster_array_size - 1];
	for (int i = 0; i < index; i++) {
	  new_cluster_array_data[i] = std::move(cluster_array_data[i]);
	}
	for (int i = index + 1; i < cluster_array_size; i++) {
	  new_cluster_array_data[i - 1] = std::move(cluster_array_data[i]);
	}
	// Deleting old cluster array data
	delete[] cluster_array_data;
	// Assigning new cluster array data
	cluster_array_data = new_cluster_array_data;
	cluster_array_size--;
  }
  // Get ClusterArray size
  [[nodiscard]] unsigned int size() const {
	return cluster_array_size;
  }
  // Clear ClusterArray
  void clear() {
	cluster_array_size = 0;
	delete[] cluster_array_data;
  }
  // Return ClusterArray copy
  [[nodiscard]] ClusterArray copy() const {
	ClusterArray copy_of_cluster_array(true);
	for (int i = 0; i < cluster_array_size; i++) {
	  copy_of_cluster_array.append(Cluster(cluster_array_data[i].name, cluster_array_data[i].path));
	}
	return copy_of_cluster_array;
  }
  // Class destructor
  ~ClusterArray() {
	if (_debug) {
	  std::cout << "[DEBUG] ClusterArray destructor called" << std::endl;
	}
	// delete[] cluster_array_data;
	cluster_array_size = 0;
  }
  // Overloading the [] operator
  [[nodiscard]] Cluster &operator[](unsigned int index) const {
	return cluster_array_data[index];
  }
};
#endif //KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
