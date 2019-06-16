struct node{
   int val;
   struct node* next;
   struct node* prev;
};

struct list{
   struct node* head;
   struct node* tail;
};

int length(struct list*);
void print(struct list);
void pushFront(struct list*, int);
void pushBack(struct list*, int);

void clear(struct list*);
void removeVal(struct list*, int);
void sortAscending(struct list*);
void sortDescending(struct list*);

void insert(struct list*, int, int);
