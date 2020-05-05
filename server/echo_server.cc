#include "grpc++/grpc++.h"
#include <unistd.h>
#include <string>

#include "server/proto/echo.grpc.pb.h"
#include "echo_service_impl.h"

using grpc::Server;
using grpc::ServerBuilder;

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  EchoServiceImpl service;
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
