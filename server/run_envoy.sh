ROOT_DIR=$(git rev-parse --show-toplevel)
pushd "$ROOT_DIR/src/grpc-web-examples/grpc_react/server/envoy" 
docker build -t tom/envoy .
popd
docker run -d --network=host tom/envoy 
