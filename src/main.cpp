#include "crow.h"
#include "core/core.hpp"

int main() {
  crow::SimpleApp app;
  KiViDbCore::Core core("../database/kividb/");
  CROW_ROUTE(app, "/")([]() {
	return "Hello from KiViDB";
  });
  CROW_ROUTE(app, "/cluster/get/<string>")([core](std::string _cluster_id) {
	crow::json::wvalue x;
	auto cluster = core.get_cluster(_cluster_id);
	char *json_str;
	sprintf(json_str, R"({ "cluster_id": "%s", "document_array_size": %d)", cluster.name.c_str(), cluster.document_array_size);
	x["clusters"] = crow::json::load(json_str);
	return x;
  });
  app.bindaddr("127.0.0.1").port(18080).run();
}