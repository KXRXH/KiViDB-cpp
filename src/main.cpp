#include "crow.h"
#include "core/core.hpp"

int main() {
  crow::SimpleApp app;
  KiViDbCore::Core core("../database/kividb/");
  CROW_ROUTE(app, "/")([]() {
	return "Hello from KiViDB";
  });
  CROW_ROUTE(app, "/cluster/get/filter/<string>")([core](const std::string &_cluster_id) {
	Cluster cluster = core.get_cluster(_cluster_id);
	std::vector<std::string> document_array;
	for (auto &i : cluster.document_array) {
	  document_array.push_back(i.name);
	}
	crow::json::wvalue x;
	x["cluster_name"] = cluster.name;
	x["cluster_documents"] = document_array;
	crow::json::wvalue result = x;
	return crow::response(std::move(result));
  });
  // TODO
  CROW_ROUTE(app, "/cluster/get/all")([core]() {
	auto cluster_array = core.get_all_clusters();
	std::vector<std::string> document_array;
	for (auto &i : cluster.document_array) {
	  document_array.push_back(i.name);
	}
	crow::json::wvalue x;
	x["cluster_name"] = cluster.name;
	x["cluster_documents"] = document_array;
	crow::json::wvalue result = x;
	return crow::response(std::move(result));
  });
  app.bindaddr("127.0.0.1").port(18080).run();
}