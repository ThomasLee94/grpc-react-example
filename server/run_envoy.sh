# The linking of network is meant for dev purposes,
# they would be linked with ports on kubernetes for deployment

ROOT_DIR=$(git rev-parse --show-toplevel)
pushd "$ROOT_DIR/server/envoy" 
docker build -t tom/envoy .
popd
docker run -d --network=host tom/envoy 
