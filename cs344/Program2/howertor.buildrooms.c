#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void makeDirectory(char*);
void buildRooms(char*, int*, char**);
void makeConnections(char*, char**);
void _makeConnections(int[7][7], int, int);
int numConnections(int[7][7], int);
void setType(char*, char**);

int main()
{
   srand(time(NULL));//seed rng
   char dirName[21];//store the directory name for this session
   memset(dirName, '\0', 21);
   makeDirectory(dirName);//make the directory
   //create array to check if room has been created
   int used[10];
   int i;
   for(i = 0; i < 10; i++){
      used[i] = 0;
   }
   //create 7 random room files in howertor.rooms.*
   char* roomNames[7];//array to store the file names in use
   buildRooms(dirName, used, roomNames);//create the room files
   makeConnections(dirName, roomNames);//build connections
   setType(dirName, roomNames);//set room types
   return 0;
}

void makeDirectory(char* dirName){
   int curProcess = getpid();//get current process id
   /**************************************************
    * The following code was found at
    * https://cboard.cprogramming.com/c-programming/
    * 165757-using-process-id-name-file-directory.html
    **************************************************/
   sprintf(dirName, "howertor.rooms.%d", curProcess);
   mkdir(dirName, 0700);
}

void buildRooms(char* dirName, int* used, char** roomNames){
   int i;
   for(i = 0; i < 7; i++){
      int roomNum = rand() % 10 + 1;//random number to generate the room
      char roomName[12];//store the room name
      memset(roomName, '\0', 12);
      char fileName[31];//store the file name/path
      memset(fileName, '\0', 31);
      FILE* room;//FILE pointer to contain the stream
      /**********************************************************
       * Depending on the random number, generate a room name,
       * store the file path, then open the stream and write
       * the room name into the file. After it's all done, the
       * corresponding room name is checked as used. If the name
       * is already used, decrement i and break the switch.
       **********************************************************/
      switch(roomNum){
	 case 1:
	    if(used[0] == 0){
               strcpy(roomName, "Albatross");//room gets named
	       roomNames[i] = "Albatross";//add name to list of names in use
	       sprintf(fileName, "%s/%s", dirName, roomName);//create filepath
	       room = fopen(fileName, "w");//open stream
	       fprintf(room, "ROOM NAME: %s\n", roomName);//print name to file
	       fclose(room);//close stream
	       used[0] = 1;//check name as used
	    }
	    else{
	       i--;//decrement i
	       break;//exit switch
	    }
	    break;//exit switch
	 case 2://above code is copypasta'd 9 more times, with different names
	    if(used[1] == 0){
	       strcpy(roomName, "Bawkses");
	       roomNames[i] = "Bawkses";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[1] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 3:
	    if(used[2] == 0){
	       strcpy(roomName, "Carmike");
	       roomNames[i] = "Carmike";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[2] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 4:
	    if(used[3] == 0){
	       strcpy(roomName, "Delphino");
	       roomNames[i] = "Delphino";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[3] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 5:
	    if(used[4] == 0){
	       strcpy(roomName, "Everlight");
	       roomNames[i] = "Everlight";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[4] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 6:
	    if(used[5] == 0){
	       strcpy(roomName, "fallUp");
	       roomNames[i] = "fallUp";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[5] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 7:
	    if(used[6] == 0){
	       strcpy(roomName, "Graveyard");
	       roomNames[i] = "Graveyard";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[6] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 8:
	    if(used[7] == 0){
	       strcpy(roomName, "Harvey");
	       roomNames[i] = "Harvey";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[7] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 9:
	    if(used[8] == 0){
	       strcpy(roomName, "Igloo");
	       roomNames[i] = "Igloo";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[8] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
	 case 10:
	    if(used[9] == 0){
	       strcpy(roomName, "Justice");
	       roomNames[i] = "Justice";
	       sprintf(fileName, "%s/%s", dirName, roomName);
	       room = fopen(fileName, "w");
	       fprintf(room, "ROOM NAME: %s\n", roomName);
	       fclose(room);
	       used[9] = 1;
	    }
	    else{
	       i--;
	       break;
	    }
	    break;
      }
   }
}

void makeConnections(char* dirName, char** roomNames){
   int connections[7][7];//2d int array to build connections
   int i, j;
   for(i = 0; i < 7; i++){//initialize connections to be 0;
      for(j = 0; j < 7; j++){
	 connections[i][j] = 0;
      }
   }
   /********************************************************
    * for each room
    * generate random number between 3 and 6
    * if numConnections < 6 and less than max connections
    * assign random outbound connections (not to self)
    * assign inbound connections
    ********************************************************/
   for(i = 0; i < 7; i++){
      int maxConnections = rand() % 4 + 3;
      if(numConnections(connections, i) < 6){
	 if(numConnections(connections, i) >= maxConnections)
	    continue;
	 else
	    _makeConnections(connections, maxConnections, i);
      }
      else
	 continue;
   }

   //if program makes it through grid, assign connections
   for(i = 0; i < 7; i++){
      int count = 1;
      FILE* room;
      char roomName[12];//store the room name
      memset(roomName, '\0', 12);
      char fileName[31];//store the file name/path
      memset(fileName, '\0', 31);
      sprintf(fileName, "%s/%s", dirName, roomNames[i]);//combine file path
      room = fopen(fileName, "a");
      for(j = 0; j < 7; j++){
	 if(connections[i][j] == 0)
	    continue;
	 else{
	    fprintf(room, "CONNECTION %d: %s\n", count, roomNames[j]);
	    count++;
	 }
      }
      fclose(room);
   }
}

void _makeConnections(int connections[7][7], int maxConnections, int room){
   /****************************************
    * for i < maxConnections
    * generate random number
    * if outbound room not assigned
    * assign as connection
    ****************************************/
   int i;
   for(i = 0; i < maxConnections; i++){
      int assign = rand() % 7;
      if(assign != i && connections[i][assign] == 0){
	 connections[i][assign] = 1;
	 connections[assign][i] = 1;
      }
      else
	 continue;
   }
}

int numConnections(int connections[7][7], int room){
   //get number of assigned connections for each room
   int i, answer = 0;
   for(i = 0; i < 7; i++){
      answer += connections[room][i];
   }
   return answer;
}

void setType(char* dirName, char** roomNames){
   int i;
   for(i = 0; i < 7; i++){
      FILE* room;
      char roomName[12];//store the room name
      memset(roomName, '\0', 12);
      char fileName[31];//store the file name/path
      memset(fileName, '\0', 31);
      sprintf(fileName, "%s/%s", dirName, roomNames[i]);//combine the filepath
      room = fopen(fileName, "a");
      if(i == 0)//make first room the start room
         fprintf(room, "ROOM TYPE: START_ROOM\n");
      else if(i == 6)//make last room the end room
	 fprintf(room, "ROOM TYPE: END_ROOM\n");
      else//make every other room a mid room
	 fprintf(room, "ROOM TYPE: MID_ROOM\n");
   }
}
