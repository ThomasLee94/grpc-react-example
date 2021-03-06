
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

#include "echo_service_impl.h"

#include "grpc++/grpc++.h"
#include <unistd.h>
#include <string>

#include "server/proto/echo.grpc.pb.h"

using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using echo::EchoRequest;
using echo::EchoResponse;
using echo::EchoService;


EchoServiceImpl::EchoServiceImpl() {}
EchoServiceImpl::~EchoServiceImpl() {}

void EchoServiceImpl::CopyClientMetadataToResponse(ServerContext* context) {
  for (auto& client_metadata : context->client_metadata()) {
    context->AddInitialMetadata(std::string(client_metadata.first.data(),
                                            client_metadata.first.length()),
                                std::string(client_metadata.second.data(),
                                            client_metadata.second.length()));
    context->AddTrailingMetadata(
        std::string(client_metadata.first.data(),
                    client_metadata.first.length()),
        std::string(client_metadata.second.data(),
                    client_metadata.second.length()));
  }
}

Status EchoServiceImpl::Echo(ServerContext* context, const EchoRequest* request,
                             EchoResponse* response) {
  CopyClientMetadataToResponse(context);
  response->set_message(request->message());
  return Status::OK;
}
