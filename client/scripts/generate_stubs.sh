ROOT_DIR=$(git rev-parse --show-toplevel)
DIR="$ROOT_DIR/server/proto"
OUT_DIR="$ROOT_DIR/client/src/generated/src"

rm -r "$OUT_DIR"
mkdir -p "$OUT_DIR"

protoc-gen-grpc --proto_path="$DIR" echo.proto --js_out=import_style=commonjs:$OUT_DIR --grpc-web_out=import_style=commonjs,mode=grpcwebtext:$OUT_DIR
#protoc-gen-grpc --proto_path="$DIR" echo.proto --grpc-web_out=mode=grpcwebtext:$OUT_DIR