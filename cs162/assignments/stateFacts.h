struct county{
   string name;
   int numCities;
   string* cityNames;
   int population;
   float avgIncome;
   float avgHouse;
};
struct state{
   string name;
   int numCounties;
   county* c;
   int population;
};

bool isValidArguments(int, char**);
void getNumStates(int, char**, int*);
state* createStates(int);
county* createCounties(int);
void getCountyData(int, county*, ifstream&);
void getStateData(int, state*, ifstream&);
void deleteInfo(state*, int);
void largestState(state*, int);
void largestCounty(state*, int);
void richCounties(state*, int, int);
void averageHouseCost(state*, int);
void sortStateNames(state*, int);
void sortCountyNames(state*, int);
void sortStatePopulation(state*, int);
void sortCountyPopulation(state*, int);
