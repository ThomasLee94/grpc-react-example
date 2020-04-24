#include "src/battleship_service/battleship_service_impl.h"

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"
#include "src/util/status_macros.h"

namespace battleshipservice  {

grpc::Status UnaryServiceImpl::BattleShip(
    grpc::ServerContext* context,
    const ::battleshipservice::BattleShipRequest* request,
    ::battleshipservice::BattleShipResponse* response) {
  RETURN_IF_NE(request->message(), "Is this working?") << "Expected message 'Is this working?'.";
  response->set_message("It is working!");
  return grpc::Status::OK;
}

}  // namespace battleshipservice