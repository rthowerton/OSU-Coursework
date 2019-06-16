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
	char key[512], cipher[512];
	char* localhost = "localhost";
    
	if (argc < 4) { fprintf(stderr,"USAGE: %s ciphertext key port\n", argv[0]); exit(0); } // Check usage & args

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
	//printf("CLIENT: Enter text to send to the server, and then hit enter: ");//THIS WILL BE REMOVED
	FILE* ciphertext = fopen(argv[1], "r");// Get ciphertext and its length
	fseek(ciphertext, 0L, SEEK_END);
	int ciphertext_length = ftell(ciphertext);
	rewind(ciphertext);
	
	//check if plaintext contains bad characters (characters != 32 or not between 65 and 90
	char checker;
	do
	{
	   checker = fgetc(ciphertext);
	   if(checker != 32 && checker != '\n' && checker != EOF)
	     if(checker < 65 || checker > 90)
	        error("CLIENT: Ciphertext contains bad characters.\n");
	} while(checker != EOF);
	rewind(ciphertext);

	FILE* keytext = fopen(argv[2], "r"); // Get key text and its length
	fseek(keytext, 0L, SEEK_END);
	int keytext_length = ftell(keytext);
	rewind(keytext);

	//ensure key is long enough
	if(keytext_length < ciphertext_length) error("CLIENT: Key too short.\n");
	
	//make sure communicating with otp_dec_d
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	strcat(buffer, "d");
	charsWritten = send(socketFD, buffer, strlen(buffer), 0);
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
	if(buffer[0] != 'd') error("CLIENT: Not connected to otp_dec_d.\n");

	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	memset(cipher, '\0', sizeof(cipher)); // Clear out the key array
	memset(key, '\0', sizeof(key)); // Clear out the key array
	//unpack ciphertext and keytext
	while((fgets(cipher, sizeof(cipher) - 1, ciphertext) != NULL) && (fgets(key, sizeof(key) - 1, keytext) != NULL)){
	   cipher[strcspn(cipher, "\n")] = 'k'; //signal that ciphertext is complete with a k character

	   //concatenate the two together in buffer
	   strcat(buffer, cipher);
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
	   memset(cipher, '\0', sizeof(cipher)); // Clear out the key array
	   memset(key, '\0', sizeof(key)); // Clear out the key array
	}
	printf("\n");
	fclose(ciphertext);
	fclose(keytext);

	close(socketFD); // Close the socket
	return 0;
}
