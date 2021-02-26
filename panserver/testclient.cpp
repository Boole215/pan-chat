#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[]){

  try{
    // Where argc is the # of parameters added to the program execution
    // and argv is an array containing the parameters
    if (argc != 2){
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io;
    udp::resolver resolver(io);

    //the "daytime" identifies the purpose of the server/"service"
    udp::endpoint host_endpoint = *resolver.resolve(udp::v4(), argv[1], "daytime").begin();

    udp::socket socket(io);
    socket.open(udp::v4());

    boost::array<char, 1> send_buf = {{ 0 }};
    socket.send_to(boost::asio::buffer(send_buf), host_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(boost::asio::buffer(recv_buf),
				     sender_endpoint);

    std::cout.write(recv_buf.data(), len);

  } catch (std::exception& e){
    std::cerr << e.what() << std::endl;
  }
  return 0;


}