#include <memory>
#include <string>

#include "absl/strings/str_cat.h"
#include "glog/logging.h"
#include "grpc++/grpc++.h"
#include "grpc++/health_check_service_interface.h"

#include "src/microservices/room_metadata/metadata_service_impl.h"
#include "src/util/base/flags.h"
#include "src/util/interceptors/status_logger.h"
#include "src/util/net/service_spec.h"

void RunServer() {
  // Build the server
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Add services
  grpc::EnableDefaultHealthCheckService(true);

  MetadataServiceImpl metadata_service;
  builder.RegisterService(&metadata_service);

  // Add interceptors
  std::vector<
      std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>>
      interceptors;
  interceptors.push_back(::util::interceptors::NewStatusLoggerFactory());
  builder.experimental().SetInterceptorCreators(std::move(interceptors));

  // Start the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  server->Wait();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  util::ParseCommandLineFlags(argc, argv);
  RunServer();
  return 0;
}