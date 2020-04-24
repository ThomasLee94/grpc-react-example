#ifndef SRC_BATTLESHIP_UNARY_SERVICE_IMPL_H
#define SRC_BATTLESHIP_UNARY_SERVICE_IMPL_H

#include "grpc++/grpc++.h"

#include "src/battleshipservice/proto/services.grpc.pb.h"

namespace battleshipservice {

class UnaryServiceImpl final : public ::battleshipservice::UnaryService::Service {
 public:
  grpc::Status BattleShip(
      grpc::ServerContext* context,
      const ::battleshipservice::BattleShipRequest* request,
      ::battleshipservice::BattleShipResponse* response) override;
};

}  // namespace battleshipservice