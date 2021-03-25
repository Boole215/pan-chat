#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

class udp_client{
  public:
  udp_client(boost::asio::io_context& io, std::string serverIP, int serverPort)
    :socket_(io),
     server_(udp::endpoint(boost::asio::ip::address::from_string(serverIP), serverPort))
  {
    socket_.open(udp::v4());
  }

  void sendPacket(std::string sendMsg){
    socket_.send_to(boost::asio::buffer(sendMsg), server_);
  }

  void recvPacket(){
    // TODO! Use the server as an example.
    // consider: how are we going to use the app's main event loop
    // in tandem with the client async operations?
    // Maybe make the app a function in the client??
  }
  private:
  udp::socket socket_;
  udp::endpoint server_;
};

int main(int argc, char* argv[]){

  //argv should be: [./testserver serverIP messageSize]
  try{
    // Where argc is the # of parameters added to the program execution
    // and argv is an array containing the parameters

    std::cout << "argc is: " << argc << std::endl;

    if (argc != 3){
      std::cerr << "Usage: client <host> <message (no spaces)>" << std::endl;
      return 1;
    }
    std::string inputMsg = argv[2];
    std::string inputIP = argv[1];
    boost::asio::io_context io;
    udp::resolver resolver(io);

    //the "daytime" identifies the purpose of the server/"service"
    //udp::endpoint host_endpoint = *resolver.resolve(udp::v4(), argv[1], "daytime").begin();
    // Or we can try this? :
    udp::endpoint host_endpoint = udp::endpoint(boost::asio::ip::address::from_string(inputIP), 1025);

    std::cout << "endpoint established with: " << inputIP << ":1025" << std::endl;
    udp::socket socket(io);
    socket.open(udp::v4());
    std::cout << "socket opened" << std::endl;

    //boost::array<char, 1> send_buf = {{ 0 }};
    //boost::asio::buffer send_buf(finputMsg);

    socket.send_to(boost::asio::buffer(inputMsg), host_endpoint);
    std::cout << "packet sent" << std::endl;
    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    std::cout << "Awaiting daytime packet" << std::endl;
    size_t len = socket.receive_from(boost::asio::buffer(recv_buf),
				     sender_endpoint);

    std::cout.write(recv_buf.data(), len);

  } catch (std::exception& e){
    std::cerr << e.what() << std::endl;
  }
  return 0;


}
