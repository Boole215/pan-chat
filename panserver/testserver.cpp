#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}

class udp_server{
  public:
  udp_server(boost::asio::io_context& io_context)
    :socket_(io_context, udp::endpoint(udp::v4(), 1025)){
    std::cout << "starting start_receive" << std::endl;
    start_receive();
  }
  private:
  void start_receive(){
    std::cout << "Starting asynchronous method" << std::endl;
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
      boost::bind(&udp_server::handle_receive, this,
		  boost::asio::placeholders::error,
		  boost::asio::placeholders::bytes_transferred));
    std::cout << "Asynchronous loop added to io_context" << std::endl;
  }

  void handle_receive(const boost::system::error_code& error,
		      std::size_t /*bytes_transferred*/){

    if(!error){
      std::cout << "Currently inside handle_receive" << std::endl;
      boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));
      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
			    boost::bind(&udp_server::handle_send, this, message,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
      start_receive();
    }
  }

  void handle_send(boost::shared_ptr<std::string> /*message*/,
		   const boost::system::error_code& /*error*/,
		   std::size_t /* bytes_transferred*/){

  }
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1> recv_buffer_;



};

int main(){

  try{
    boost::asio::io_context io;
    std::cout << "io context created" << std::endl;
    udp_server server(io);
    std::cout << "server created" << std::endl;

    io.run();

  } catch(std::exception& e){

    std::cerr << e.what() << std::endl;
  }
  return 0;
}
