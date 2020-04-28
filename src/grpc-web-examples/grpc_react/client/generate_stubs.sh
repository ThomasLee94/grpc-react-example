DIR="./../server/proto"
OUT_DIR="./generated/src"

protoc -I="$DIR" echo.proto --js_out=import_style=commonjs:$OUT_DIR

protoc -I="$DIR" echo.proto --grpc-web_out=import_style=commonjs,mode=grpcwebtext:$OUT_DIR