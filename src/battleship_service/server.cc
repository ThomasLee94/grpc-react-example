#include <memory>
#include <string>
#include <iostream>

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"
#include "src/battleship_service/battleship_service_impl.h"
// #include "src/battleship_game/game.h"

using ::battleshipservice::UnaryServiceImpl;
// using ::battleshipservice::ServerStreamingHandler;

void RunServer() {
  // Build the server
  grpc::ServerBuilder builder;
  builder.AddListeningPort("localhost:5000", grpc::InsecureServerCredentials());

  // Add services
  grpc::EnableDefaultHealthCheckService(true);

  UnaryServiceImpl unary_service;
  builder.RegisterService(&unary_service);

  // Start the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
  // LOG(INFO) << "Server listening on " << server_address;

}

int main(int argc, char** argv) {
  // battleship::Game game;
  // std::cout << game.IsStarted(); 
  // return 0;
  RunServer();
  return 0;
}