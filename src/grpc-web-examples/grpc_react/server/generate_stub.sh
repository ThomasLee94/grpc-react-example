DIR="./proto"
OUT_DIR="./generated"

protoc -I="$DIR" --cpp_out="$OUT_DIR" echo.proto