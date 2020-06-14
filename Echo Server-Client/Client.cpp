#include <iostream>
#include <conio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

INT WSAAPI inet_pton(
  INT   Family,
  PCSTR pszAddrString,
  PVOID pAddrBuf
);

int main(int argv, char** argc) {

	// Setup ==================

	if (argv != 2) {
		std::cerr << "\nSyntax: Client <IP_Address>\n" << std::endl;
		return 0;
	}

	char* ipaddr = argc[1];
	int port = 55000;

	// Startup Winsock =======================

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsData);

	if (wsOK != 0) {
		std::cerr << "Winsock Startup Error. Quiting!" << std::endl;
		WSACleanup();
		return 0;
	}

	// Create Client Socket ==============

	SOCKADDR_IN clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(port);
	clientAddr.sin_addr.S_un.S_addr = inet_addr(ipaddr);

	SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);

	// Make Connection ====================

	int connResult = connect(clientSock, (SOCKADDR*)& clientAddr, sizeof(clientAddr));

	if (connResult == SOCKET_ERROR) {
		std::cerr << " Connection Error. Quiting!" << std::endl;
		closesocket(clientSock);
		WSACleanup();
		return 0;
	}

	// Start Echo ==================

	char buf[2048];        // stores incoming and outgoing data
	char h;                // stores incoming charcters
	int bytes;             // number of bytes being sent
	int bytesReceived;

	while (true) {

		ZeroMemory(buf, 2048);
		std::cout << "> ";
		bytes = 0;

		// get input

		for (int i = 0; i < 2047; i++) {

			h = _getch();
			_putch(h);

			if (h != 13 && h != 8) {
				bytes++;
				buf[i] = h;
			}
			else if (h == 8) {
				i--;
				bytes--;
				buf[i] = 0;
				i--;
				_putch(' ');
				_putch('\b');
			}
			else if (h == 13) {
				bytes++;
				_putch('\n');
				break;
			}
		}

		if (buf[0] == 0) {
			std::cout << "Quiting!" << std::endl;
			break;
		}

		send(clientSock, buf, bytes, 0);

		ZeroMemory(buf, 2048);
		bytesReceived = recv(clientSock, buf, 2048, 0);
		std::cout << "SERVER> " << buf << std::endl;
	}

	// Close Client and Winsock ================

	closesocket(clientSock);
	WSACleanup();

	return 0;
}