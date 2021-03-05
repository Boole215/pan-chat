#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>


using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}



int main(){

  std::cout << "I start" << std::endl;
  try{
      boost::asio::io_context io;
      udp::socket socket(io, udp::endpoint(udp::v4(), 1025));
      std::cout << "Socket setup at 1025" << std::endl;
      for(;;){
	boost::array<char, 1> recv_buf;
	udp::endpoint remote_endpoint;
	std::cout << "Awaiting connection" << std::endl;
	//receive_from populates the remote_endpoint object.
	socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
	std::cout << "Accepted connection" << std::endl;
	std::string message = make_daytime_string();
	std::cout << "daytime message created" << std::endl;
	boost::system::error_code ignored_error;
	socket.send_to(boost::asio::buffer(message),
		       remote_endpoint, 0, ignored_error);
      }

    }
  catch (std::exception& e){
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
