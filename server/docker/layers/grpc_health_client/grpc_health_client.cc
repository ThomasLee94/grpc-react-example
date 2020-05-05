#include <chrono>  // NOLINT(build/c++11)
#include <string>

#include "absl/flags/flag.h"
#include "absl/time/time.h"
#include "glog/logging.h"
#include "grpc++/grpc++.h"
#include "src/proto/grpc/health/v1/health.grpc.pb.h"

#include "server/util/flags.h"

ABSL_FLAG(std::string, server, "localhost:50051", "");

ABSL_FLAG(absl::Duration, timeout, absl::Seconds(1), "");
ABSL_FLAG(std::string, service, "", "");

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  util::ParseCommandLineFlags(argc, argv);

  grpc::health::v1::HealthCheckRequest request;
  if (!absl::GetFlag(FLAGS_service).empty()) {
    request.set_service(absl::GetFlag(FLAGS_service));
  }

  grpc::ClientContext context;
  context.set_deadline(
      std::chrono::system_clock::now() +
      absl::ToChronoMilliseconds(absl::GetFlag(FLAGS_timeout)));

  auto stub =
      grpc::health::v1::Health::NewStub(
          grpc::CreateChannel(
              absl::GetFlag(FLAGS_server), grpc::InsecureChannelCredentials()));

  grpc::health::v1::HealthCheckResponse response;
  grpc::Status status = stub->Check(&context, request, &response);

  if (!status.ok()) {
    LOG(ERROR) << "Health-check failed with error: " << status.error_message();
    return 1;
  }

  LOG(INFO) << response.DebugString();
  return 0;
}