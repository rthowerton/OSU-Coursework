#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues
int mod(int a, int b)//borrowed from https://stackoverflow.com/questions/11720656/modulo-operation-with-negative-numbers
{
        int r = a % b;
        return r < 0 ? r + b : r;
}

int main(int argc, char *argv[])
{
   	pid_t child_pids[5] = {-5, -5, -5, -5, -5};
	int for_cnt;

	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[1024], key[512];
	char* temp;
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections


	//while forever
	while(1)
	{
	   int xt_status = -5;
           int childExitMethod = -5;//background process exit method
	   //first check each active child
           for(for_cnt = 0; for_cnt < 5; for_cnt++)
	   {
	      if(child_pids[for_cnt] != -5){//if process is active
	         //wait WNOHANG
	         waitpid(child_pids[for_cnt], &childExitMethod, WNOHANG);
	         if(childExitMethod != -5){
	            if(WIFEXITED(childExitMethod)){//if process exited
	               //if ended, reset child pid to -5
		       child_pids[for_cnt] = -5;
	            }
	            else if(WIFSIGNALED(childExitMethod)){//if process was terminated
	               //if ended, reset child pid to -5
		       child_pids[for_cnt] = -5;
	            }
	         }
	      }
           }

	   //check if there's an open slot
	   int active_children = 0;
	   for(for_cnt = 0; for_cnt < 5; for_cnt++)
	   {
	      if(child_pids[for_cnt] == -5)
		 break;
	      else
		 active_children++;
	   }
	   if(active_children == 5)
	      wait(&childExitMethod);
	
	   // Accept a connection, blocking if one is not available until one connects
	   sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
	   establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
	   if (establishedConnectionFD < 0) error("ERROR on accept");
	
	   pid_t spawnpid = fork();
	   switch(spawnpid)
	   {
	      case -1:
	         perror("Fork failed.\n");
	         exit(1);
	      case 0:
	         //check if communicating with otp_enc
	         memset(buffer, '\0', sizeof(buffer));
		 charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer) - 1, 0);
		 if(buffer[0] != 'e'){
		    memset(buffer, 'e', sizeof(buffer));
		    charsRead = send(establishedConnectionFD, buffer, strlen(buffer), 0);
		    error("SERVER: Not connected to otp_enc.\n");
		 }
		 else
		    charsRead = send(establishedConnectionFD, buffer, strlen(buffer), 0);
		 //receive key and plaintext, need to un-concatenate
	         memset(buffer, '\0', sizeof(buffer));

	         while(recv(establishedConnectionFD, buffer, sizeof(buffer) - 1, 0))
		 {
		    //unconcatenate plaintext and key
		    int kspan = strcspn(buffer, "k");
		    temp = strstr(buffer, "k");
		    strcpy(key, temp + 1);
		    memset(temp, '\0', sizeof(buffer) - kspan);

	            //do ciphertext
		    for(for_cnt = 0; for_cnt < strlen(buffer); for_cnt++)
		    {
		       char buf, k;
		       if(buffer[for_cnt] == 32) buf = 26;
		       else buf = buffer[for_cnt] - 65;
		       if(key[for_cnt] == 32) k = 26;
		       else k = key[for_cnt] - 65;
		       if(((char)(mod(buf + k, 27)) + 65) == 91) buffer[for_cnt] = 32;
		       else buffer[for_cnt] = (char)(mod(buf + k, 27)) + 65;
		    }

	            // Send a Success message back to the client
	            // Actually means send ciphertext back to otp_enc
	            charsRead = send(establishedConnectionFD, buffer, strlen(buffer), 0); // Send success back
	            if (charsRead < 0) error("ERROR writing to socket");
		 }
	         close(establishedConnectionFD); // Close the existing socket which is connected to the client
		 exit(0);
	      default:
	         //add spawnpid to child_pids
		 for(for_cnt = 0; for_cnt < 5; for_cnt++)
		    if(child_pids[for_cnt] == -5){
		       child_pids[for_cnt] = spawnpid;
		       break;
		    }
	   }
	}
	close(listenSocketFD); // Close the listening socket
	return 0; 
}
