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
	}
	//Bind the socket toan IP / port
	//Mark the socket for listening in
	//Accept a call
	//Close the listening socket
	//While receiving display message, echo message
	//Close socket
	return 0;
}
