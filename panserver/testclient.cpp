#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[]){

  //argv should be: [./testserver serverIP messageSize]
  try{
    // Where argc is the # of parameters added to the program execution
    // and argv is an array containing the parameters

    std::cout << "argc is: " << argc << std::endl;

    if (argc != 2){
      std::cerr << "Usage: client <host>" << std::endl;
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
