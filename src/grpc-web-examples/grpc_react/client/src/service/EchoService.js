/*eslint-disabled */
//@ts-nocheck

// import {EchoServiceClient} from '../generated/src/echo_grpc_web_pb'
import EchoRequest from '../generated/src/echo.ts'
import EchoServiceClient from '../generated/src/echo_grpc_web_pb'
// const EchoServiceClient = require('../generated/src/echo_grpc_web_pb.js');


const client = new EchoServiceClient('localhost:8080');

export async function echoServiceEndpointRPC() {
    const request = new EchoRequest();
    request.setMessage("Testing the echo rpc!");

    const output = await client.Echo(request) 
    return output
}

// const client = new EchoServiceClient('localhost:8080');
// const request = new EchoRequest();


// request.setMessage('Hello World!');
    
// const metadata = {'custom-header-1': 'value1'};
    
// client.Echo(request, metadata, (err, response) => {
//     console.log("Testing")
// });
 
// const echoapp = new App();
// const response = await echoapp.Echo("Yo")
// response.getMessage()

// module.exports = {
//     echoServiceEndpointRPC
// }