#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

	// Setup ========================

	char ipaddr[] = "0.0.0.0";
	int port = 45000;

	// Winsock Startup ===============================

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsData);

	if (wsOK != 0) {
		std::cerr << "Winsock Startup Error. Quiting!" << std::endl;
		WSACleanup();
		return 0;
	}

	// Create Listening Socket ======================

	SOCKET listSock = socket(AF_INET, SOCK_STREAM, 0);

	if (listSock == INVALID_SOCKET) {
		std::cerr << "Listening Socket is Invalid. Quiting!" << std::endl;
		closesocket(listSock);
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN listAddr;
	listAddr.sin_family = AF_INET;
	listAddr.sin_port = htons(45000);
	inet_pton(AF_INET, ipaddr, &listAddr.sin_addr);

	// Binding Listening Socket and Start Listening ===================

	int bindResult = bind(listSock, (SOCKADDR*)&listAddr, sizeof(listAddr));

	if (bindResult != 0) {
		std::cerr << "Listening Socket Binding Error. Quiting!" << std::endl;
		closesocket(listSock);
		WSACleanup();
		return 0;
	}

	int listenResult = listen(listSock, SOMAXCONN);

	if (listenResult != 0) {
		std::cerr << "Listeing Error. Quiting!" << std::endl;
		closesocket(listSock);
		WSACleanup();
		return 0;
	}

	// Create and Accept Client ======================

	SOCKADDR_IN clientAddr;
	int clSize = sizeof(clientAddr);

	SOCKET clientSock = accept(listSock, (SOCKADDR*)& clientAddr, &clSize);

	if (clientSock == INVALID_SOCKET) {
		std::cerr << "Client Socket Error. Quiting!" << std::endl;
		closesocket(listSock);
		closesocket(clientSock);
		WSACleanup();
		return 0;
	}

	// Get info of Client =====================

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((SOCKADDR*)& clientAddr, clSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << " connected on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &clientAddr.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(clientAddr.sin_port) << std::endl;
	}

	// Close Listeing socket ===================

	closesocket(listSock);

	// Start Echo ===========================

	char buf[2048];
	int bytesReceived;
	
	while (true) {

		ZeroMemory(buf, 2048);
		bytesReceived = recv(clientSock, buf, 2048, 0);
		
		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Receiving Error. Quiting" << std::endl;
			break;
		}
		else if (bytesReceived == 0) {
			std::cout << "Client Disconnected. Quiting!" << std::endl;
			break;
		}
		
		std::cout << "CLIENT> " << buf << std::endl;
		send(clientSock, buf, bytesReceived, 0);
		
	}

	// Close client and winsock ===============

	closesocket(clientSock);
	WSACleanup();

	return 0;
}