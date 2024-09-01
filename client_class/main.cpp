#include <iostream>
#include "client_class.hpp"
#include <boost/asio.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <thread>
#define FILE_PATH "/etc/server_config.conf"

bool check_file() {
	return std::filesystem::exists(FILE_PATH);
}
 
bool check_args(int &argc) {
	return argc == 4;
}

void read_from_file(std::string &server_ip, std::string &server_passwd) {
	std::ifstream in(FILE_PATH);
	if (std::getline(in, server_ip)) {
		if (std::getline(in, server_passwd)) {
			in.close();
		}
	}
}

std::string get_local_ip_address() {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
        boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
        boost::asio::ip::tcp::resolver::iterator end;
        while (iter != end) {
            boost::asio::ip::address addr = (iter->endpoint()).address();
            if (addr.is_v4()) {
                return addr.to_string();
            }
            ++iter;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return "Unable to get local IP address";
}
int main (int argc, char* argv[]) {
	std::cout << "\033[93m";
	std::string server_ip;
	std::string server_passwd;
	if (check_file()) {
		read_from_file(server_ip, server_passwd);
	} else {
		if(getuid() != 0) {
			std::cout << "Permission denied.Please run programm with sudo -E" << std::endl;
			return 1;
		}
		if (!check_args(argc)) {
			std::cout << "Please configure server config file with option --config <IP> <Password>" << std::endl;
			return false;
		} else {
			if (std::strcmp(argv[1], "--config") == 0) {
				server_ip = std::string(argv[2]);
				std::cout << server_ip << std::endl;
				server_passwd = std::string(argv[3]);
				if(!Client::is_valid_ip(server_ip)) {
					Client::get_server_ip(server_ip);
				} else {
					Client::check_server_ip(server_ip);
				}
				server_passwd = Client::xorEncryptDecrypt(server_passwd, 'K');
				Client::write_to_file(server_ip);
			} else {
				std::cout << "Please configure server config file with option --config <IP> <Password>" << std::endl;
				return false;
			}
		}
	}
	boost::asio::io_context ioContext;
	std::string ip;
	std::cout << "IP address: ";
	std::getline(std::cin, ip);	
	Client client1(ioContext, "" , "");
	Client client2(ioContext, "" , "" );
	client1.set_server_endpoint(server_ip);
	client1.set_server_passwd(server_passwd);
	client1.connect_to_server();
	boost::asio::ip::tcp::acceptor tcp_acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), 5002));
	client1.accept_client_connections(tcp_acceptor, client2, ioContext);  
	boost::asio:: streambuf buffer_server;
	client1.receive_data_from_server(buffer_server, client2, ioContext, tcp_acceptor);
	ioContext.run();
	return 0;
}
