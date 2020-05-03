DIR="./../server/proto"
OUT_DIR="./src/generated/src"

protoc-gen-grpc -I="$DIR" echo.proto --ts_out=$OUT_DIR

protoc-gen-grpc -I="$DIR" echo.proto --grpc-web_out=mode=grpcwebtext:$OUT_DIR