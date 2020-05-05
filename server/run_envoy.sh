ROOT_DIR=$(git rev-parse --show-toplevel)
pushd "$ROOT_DIR/server/envoy" 
docker build -t tom/envoy .
popd
docker run -d --network=host tom/envoy 
