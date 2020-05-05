#ifndef NET_GRPC_GATEWAY_EXAMPLES_ECHO_ECHO_SERVICE_IMPL_H_
#define NET_GRPC_GATEWAY_EXAMPLES_ECHO_ECHO_SERVICE_IMPL_H_

/**
 *
 * Copyright 2018 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "grpc++/grpc++.h"
#include <unistd.h>
#include <string>

#include "src/grpc-web-examples/grpc_react/server/proto/echo.grpc.pb.h"

class EchoServiceImpl final :
    public echo::EchoService::Service {
 public:
  EchoServiceImpl();
  ~EchoServiceImpl() override;

  void CopyClientMetadataToResponse(grpc::ServerContext* context);
  grpc::Status Echo(
      grpc::ServerContext* context,
      const echo::EchoRequest* request,
      echo::EchoResponse* response) override;
};

#endif  // NET_GRPC_GATEWAY_EXAMPLES_ECHO_ECHO_SERVICE_IMPL_H_
