#include <memory>
#include <string>

#include "grpc++/grpc++.h"

#include "../battleship/board.h"

void RunServer() {
  // Build the server
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Add services
  grpc::EnableDefaultHealthCheckService(true);

  MetadataServiceImpl metadata_service;
  builder.RegisterService(&metadata_service);

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