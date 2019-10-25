#include <iostream>
#include <ctime>
#include <string>
#include <memory>

struct ClientContext {
	int val;
};

class HelloRequest {
public:
	HelloRequest(void)
	{ }

	void set_name(const std::string name) {
		this->name_ = name;
	}

private:
	std::string name_;
};

class HelloReply {
public:
	HelloReply(void)
	{ }

	void set_message(const char* msg) {
		this->msg_ = msg;
	}

	std::string message(void) {
		return this->msg_;
	}
private:
	std::string msg_;
};

class Status {
public:
	Status(int code)
		:code_(code)
	{ }

	bool ok(void) {
		return (this->code_ == 0);
	}

	int error_code(void) {
		return this->code_;
	}

	std::string error_message(void) {
		return "RPC Failed!";
	}
private:
	int code_;
};

class Stub {
public:
	Stub(std::string address)
		:status_(0),
		address_(address)
	{ }

	Status SayHello(ClientContext *ctx, HelloRequest &req, HelloReply *reply) {
		reply->set_message("Hello World from Server!");
		return this->status_;
	}

	Status SayHelloAgain(ClientContext *ctx, HelloRequest &req, HelloReply *reply) {
		reply->set_message("Again, Hello World from Server!");
		return this->status_;
	}

private:
	Status status_;
	std::string address_;
};

class GreeterClient {
 public:
  GreeterClient(std::string address)
      : stub_(new Stub(address)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHelloAgain(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHelloAgain(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Stub> stub_;
};


int main(void) {
	std::clock_t start = std::clock ();
	// Instantiate the client. It requires a channel, out of which the actual RPCs
	// are created. This channel models a connection to an endpoint (in this case,
	// localhost at port 50051). We indicate that the channel isn't authenticated
	// (use of InsecureChannelCredentials()).
	GreeterClient greeter("localhost:50051");
	std::string user("world");
	std::string reply;

	reply = greeter.SayHello(user);
	std::cout << "Greeter recieved: " << reply << std::endl;

	reply = greeter.SayHelloAgain(user);
	std::cout << "Greeter received: " << reply << std::endl;

	std::clock_t end = std::clock ();
	std::cout << "Time consumption: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " (ms)" << std::endl;

	return 0;
}
