#ifndef P2P_SHARE_CLIENT_H
#define P2P_SHARE_CLIENT_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <algorithm>

#include <SFML/Network.hpp>

#include "Const.h"
#include "Connection.h"
#include "File.h"

class Client {
public:
	Client();
	~Client();

	void init();

	void go();
private:
	std::vector<Connection*> peers;
	Connection indexServer;
	sf::TcpListener listener;
	sf::SocketSelector waiter;

	std::mutex lock;

	std::vector<File> incompleteFiles;
	File* findIncompleteFile(std::string filename);
	void removeIncompleteFile(std::string filename);

	std::string myIp;
	sf::Uint32 listenerPort;

	bool timeToExit;

	void incomingLoop();
	void inputLoop();

	void handleServerMessage();
	void handleMessage(Connection* peer);
	void handleInput(std::string input);

	void handleQuit();
	void handleConnectServer(std::string ip, sf::Uint32 port);

	Connection* connectToPeer(std::string ip, sf::Uint32 port);
	Connection* findPeer(std::string ip, sf::Uint32 port);

};


#endif //P2P_SHARE_CLIENT_H
