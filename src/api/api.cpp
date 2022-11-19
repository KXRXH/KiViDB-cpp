//
// Created by kxrxh on 11/19/22.
//

#include "api.hpp"
void Api::listen_to(int _port) {
  // Home route
  CROW_ROUTE(app, "/")([]() {
	return "Hello from KiViDB";
  });
  app.port(_port).multithreaded().run();
}
void Api::init_cluster_routes() {
  // Cluster routes
  // Create a new cluster
  CROW_ROUTE(app, "/cluster/create/<string>").methods("POST"_method)([&](const crow::request &req,
												  crow::response &res,
												  const std::string &_cluster_id) {
	crow::json::wvalue json;
	// Check if the cluster already exists
	if (core.cluster_exists(_cluster_id)) {
	  res.code = 400;
	  json["message"] = "Cluster already exists";
	  res.body = json.dump();
	  res.end();
	  return;
	}
	core.create_cluster(_cluster_id);
	res.code = 200;
	json["message"] = "Cluster successfully created";
	res.body = json.dump();
	res.end();
  });
  // Delete a cluster
  CROW_ROUTE(app, "/cluster/delete/<string>").methods("DELETE"_method)([&](const crow::request &req,
												  crow::response &res,
												  const std::string &_cluster_id) {
	crow::json::wvalue json;
	// Check if the cluster already exists
	if (!core.cluster_exists(_cluster_id)) {
	  res.code = 400;
	  json["message"] = "Cluster doesn't exists";
	  res.body = json.dump();
	  res.end();
	  return;
	}
	core.delete_cluster(_cluster_id);
	res.code = 200;
	json["message"] = "Cluster successfully deleted";
	res.body = json.dump();
	res.end();
  });
  // Getting Cluster by name
  CROW_ROUTE(app, "/cluster/get/filter/<string>")([&](const std::string &_cluster_id) {
	Cluster cluster = this->core.get_cluster(_cluster_id);
	// Getting all documents from the Cluster
	std::vector<std::string> document_array(cluster.document_array.size());
	for (int i = 0; auto &doc : cluster.document_array) {
	  document_array[i++] = doc.name;
	}
	// Setting up Cluster info
	crow::json::wvalue cluster_information;
	cluster_information["cluster_name"] = cluster.name;
	cluster_information["cluster_documents"] = document_array;
	std::vector<crow::json::wvalue> cluster_array_json;
	// Pushing Cluster info to Cluster array
	cluster_array_json.push_back(cluster_information);
	crow::json::wvalue result;
	result["message"] = std::move(cluster_array_json);
	return crow::response(std::move(result));
  });
  // Getting all clusters
  CROW_ROUTE(app, "/cluster/get/all")([&]() {
	auto cluster_array = this->core.get_all_clusters();
	std::vector<crow::json::wvalue> cluster_array_json(cluster_array.size());
	for (int i = 0; i < cluster_array.size(); i++) {
	  // Getting Cluster
	  auto cluster = cluster_array[i];
	  // Filling Document array
	  std::vector<std::string> document_array(cluster.document_array.size());
	  for (int n = 0; auto &doc : cluster.document_array) {
		document_array[n++] = std::move(doc.name);
	  }
	  // Setting up Cluster info
	  crow::json::wvalue cluster_information;
	  cluster_information["cluster_name"] = cluster.name;
	  cluster_information["cluster_documents"] = document_array;
	  // Adding Cluster info to Cluster array
	  cluster_array_json[i] = std::move(cluster_information);
	}
	crow::json::wvalue result;
	result["message"] = std::move(cluster_array_json);
	return crow::response(std::move(result));
  });
}
