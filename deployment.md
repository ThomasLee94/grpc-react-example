## Commands with docker & gcloud
`bazel build -c opt src/docker/...`

`bazel build -c opt server:image.tar`

`docker load -i bazel-bin/server/image.tar`

`docker tag bazel/server:image gcr.io/grpc-react-test/echo_server:latest`

`docker push gcr.io/grpc-react-test/echo_server:latest`

`kubectl get pods`

`gcloud container clusters get-credentials cluster-2 --zone us-west1-a --project grpc-react-test`

`kubectl apply -f infra/server/deployment.yaml`

## Debug

`kubectl describe pod <pod_name>`

`kubectl logs <pod_name>`