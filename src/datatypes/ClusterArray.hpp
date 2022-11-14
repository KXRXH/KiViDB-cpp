//
// Created by kxrxh on 11/15/22.
//

#ifndef KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
#define KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
struct Cluster {
  const char *name;
  const char *path;
};

class ClusterArray {
private:
  unsigned int cluster_array_size;
  Cluster *cluster_array_data;
public:
  // Class constructor
  ClusterArray() {
	cluster_array_size = 0;
	cluster_array_data = nullptr;
  }
  // Append a new cluster to the cluster array
  void append(Cluster cluster) {
	cluster_array_size++;
	auto *new_cluster_array_data = new Cluster[cluster_array_size];
	for (unsigned int i = 0; i < cluster_array_size - 1; i++) {
	  new_cluster_array_data[i] = cluster_array_data[i];
	}
	new_cluster_array_data[cluster_array_size - 1] = cluster;
  }
  // Class destructor
  ~ClusterArray() {
	cluster_array_size = 0;
	delete[] cluster_array_data;
  }
};
#endif //KIVIDBCPP_SRC_DATATYPES_CLUSTERARRAY_HPP
