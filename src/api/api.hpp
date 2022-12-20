//
// Created by kxrxh on 11/19/22.
//

#ifndef KIVIDB_CPP_SRC_API_API_HPP
#define KIVIDB_CPP_SRC_API_API_HPP

#include "crow_all.h"
#include "../core/core.hpp"

class Api {
private:
  crow::App<crow::CORSHandler> app;
  KiViDbCore::Core core;
public:
  explicit Api(const KiViDbCore::Core &Core) : core(Core) {};

  void init_cluster_routes();

  void init_document_routes();

  void listen_to(int _port);
};

#endif //KIVIDB_CPP_SRC_API_API_HPP
