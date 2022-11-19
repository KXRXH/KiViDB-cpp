#include "core/core.hpp"
#include "api/api.hpp"
#include "boost/process/env.hpp"
#include "regex"
using namespace std;

int main() {
  // Getting env variables
  boost::process::environment env = boost::this_process::environment();
  std::string kividb_path = env["KIVIDB_PATH"].to_string();
  std::string kividb_port = env["KIVIDB_PORT"].to_string();
  int int_port = 8085;
  if (std::regex_match(kividb_port, std::regex("[0-9]+"))) {
	int_port = std::stoi(kividb_port);
  };
  Api api((KiViDbCore::Core((!kividb_path.empty() ? kividb_path : "../database/kividb"))));
  // api.init_document_routes();
  api.init_cluster_routes();
  api.listen_to(int_port);
}