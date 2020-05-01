import * as pb_1 from "google-protobuf";
import * as grpc_1 from "grpc";
export namespace echo {
    export class EchoRequest extends pb_1.Message {
        constructor(data?: any[] | {
            message?: string;
        }) {
            super();
            pb_1.Message.initialize(this, Array.isArray(data) && data, 0, -1, [], null);
            if (!Array.isArray(data) && typeof data == "object") {
                this.message = data.message;
            }
        }
        get message(): string | undefined {
            return pb_1.Message.getFieldWithDefault(this, 1, undefined) as string | undefined;
        }
        set message(value: string) {
            pb_1.Message.setField(this, 1, value);
        }
        toObject() {
            return {
                message: this.message
            };
        }
        serialize(w?: pb_1.BinaryWriter): Uint8Array | undefined {
            const writer = w || new pb_1.BinaryWriter();
            if (this.message !== undefined)
                writer.writeString(1, this.message);
            if (!w)
                return writer.getResultBuffer();
        }
        static deserialize(bytes: Uint8Array | pb_1.BinaryReader): EchoRequest {
            const reader = bytes instanceof Uint8Array ? new pb_1.BinaryReader(bytes) : bytes, message = new EchoRequest();
            while (reader.nextField()) {
                if (reader.isEndGroup())
                    break;
                switch (reader.getFieldNumber()) {
                    case 1:
                        message.message = reader.readString();
                        break;
                    default: reader.skipField();
                }
            }
            return message;
        }
    }
    export class EchoResponse extends pb_1.Message {
        constructor(data?: any[] | {
            message?: string;
        }) {
            super();
            pb_1.Message.initialize(this, Array.isArray(data) && data, 0, -1, [], null);
            if (!Array.isArray(data) && typeof data == "object") {
                this.message = data.message;
            }
        }
        get message(): string | undefined {
            return pb_1.Message.getFieldWithDefault(this, 1, undefined) as string | undefined;
        }
        set message(value: string) {
            pb_1.Message.setField(this, 1, value);
        }
        toObject() {
            return {
                message: this.message
            };
        }
        serialize(w?: pb_1.BinaryWriter): Uint8Array | undefined {
            const writer = w || new pb_1.BinaryWriter();
            if (this.message !== undefined)
                writer.writeString(1, this.message);
            if (!w)
                return writer.getResultBuffer();
        }
        static deserialize(bytes: Uint8Array | pb_1.BinaryReader): EchoResponse {
            const reader = bytes instanceof Uint8Array ? new pb_1.BinaryReader(bytes) : bytes, message = new EchoResponse();
            while (reader.nextField()) {
                if (reader.isEndGroup())
                    break;
                switch (reader.getFieldNumber()) {
                    case 1:
                        message.message = reader.readString();
                        break;
                    default: reader.skipField();
                }
            }
            return message;
        }
    }
    export var EchoService = {
        Echo: {
            path: "/echo.EchoService/Echo",
            requestStream: false,
            responseStream: false,
            requestType: echo.EchoRequest,
            responseType: echo.EchoResponse,
            requestSerialize: (message: EchoRequest) => Buffer.from(message.serialize()),
            requestDeserialize: (bytes: Buffer) => EchoRequest.deserialize(new Uint8Array(bytes)),
            responseSerialize: (message: EchoResponse) => Buffer.from(message.serialize()),
            responseDeserialize: (bytes: Buffer) => EchoResponse.deserialize(new Uint8Array(bytes))
        }
    };
    export class EchoServiceClient extends grpc_1.makeGenericClientConstructor(EchoService, "EchoService", {}) {
        constructor(address: string, credentials: grpc_1.ChannelCredentials) {
            super(address, credentials)
        }
    }
}
