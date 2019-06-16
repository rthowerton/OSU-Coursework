struct squares{
   int mult;
   float div;
};

bool checkDimensions(char*, char*);
void integerize(int*, int*, char*, char*);
squares** makeTable(int, int);
void setMult(squares**, int, int);
void setDiv(squares**, int, int);
void deleteTable(squares** , int );
