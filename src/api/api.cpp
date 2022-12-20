//
// Created by kxrxh on 11/19/22.
//
#include "api.hpp"

// Running REST API server
void Api::listen_to(int _port) {
  // Home route
  CROW_ROUTE(app, "/")([]() {
    return "Hello from KiViDB";
  });
  app.port(_port).multithreaded().run();
}

void Api::init_cluster_routes() {
  // Cluster routes
  //
  // Create a new [route]
  //
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
  //
  // Delete a cluster [route]
  //
  CROW_ROUTE(app, "/cluster/delete/<string>").methods("DELETE"_method)([&](const crow::request &req,
                                                                           crow::response &res,
                                                                           const std::string &_cluster_id) {
    crow::json::wvalue json;
    // Check if the cluster already exists
    if (core.cluster_exists(_cluster_id)) {
      core.delete_cluster(_cluster_id);
      res.code = 200;
      json["message"] = "Cluster successfully deleted";
      res.body = json.dump();
      res.end();
      return;
    }
    res.code = 400;
    json["message"] = "Cluster doesn't exists";
    res.body = json.dump();
    res.end();
  });
  //
  // Getting Cluster by name [route]
  //
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
  //
  // Getting all clusters [route]
  //
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

void Api::init_document_routes() {
  // Document routes
  //
  // Create new document [route]
  //
  CROW_ROUTE(app, "/document/create/<string>/<string>").methods("POST"_method)([&](const crow::request &req,
                                                                                   crow::response &res,
                                                                                   const std::string &_cluster_id,
                                                                                   const ::std::string &_document_id) {
    crow::json::wvalue json;
    // Check if the document already exists
    if (core.document_exists(_cluster_id, _document_id)) {
      res.code = 400;
      json["message"] = "Document already exists";
      res.body = json.dump();
      res.end();
      return;
    }
    // Converting string to JSON object
    auto response_json = crow::json::load(req.body);
    // Check if the JSON is valid
    if (response_json.keys().empty()) {
      res.code = 400;
      json["message"] = "Invalid JSON";
      res.body = json.dump();
      res.end();
      return;
    }
    // Creating new document
    core.create_document(_cluster_id, _document_id, response_json["content"].s());
    res.code = 200;
    json["message"] = "Document successfully created";
    res.body = json.dump();
    res.end();
  });
  //
  // Delete the document [route]
  //
  CROW_ROUTE(app, "/document/delete/<string>/<string>").methods("DELETE"_method)([&](const crow::request &req,
                                                                                     crow::response &res,
                                                                                     const std::string &_cluster_id,
                                                                                     const ::std::string &_document_id) {
    crow::json::wvalue json;
    // Check if the document exists
    if (core.document_exists(_cluster_id, _document_id)) {
      res.code = 200;
      core.delete_document(_cluster_id, _document_id);
      json["message"] = "Document successfully deleted";
      res.body = json.dump();
      res.end();
      return;
    }
    res.code = 400;
    json["message"] = "Document doesn't exists";
    res.body = json.dump();
    res.end();
  });
  //
  // Update the document [route]
  //
  CROW_ROUTE(app, "/document/patch/<string>/<string>").methods("PATCH"_method)([&](const crow::request &req,
                                                                                   crow::response &res,
                                                                                   const std::string &_cluster_id,
                                                                                   const ::std::string &_document_id) {
    crow::json::wvalue json;
    // Check if the document exists
    if (core.document_exists(_cluster_id, _document_id)) {
      // Converting string to JSON object
      auto response_json = crow::json::load(req.body);
      // Check if the JSON is valid
      if (response_json.keys().empty()) {
        res.code = 400;
        json["message"] = "Invalid JSON";
        res.body = json.dump();
        res.end();
        return;
      }
      res.code = 200;
      core.update_document(_cluster_id, _document_id, response_json["content"].s());
      json["message"] = "Document successfully patched";
      res.body = json.dump();
      res.end();
      return;
    }
    res.code = 400;
    json["message"] = "Document doesn't exists";
    res.body = json.dump();
    res.end();
  });
  //
  // Get the document value [route]
  //
  CROW_ROUTE(app, "/document/get/<string>/<string>").methods("GET"_method)([&](const crow::request &req,
                                                                               crow::response &res,
                                                                               const std::string &_cluster_id,
                                                                               const ::std::string &_document_id) {
    crow::json::wvalue json;
    // Check if the document exists
    if (core.document_exists(_cluster_id, _document_id)) {
      res.code = 200;
      json["message"] = core.get_document(_cluster_id, _document_id).content;
      res.body = json.dump();
      res.end();
      return;
    }
    res.code = 400;
    json["message"] = "Document doesn't exists";
    res.body = json.dump();
    res.end();
  });
}