## Commands with docker & gcloud
### Backend
`gcloud auth login`

`bazel build -c opt server/docker/...`

`bazel build -c opt server:image.tar`

`docker load -i bazel-bin/server/image.tar`

`docker tag bazel/server:image gcr.io/grpc-react-test/echo_server:latest`

`docker push gcr.io/grpc-react-test/echo_server:latest`

`kubectl get pods`

`gcloud container clusters get-credentials cluster-2 --zone us-west1-a --project grpc-react-test`

`kubectl apply -f infra/server/deployment.yaml`

### Envoy
`bazel build -c opt server/edge_envoy/...`

`bazel build -c opt server/edge_envoy:image_envoy.tar`

`docker load -i bazel-bin/server/edge_envoy/image_envoy.tar`

run image locally - `docker run bazel/server/edge_envoy:image_envoy`

`docker tag bazel/server/edge_envoy:image_envoy gcr.io/grpc-react-test/edge-envoy:v1.14.1`

`docker push gcr.io/grpc-react-test/edge-envoy:v1.14.1`

`kubectl apply -f server/edge_envoy/deployment.yaml`

`kubectl apply -f infra/microservices/server/service.yaml`

`kubectl apply -f infra/microservices/edge_envoy/service.yaml`

## Debug

`kubectl describe pod <pod_name>`

`kubectl logs <pod_name>`
