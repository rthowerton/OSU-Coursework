#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct room{//room struct
   int id;
   char* name;
   int numConnections;
   struct room* connections[6];
   char* type;
};

void getNewestDir(char*);
void getFileNames(char*, char**);
void getNumLines(char*, char**, int*);
void getRoomData(char*, char**, struct room*, int*, int);
void* printTime(void*);
void playGame(char*, char**, int*, struct room*);

pthread_mutex_t threadControl = PTHREAD_MUTEX_INITIALIZER;

int main(){
   int i, j;

   //make a mutex
   pthread_mutex_lock(&threadControl);

   char newestDirName[24]; //string to hold newest dir name
   memset(newestDirName, '\0', sizeof(newestDirName)); //clear string
   getNewestDir(newestDirName); //Get the newest dir name
   //get file names
   char* fileNames[7];
   getFileNames(newestDirName, fileNames);

   int numLines[7];
   getNumLines(newestDirName, fileNames, numLines);

   struct room rooms[7];//structs to hold room data
   for(i = 0; i < 7; i++){
      getFileNames(newestDirName, fileNames);//reset fileNames
      rooms[i].id = i;//set room id
      getRoomData(newestDirName, fileNames, &rooms[i], numLines, i);//function call
   }

   for(i = 0; i < 7; i++){
      getFileNames(newestDirName, fileNames);
      FILE* toOpen;//file to open
      //create strings
      char line[80], fileName[40];//char array to hold line and file name
      memset(line, '\0', sizeof(line));
      memset(fileName, '\0', sizeof(fileName));//clear memory space
      char* connection = malloc(16*sizeof(char));
      sprintf(fileName, "%s/%s", newestDirName, fileNames[i]);//filePath to open
      toOpen = fopen(fileName, "r");//open the file path
      getFileNames(newestDirName, fileNames);
      int lineCount = 0, connectNum = 0;//count the number of lines
      while(fgets(line, sizeof(line), toOpen)){//get next line
         if(lineCount == 0){//room name is first line
            //do nothing
         }

         else if(lineCount == numLines[i] - 1){//room type is last line
	    //do nothing
         }

         else{
	    sscanf(line, "%*s %*s %s", connection);
	    for(j = 0; j < 7; j++){
	       if(strcmp(connection, rooms[j].name) == 0)
		  rooms[i].connections[connectNum] = &rooms[j];
	    }
	    connectNum++;
	 }
      
         lineCount++;//increment current line
      }
      fclose(toOpen);//close file
   }

   //play the game
   playGame(newestDirName, fileNames, numLines, rooms);
   return 0;
}

void playGame(char* newestDirName, char** fileNames, int* numLines, struct room* rooms){
   int i, movedRooms, steps = 0;//variables
   struct room* current;//current room pointer
   char nextLocation[256];//user input for next room
   memset(nextLocation, '\0', sizeof(nextLocation));
   char* path[256];//user better not get stuck for 256 attempts

   //make a new thread
   pthread_t timeThread;
   int resultCode = pthread_create(&timeThread, NULL, printTime, NULL);

   //get starting location
   for(i = 0; i < 7; i++){
      if(strcmp(rooms[i].type, "START_ROOM") == 0){
	 current = &rooms[i];
	 path[steps] = current->name;
	 steps++;
	 break;
      }
   }

   /****************************************
    * while not at end room
    * print current location
    * print possible connections
    * prompt user for new location
    ****************************************/
   while(strcmp(current->type, "END_ROOM") != 0) {
      movedRooms = 0;
      printf("CURRENT LOCATION: %s\n", current->name);
      printf("POSSIBLE CONNECTIONS: ");
      for(i = 0; i < current->numConnections; i++){
	 printf("%s ", current->connections[i]->name);
      }
      printf("\n");
      printf("WHERE TO? >");
      scanf("%s", nextLocation);

      if(strcmp(nextLocation, "time") == 0){
	 pthread_mutex_unlock(&threadControl);//unlock current thread
	 pthread_join(timeThread, NULL);//wait for printTime to finish
	 pthread_mutex_lock(&threadControl);//lock the mutex
	 resultCode = pthread_create(&timeThread, NULL, printTime, NULL);//reset thread
	 movedRooms = 1;//I know that we didn't technically move rooms, but it's useful
      }

      for(i = 0; i < current->numConnections; i++){//change location
	 //if nextLocation is available
         if(strcmp(nextLocation, current->connections[i]->name) == 0){
	    current = current->connections[i];
	    movedRooms = 1;
	    path[steps] = current->name;
	    steps++;
	    break;
	 }
      }
      if(!movedRooms){//if user entered invalid name
	 printf("\n");
	 printf("INVALID ROOM NAME.\n");
	 printf("\n");
      }
      else
	 printf("\n");
   }

   //once user has escaped, play victory screen
   printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
   printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
   for(i = 0; i < steps; i++){
      printf("%s\n", path[i]);
   }
}

void* printTime(void* argument){
   pthread_mutex_lock(&threadControl);//lock the mutex
   time_t rawTime;//time value
   struct tm* timeKeeper;//hold time
   FILE* toOpen = fopen("currentTime.txt", "w");//open currentTime.txt for writing

   time(&rawTime);//get raw time
   timeKeeper = localtime(&rawTime);//set timeKeeper to local time
   printf("\n %s", asctime(timeKeeper));//print local time as string to screen
   fprintf(toOpen, "%s\n", asctime(timeKeeper));//print local time to currentTime.txt
   pthread_mutex_unlock(&threadControl);//unlock the mutex
}

void getRoomData(char* newestDirName, char** fileNames, struct room* room, int* numLines, int roomNumber){
   FILE* toOpen;//file to open
   //create strings
   char line[80], fileName[40];//char array to hold line and file name
   memset(line, '\0', sizeof(line));
   memset(fileName, '\0', sizeof(fileName));//clear memory space
   char* name =  malloc(16*sizeof(char));//char array to hold struct name
   char* type = malloc(16*sizeof(char));//char array to hold type
   sprintf(fileName, "%s/%s", newestDirName, fileNames[roomNumber]);//filePath to open
   toOpen = fopen(fileName, "r");//open the file path
   
   int lineCount = 0, connectCount = 0;//count the number of lines
   while(fgets(line, sizeof(line), toOpen)){//get next line
      if(lineCount == 0){//room name is first line
         sscanf(line, "%*s %*s %s", name);
         room->name = name;
      }

      else if(lineCount == numLines[roomNumber] - 1){//room type is last line
	 sscanf(line, "%*s %*s %s", type);
	 room->type = type;
      }

      else
	 connectCount++;
      
      lineCount++;//increment current line
   }
   room->numConnections = connectCount;
   fclose(toOpen);//close file
}

void getNumLines(char* newestDirName, char** fileNames, int* numLines){
   int i = 0, j;
   DIR* toOpen;//directory pointer to open
   FILE* room;//file pointer to open
   char line[80], fileName[40];//create strings
   memset(line, '\0', sizeof(line));
   memset(fileName, '\0', sizeof(fileName));
   struct dirent *fileInDir;

   if((toOpen = opendir(newestDirName)) != NULL){//if directory could be opened
      while((fileInDir = readdir(toOpen)) != NULL){//read every file in directory
	 //if file is not . or ..
	 if(strcmp(fileInDir->d_name , ".") == 0 || strcmp(fileInDir->d_name, "..") == 0)
	    continue;
	 else{//is data file
            for(j = 0; j < 7; j++){//for evry room
	       sprintf(fileName, "%s/%s", newestDirName, fileNames[j]);//fetch file name
	       room = fopen(fileName, "r");//open specific directory
	       int linesInFile = 0;
	       while(fgets(line, sizeof(line), room))
		  linesInFile++;
	       numLines[j] = linesInFile;//numLines gets the number of lines in the file
	       fclose(room);//close the file pointer
	    }
	    i++;
	 }
      }
   }
   closedir(toOpen);//close the directory
}


void getFileNames(char* newestDirName, char** fileNames){
   int i = 0;
   DIR* toOpen;
   struct dirent *fileInDir;
   if((toOpen = opendir(newestDirName)) != NULL){//if directory could be opened
      while((fileInDir = readdir(toOpen)) != NULL){//read every file in directory
	 //if file is not . or ..
	 if(strcmp(fileInDir->d_name , ".") == 0 || strcmp(fileInDir->d_name, "..") == 0)
	    continue;
	 else{//is data file
            fileNames[i] = fileInDir->d_name;
	 }
	 i++;
      }
   }
   closedir(toOpen);//close directory
}

void getNewestDir(char* newestDirName)
{
   int newestDirTime = -1; //Modiefied timestamp of examined subdir
   char targetDirPrefix[16] = "howertor.rooms."; //Predefined prefix

   DIR* dirToCheck; //Hold starting directory
   struct dirent *fileInDir; //Hold current subdir of starting dir
   struct stat dirAttributes; //Hold information about subdir

   dirToCheck = opendir("."); //Open directory program is run in

   if(dirToCheck > 0){ //Check if directory can be opened
      while((fileInDir = readdir(dirToCheck)) != NULL){ //Check each entry
	 if(strstr(fileInDir->d_name, targetDirPrefix) != NULL){ //if has prefix
	    stat(fileInDir->d_name, &dirAttributes); //Get attributes of entry

	    if((int)dirAttributes.st_mtime > newestDirTime){ //If new time > older
	       newestDirTime = (int)dirAttributes.st_mtime;
	       memset(newestDirName, '\0', sizeof(newestDirName));
	       strcpy(newestDirName, fileInDir->d_name);
	    }
	 }
      }
   }

   closedir(dirToCheck); //Close the directory
}
