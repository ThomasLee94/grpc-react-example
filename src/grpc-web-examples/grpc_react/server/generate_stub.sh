DIR="./proto"
OUT_DIR="./generated"

protoc -I="$DIR" --cpp_out="$OUT_DIR" echo.proto

protoc -I="$DIR" --grpc_out="$OUT_DIR" --plugin=protoc-gen-grpc=grpc_cpp_plugin echo.proto
# protoc -I="$DIR" --grpc_out="$OUT_DIR" --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` echo.proto