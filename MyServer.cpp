//32 minutes 18 seconds
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {
	//Create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1) {
		cerr << "Can't create a socket!" << endl;
		return -1;
	}
	//Bind the socket toan IP / port
	//sockaddr = socket address
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	//htons = host to network
	hint.sin_port = htons(54000);
	//internet port to network
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	//returns a boolean, but it also binds the socket
	if (bind(listening, /*AF_INET, */(sockaddr*)&hint, sizeof(hint)) == -1) {
		cerr << "Can't bind to IP/port" << endl;
		return -2;	
	}
	//Mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1) {
		cerr << "Can't listen!" << endl;
		return -3;
	}
	//Accept a call
	sockaddr_in client;
	socklen_t clientSize;
	char host[NI_MAXHOST];
	//Service
	char svc[NI_MAXSERV];
	int clientSocket = accept(listening, AF_INET, (sockaddr*)&client, &clientSize);
	if (clientSocket == -1) {
		cerr << "Problem with client connecting!" << endl;
		return -4;
	}
	//Close the listening socket
	close(listening);
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0 ,NI_MAXSERV);
	int result = genameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV);
	if (result) {
		cout << host << " connected  on " << service << endl;
	}
	else {
		//network to port
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connetced on " << ntohs(client.sin_port) << endl;
	}
	//While receiving display message, echo message
	char buf[4096];
	while (true) {
		//Clear the Buffer
		memset(buf, 0, 4096);
		//Wait for a Message
		int bytesRecv = recv(clientSocket, but, 4096, 0);
		if (bytesRecv == -1) {
			cerr << "There was a connection issue" << endl;
			break;
		}
		if (bytesRecv == 0) {
			cout << "The client disconnected" << endl;
			break;	
		}
		//Display Message
		cout << "Recieved: " << string(buf, 0, bytesRecv) << endl;
		//Resend Message
		send(clientSocket, buf, bytesRecv + 1, 0);
	}
	//Close socket
	close(clientSocket);
	return 0;
}
