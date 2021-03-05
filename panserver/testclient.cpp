#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[]){


  try{
    // Where argc is the # of parameters added to the program execution
    // and argv is an array containing the parameters

    std::cout << "argc is: " << argc << std::endl;

    if (argc != 2){
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io;
    udp::resolver resolver(io);

    //the "daytime" identifies the purpose of the server/"service"
    //udp::endpoint host_endpoint = *resolver.resolve(udp::v4(), argv[1], "daytime").begin();
    // This works for sure, gotta
    udp::endpoint host_endpoint = udp::endpoint(argc, 1025);

    std::cout << "endpoint established" << std::endl;
    udp::socket socket(io);
    socket.open(udp::v4());
    std::cout << "socket opened" << std::endl;

    boost::array<char, 1> send_buf = {{ 0 }};
    socket.send_to(boost::asio::buffer(send_buf), host_endpoint);
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
