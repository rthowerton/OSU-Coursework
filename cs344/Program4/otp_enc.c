#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	int socketFD, portNumber, charsWritten, charsRead, get_char;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[1024];
	char key[512], plain[512];
	char* localhost = "localhost";
    
	if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]); exit(0); } // Check usage & args

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");

	// Get input message from user
	FILE* plaintext = fopen(argv[1], "r");// Get plaintext and its length
	fseek(plaintext, 0L, SEEK_END);
	int plaintext_length = ftell(plaintext);
	rewind(plaintext);
	//check if plaintext contains bad characters (characters != 32 or not between 65 and 90
	char checker;
	do
	{
	   checker = fgetc(plaintext);
	   if(checker != 32 && checker != '\n' && checker != EOF)
	     if(checker < 65 || checker > 90)
	        error("CLIENT: Plaintext contains bad characters.\n");
	} while(checker != EOF);
	rewind(plaintext);

	FILE* keytext = fopen(argv[2], "r"); // Get key text and its length
	fseek(keytext, 0L, SEEK_END);
	int keytext_length = ftell(keytext);
	rewind(keytext);

	//ensure key is long enough
	if(keytext_length < plaintext_length) error("CLIENT: Key too short.\n");
	
	//make sure communicating with otp_enc_d
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	strcat(buffer, "e");
	charsWritten = send(socketFD, buffer, strlen(buffer), 0);
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
	if(buffer[0] != 'e') error("CLIENT: Not connected to otp_enc_d.\n");

	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	memset(plain, '\0', sizeof(plain)); // Clear out the plain array
	memset(key, '\0', sizeof(key)); // Clear out the key array
	//unpack plaintext and keytext
	while((fgets(plain, sizeof(plain) - 1, plaintext) != NULL) && (fgets(key, sizeof(key) - 1, keytext) != NULL)){
	   plain[strcspn(plain, "\n")] = 'k'; //signal that plaintext is complete with a k character

	   //concatenate the two together in buffer
	   strcat(buffer, plain);
	   strcat(buffer, key);
	   buffer[strcspn(buffer, "\n")] = '\0'; // Get rid of the trailing \n character

	   // Send message to server
	   charsWritten = send(socketFD, buffer, strlen(buffer), 0); // Write to the server
	   if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	   if (charsWritten < strlen(buffer)) perror("CLIENT: WARNING: Not all data written to socket!\n");

	   // Get return message from server
	   memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
 	   charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
	   if (charsRead < 0) error("CLIENT: ERROR reading from socket");
	   printf("%s", buffer);
	   
	   //clear arrays for future use
	   memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	   memset(plain, '\0', sizeof(plain)); // Clear out the plain array
	   memset(key, '\0', sizeof(key)); // Clear out the key array
	}
	printf("\n");
	fclose(plaintext);
	fclose(keytext);

	close(socketFD); // Close the socket
	return 0;
}
