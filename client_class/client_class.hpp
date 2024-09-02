#ifndef __CLIENT_CLASS__
#define __CLIENT_CLASS__
#include <string>
#include <boost/asio.hpp>
#include <stdint.h>
#include <atomic>
#include <map>
class Client{
    private:
        boost::asio::ip::tcp::socket _client_socket;
        boost::asio::ip ::tcp::socket _server_socket; 
        boost::asio::ip::tcp::endpoint server_endpoint;
        std::string user_name;
        std::string ip_address;
        std::string encrypted_server_passwd;
        bool set_user_name( const std:: string _user_name );
        std::string get_user_name();
        bool set_ip_address(const std::string _ip_address);
        boost::asio::ip::tcp::socket& get_client_socket();
        boost::asio::ip::tcp::socket& get_server_socket();
        void get_another_client_username(boost::asio::io_context &ioContext, Client &another_client, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void connect_to_another_client_request(Client&  other_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void accept_handler(const boost::system::error_code &err, Client &another_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void client_receive_handler(const boost::system::error_code &err, std::shared_ptr<boost::asio::streambuf> buf, Client &another_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void server_receive_handler(const boost::system::error_code &err, boost:: asio :: streambuf &buf , Client& another_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        bool check_user_name(std::string &username);
        void getUserName(std::string &username);
        void send_message(const std::string &message);
        void start_input_thread(Client &another_client);
        std::thread input_thread;
        std::thread input_thread2;
        std::atomic<bool> is_open_chat{true};
        bool is_accepted;
        bool check_file_path(const std:: string& file_path);
        std::string expandTilde(const std::string& path);
        unsigned short terminal_width;
        std::map<std::string, std::string> emoji_list;
        std::map<std::string, std::string> users_list;
        std::map<std::string, std::string> user_status_list;
        void update_user_list(std::string &message);
        void get_client_response(Client &another_client, boost::asio::io_context &ioContext, std::shared_ptr<boost::asio::streambuf> buf);
    public:
        Client(boost:: asio :: io_context& io_context , std:: string user_name , std:: string ip_address  );
        void send_data_to_server();
        void receive_data_from_server(boost:: asio :: streambuf& buf,Client& another_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void accept_client_connections(boost::asio::ip::tcp::acceptor &tcp_acceptor, Client &another_client, boost::asio::io_context &ioContext);
        void connect_to_server();
        void receive_data_from_another_client(std::shared_ptr<boost::asio::streambuf> buf, Client &another_client, boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &tcp_acceptor);
        void set_server_endpoint(std::string &server_ip);
        std::string get_ip_address();
        static void write_to_file(std::string &text);
        static bool is_valid_ip(const std::string &ip);
        static void get_server_ip(std::string &server_ip);
        static void check_server_ip(std::string &server_ip);
        void set_server_passwd(std::string &server_passwd);
};

#endif