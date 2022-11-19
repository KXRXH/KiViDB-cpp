#include "crow_all.h"
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
	for (auto &doc : cluster.document_array) {
	  document_array.push_back(doc.name);
	}
	crow::json::wvalue x;
	x["cluster_name"] = cluster.name;
	x["cluster_documents"] = document_array;
	crow::json::wvalue result = x;
	return crow::response(std::move(result));
  });
  CROW_ROUTE(app, "/cluster/get/all")([core]() {
	auto cluster_array = core.get_all_clusters();
    std::vector<crow::json::wvalue> cluster_array_json;
	for (int i = 0; i < cluster_array.size(); i++) {
      auto cluster = cluster_array[i];
      std::vector<std::string> document_array;
      for (auto &doc : cluster.document_array) {
        document_array.push_back(doc.name);
      }
      crow::json::wvalue x;
      x["cluster_name"] = cluster.name;
      x["cluster_documents"] = document_array;
      cluster_array_json.push_back(x);
    }
	return crow::response(std::move(cluster_array_json));
  });
  app.bindaddr("127.0.0.1").port(18080).run();
}