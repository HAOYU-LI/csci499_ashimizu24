#include <google/protobuf/text_format.h>
#include <iostream>
#include <string.h>
#include <google/protobuf/any.h>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "func.grpc.pb.h"
#include "func.pb.h"
#include "warble_code.h"
#include "../commandline/events.h" 

using func::KeyValueStore;

//TODO - compile error saying KeyValueStore has not been declared

// Server that takes in processes requests from the commandline and redirects them to the kvstore
class FuncHandler final : public KeyValueStore::Service { 
public:
  FuncHandler() : wc_(grpc::CreateChannel( "localhost:50000", grpc::InsecureChannelCredentials())) {}
  // Hook processes messages and calls certain event types
  grpc::Status hook(grpc::ServerContext* context, const func::HookRequest request, func::HookReply reply);

  grpc::Status unhook(grpc::ServerContext* context, const func::UnhookRequest request, func::UnhookReply reply);

  // Where all the inputs come in 
  //grpc::Status event(grpc::ServerContext* context, const func::EventRequest request, func::EventReply reply) override;
  grpc::Status event(grpc::ServerContext* context, const func::EventRequest* request, func::EventReply* response) override;

private:
  WarbleCode wc_;
};