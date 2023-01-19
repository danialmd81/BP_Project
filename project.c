#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include "helper_windows.h"
#include "colorize.h"

typedef struct user
{
  char name[20];
  char family_name[20];
  int age;
  char username[30];
  char password[10]; 

}user;

typedef struct words
{
  char* word;
  struct words *next;
}words;

words *head;

words* createwords(char* word);
void push_back(char* word);
void pop_front();
void print();
void my_callback_on_key_arrival(char c);
void clear()
{
  system("cls");
}
void make_board();
void menu();
void sign_in();
void sign_up();
void game_menu_history();
void game_menu();
void easy();
void medium();
void hard();
void make_normal_words();
void make_long_words();
void make_hard_words();

int main()
{
  head=createwords(NULL);
  srand(time(NULL));
  make_normal_words();
  make_long_words();
  make_hard_words();
  
  menu();
  
  HANDLE thread_id = start_listening(my_callback_on_key_arrival);

  WaitForSingleObject(thread_id,100);
  
  return 0;
}

void my_callback_on_key_arrival(char c)
{

}

void make_board(int x,int y)
{
  clear();
  for(int i=0 ;i<x;i++)
  {
    gotoxy(i,0);
    setcolor(3);
    printf("#");
    gotoxy(i,y);
    setcolor(3);
    printf("#");
  }

  for(int j=0;j<y;j++)
  {
    gotoxy(0,j);
    setcolor(3);
    printf("#");
    gotoxy(x,j);
    setcolor(3);
    printf("#");
  }
}

void menu()
{
  make_board(40,5);
  gotoxy(15,1);
  setcolor(1);
  printf("1.sign in");
  gotoxy(15,2);
  printf("2.register");
  gotoxy(15,3);
  setcolor(2);
  printf("Enter your choice:");
  setcolor(15);
  int call;
  line87: scanf("%d",&call);

  if(call==1)
  {
    sign_in();
  }
  else if (call==2)
  {
    sign_up();
  }
  else
  { 
    gotoxy(15,4);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(33,3);
    goto line87;
  }
  
}

void sign_in()
{
  user check;
  line107:make_board(40,6);
  gotoxy(1,1);
  setcolor(14);
  printf("*Username:");
  setcolor(15);
  char username[30];
  scanf("%s",username);
  FILE *file1=fopen(username,"r");
  if(file1==NULL)
  {
    gotoxy(1,2);
    setcolor(4);
    printf("Invalid Username.");
    Sleep(50);
    
    goto line107;
  }
  else
  {
    line123: gotoxy(1,2);
    setcolor(14);
    printf("*password:");
    setcolor(15);
    char password[10];
    fread(&check,sizeof(user),1,file1);
    scanf("%s",password);
    if(strcmp(check.password,password)==0)
    {
      game_menu_history();
    }
    else
    {
      gotoxy(1,3);
      setcolor(4);
      printf("Invalid Password.");
      goto line123;
    }
  }
  


}

void sign_up()
{
  user new_user;
  make_board(40,6);
  gotoxy(1,1);
  setcolor(14);
  printf("*Name:");
  setcolor(15);
  scanf("%s",new_user.name);
  gotoxy(1,2);
  setcolor(14);
  printf("*Family Name:");
  setcolor(15);
  scanf("%s",new_user.family_name);
  gotoxy(1,3);
  setcolor(14);
  printf("*Age:");
  setcolor(15);
  scanf("%d",&new_user.age);
  gotoxy(1,4);
  setcolor(14);
  printf("*Username:");
  setcolor(15);
  scanf("%s",new_user.username);
  gotoxy(1,5);
  setcolor(14);
  printf("*Password:");
  setcolor(15);
  scanf("%s",new_user.password);
  FILE *file=fopen((new_user.username).txt,"w");
  fwrite(&new_user,sizeof(user),1,file);
  game_menu();
}

void game_menu()
{
  int call;
  make_board(40,10);
  gotoxy(15,1);
  setcolor(1);
  printf("Select Your Game Level:");
  gotoxy(15,2);
  printf("1.Easy");
  gotoxy(15,3);
  printf("2.Medium");
  gotoxy(15,4);
  printf("3.Hard");
  setcolor(15);
  gotoxy(38,1);
  line203:scanf("%d",&call);
  if(call==1)
  {
    easy();
  }
  else if(call==2)
  {
    medium();
  }
  else if(call==3)
  {
    hard();
  }
  else
  {
    gotoxy(15,5);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(38,1);
    goto line203;
  }

}

void game_menu_history()
{
  int call;
  make_board(40,10);
  gotoxy(15,1);
  setcolor(1);
  printf("Select Your Game Level:");
  gotoxy(15,2);
  printf("1.Easy");
  gotoxy(15,3);
  printf("2.Medium");
  gotoxy(15,4);
  printf("3.Hard");
  setcolor(15);
  gotoxy(38,1);
  line203:scanf("%d",&call);
  if(call==1)
  {
    easy();
  }
  else if(call==2)
  {
    medium();
  }
  else if(call==3)
  {
    hard();
  }
  else
  {
    gotoxy(15,5);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(38,1);
    goto line203;
  }
}

void easy()
{

}

void medium()
{

}

void hard()
{

}

words* createwords(char* word)
{
  words *newwords;
  newwords = (words *)malloc(sizeof(words));
  if(newwords == NULL) 
  {
    printf(" Memory can not be allocated.");
  }
  else
  {
    newwords->word=word;
    newwords->next = NULL;
    return newwords;
  }
}

void push_back(char* word)
{
  words *newwords = createwords(word);
  words *last =head;
  while (last->next!= NULL)
  {
      last = last->next;
  }
  last->next = newwords;
  return;
}

void pop_front()
{
    words* front = head->next;
    if(front==NULL)
    {
        printf("Impossible to delete from empty Singly Linked List");
        return;
    }
    head->next=front->next;
    free(front);
}

void print()
{
    words *print=head->next;
    while ( print!= NULL)
    {
        printf("%d\n",print->word);
        print = print->next;
    }
}

void make_normal_words()
{
  char check[30],word[11];
  int count;
  FILE *file=fopen("words.txt","r+");
  FILE *write=fopen("Normal Words.txt","w+");
  for(int i=0;i<9998;i++)
  {
    fscanf(file,"%s",check);
    if(strlen (check)<=10)
    {
      fprintf(write,"%s\n",check);
    }
  }
}

void make_long_words()
{
   char check[30],word[11];
    int count;
    FILE *file=fopen("words.txt","r+");
    FILE *write=fopen("Long Words.txt","w+");
    for(int i=0;i<9998;i++)
    {
      fscanf(file,"%s",check);
      if(strlen (check)>10&&strlen (check)<=20)
      {
        fprintf(write,"%s\n",check);
      }
    }
}

void make_hard_words()
{
  FILE *hard_file=fopen("Hard Words.txt","w");
  
  for(int j=0;j<1000;j++)
  {
    int randd=(rand()%19)+1;
    for(int i=0;i<randd;i++)
    {
      putc((rand()%96)+32,hard_file);
    }
    fputs("\n",hard_file);
  }
  
}





