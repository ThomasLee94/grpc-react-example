const { googleRPC } = require("reactRPC")
​
const messages = require("../helloworld_pb.js")
​
const services = require("../helloworld_grpc_web_pb.js")
​
const URL = "http://" + window.location.hostname + ":8080"
​
googleRPC.build(messages, services, URL)