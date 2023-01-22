#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "helper_windows.h"
#include "colorize.h"



typedef struct history
{
  unsigned long long int score;
  int day,month,year,turn;
  char *level;
}history;
typedef struct user
{
  char name[20];
  char family_name[20];
  int age,nobat_bazi;
  char username[30];
  char password[10];
  history historyy[4];
}user;

typedef struct words
{
  char* word;
  struct words *next;
  struct words *back;
}words;

FILE *file;
user new_user;
char username[30];
words *head;
unsigned long long int scoree=0;
int call,nobat_bazi=0;
int len=0,row=1,col=10,num_word_har_dor=0,num_dor=0;
int num_check_word=0,max_word=0,num_all_printed_word=0;
int max_dor=0,num_all_deleted_word=0;
double timee,discount;
HANDLE thread_id;


words* createwords(char* word);
void push_back(char* word);
void my_callback_on_key_arrival(char c);
void clear()
{
  system("cls");
}
void make_board(int x,int y);
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
void print(int color,double discount);
char*chose_word_from_normal(char* word);
char*chose_word_from_long(char* word);
char*chose_word_from_hard(char* word);
void hidecursor();
void game_over();
void victory();
void score(int x,int y);


int main()
{
  head=createwords(NULL);
  srand(time(NULL));
  make_normal_words();
  make_long_words();
  make_hard_words();
  hidecursor();
  // easy();
  // menu();
  victory();
  WaitForSingleObject(thread_id,INFINITE);
  return 0;
}

void my_callback_on_key_arrival(char c)
{
  if(num_all_deleted_word==max_word)
  {
    return;
  }
  if(c==head->next->word[len]&&num_all_deleted_word<max_word)
  {
    gotoxy(col,row-1);
    setcolor(2);
    printf("%c",head->next->word[len]);
    setcolor(7);
    col++;
    len++;
    if(len==strlen(head->next->word))
    {
      num_all_deleted_word++;
      head=head->next;
      num_check_word--;
      row--;
      len=0;
      col=10;
      if(strlen(head->word)<=10)
      {
        scoree++;
        Sleep(100);
        print(7,discount);
        return;
      }
      else
      {
        if(strpbrk(head->word,"!\"#$&'()*+,-./:;<>.?@_[]\\^'{}|~")==NULL)
        {
          scoree+=2;
          Sleep(100);
          print(7,discount);
          return;
        }
        else
        {
          scoree+=3;
          Sleep(100);
          print(7,discount);
          return;
        }
      }
    }
    return;
  }

  if(c!=head->next->word[len]&&c!='\b'&&num_all_deleted_word<max_word)
  {
    gotoxy(col,row-1);
    setcolor(4);
    printf("%c",head->next->word[len]);
    setcolor(7);
    col++;
    len++;
    if(len==strlen(head->next->word))
    {
      num_all_deleted_word++;
      head=head->next;
      num_check_word--;
      row--;
      len=0;
      col=10;
      Sleep(100);
      print(7,discount);
      return;
    }
    return;
  }

  if(c=='\b'&&num_all_deleted_word<max_word)
  {
    if(len!=0)
    {
      len--;
      col--;
    }
    gotoxy(col,row-1);
    setcolor(7);
    printf("%c",head->next->word[len]);
    if(len==0)
    {
      if(head->back!=NULL&&row<0)
      {
        head=head->back;
        row--;
        num_check_word--;
        num_all_deleted_word--;
        len=strlen(head->next->word);
        col=strlen(head->next->word)+9;
        Sleep(100);
        print(7,discount);
        return;
      }
      return;
    }
    return;
  }


}

void make_board(int x,int y)
{
  clear();
  for(int i=0;i<x;i++)
  {
    gotoxy(i,0);
    setcolor(6);
    char a=6;
    printf("%c",a);
    gotoxy(i,y);
    setcolor(6);
    printf("%c",a);
  }

  for(int j=0;j<y;j++)
  {
    gotoxy(0,j);
    setcolor(6);
    char a=6;
    printf("%c",a);
    gotoxy(x,j);
    setcolor(6);
    printf("%c",a);
  }
}

void menu()
{
  make_board(40,5);
  gotoxy(10,1);
  setcolor(1);
  printf("1.sign in");
  gotoxy(10,2);
  printf("2.register");
  gotoxy(10,3);
  setcolor(2);
  printf("Enter your choice:");
  setcolor(7);
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
    gotoxy(10,4);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(33,3);
    goto line87;
  }

}

void sign_in()
{
  line107:make_board(40,6);
  gotoxy(1,1);
  setcolor(6);
  printf("*Username:");
  setcolor(7);
  scanf("%s",username);
  file=fopen(username,"r+");
  if(file==NULL)
  {
    gotoxy(1,2);
    setcolor(4);
    printf("Invalid Username.");
    Sleep(100);
    goto line107;
  }
  else
  {
    line123: gotoxy(1,2);
    setcolor(6);
    printf("*password:");
    setcolor(7);
    char password[10];
    fread(&new_user,sizeof(user),1,file);
    scanf("%s",password);
    if(strcmp(new_user.password,password)==0)
    {
      nobat_bazi=new_user.nobat_bazi;
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
  make_board(40,6);
  gotoxy(1,1);
  setcolor(6);
  printf("*Name:");
  setcolor(7);
  scanf("%s",new_user.name);
  gotoxy(1,2);
  setcolor(6);
  printf("*Family Name:");
  setcolor(7);
  scanf("%s",new_user.family_name);
  gotoxy(1,3);
  setcolor(6);
  printf("*Age:");
  setcolor(7);
  scanf("%d",&new_user.age);
  gotoxy(1,4);
  setcolor(6);
  printf("*Username:");
  setcolor(7);
  scanf("%s",new_user.username);
  gotoxy(1,5);
  setcolor(6);
  printf("*Password:");
  setcolor(7);
  new_user.nobat_bazi=0;
  scanf("%s",new_user.password);
  FILE *file=fopen(new_user.username,"w+");
  fwrite(&new_user,sizeof(user),1,file);
  game_menu();
}

void game_menu()
{
  make_board(40,10);
  gotoxy(10,1);
  setcolor(1);
  printf("Select Your Game Level:");
  gotoxy(10,2);
  printf("1.Easy");
  gotoxy(10,3);
  printf("2.Medium");
  gotoxy(10,4);
  printf("3.Hard");
  setcolor(7);
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
    gotoxy(10,5);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(33,1);
    goto line203;
  }

}

void game_menu_history()
{
  make_board(40,10);
  gotoxy(10,1);
  setcolor(1);
  printf("Select Your Game Level:");
  gotoxy(10,2);
  setcolor(6);
  printf("1.Easy");
  gotoxy(10,3);
  printf("2.Medium");
  gotoxy(10,4);
  printf("3.Hard");
  gotoxy(10,5);
  setcolor(2);
  printf("4.");
  if()
  {
    gotoxy(10,6);
    printf("5.");
  }
  if()
  {
    gotoxy(10,7);
    printf("6.");
  }

  setcolor(7);
  gotoxy(33,1);
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
    gotoxy(10,5);
    setcolor(4);
    printf("Choose Wisely.");
    gotoxy(33,1);
    goto line203;
  }
}

void easy()
{
  make_board(40,25);
  score(40,4);
  timee=10000.000;
  discount=0.8;
  int i=0,a=10;
  for(int t=0;timee>=1000.000;t++)
  {
    char word[21][40];
    int num_normal_word=10,num_long_word=0;
    for(;i<a;i++)
    {
      int choose = (rand()%10)+1;
      if(choose>(10-num_normal_word))
      {
        push_back(chose_word_from_normal(word[i]));
      }
      else if(choose<=num_long_word)
      {
        push_back(chose_word_from_long(word[i]));
      }
      else
      {
        push_back(chose_word_from_hard(word[i]));
      }
      max_word++;
    }
    if(a==40)
    {
      a=0;
      i=0;
    }
    a+=10;
    num_normal_word--;
    if(t%3!=1)
    {
      num_long_word++;
    }
    timee =timee*(0.8);
  }
  thread_id = start_listening(my_callback_on_key_arrival);
  timee=10000.000;
  for(num_dor=0;timee>=1000;)
  {
    for(num_word_har_dor=0;num_word_har_dor<10;)
    {
      print(7,discount);
      Sleep(timee);
    }
  }
}

void medium()
{
  make_board(40,25);
  score(40,4);
  timee=8000.000;
  discount=0.7;
  int i=0,a=10;
  for(int t=0;timee>=1000.000;t++)
  {
    char word[21][40];
    int num_normal_word=5,num_hard_word=0;
    for(;i<a;i++)
    {
      int choose = (rand()%10)+1;
      if(choose>(10-num_normal_word))
      {
        push_back(chose_word_from_normal(word[i]));
      }
      else if(choose<=num_hard_word)
      {
        push_back(chose_word_from_hard(word[i]));
      }
      else
      {
        push_back(chose_word_from_long(word[i]));
      }
      max_word++;
    }
    if(a==40)
    {
      a=0;
      i=0;
    }
    a+=10;
    num_normal_word--;
    num_hard_word++;
    timee =timee*(0.7);
  }
  thread_id = start_listening(my_callback_on_key_arrival);
  timee=8000.000;
  for(num_dor=0;timee>=1000;)
  {
    for(num_word_har_dor=0;num_word_har_dor<10;)
    {
      print(7,discount);
      Sleep(timee);
    }
  }

}

void hard()
{
  make_board(40,25);
  score(40,4);
  timee=5000.000;
  discount=0.6;
  int i=0,a=10;
  for(int t=0;timee>=1000.000;t++)
  {
    char word[21][40];
    int num_normal_word=3,num_hard_word=1;
    for(;i<a;i++)
    {
      int choose = (rand()%10)+1;
      if(choose>(10-num_normal_word))
      {
        push_back(chose_word_from_normal(word[i]));
      }
      else if(choose<=num_hard_word)
      {
        push_back(chose_word_from_hard(word[i]));
      }
      else
      {
        push_back(chose_word_from_long(word[i]));
      }
      max_word++;
    }
    a+=10;
    max_dor=t;
    num_normal_word--;
    num_hard_word++;
    timee =timee*(0.6);
  }
  thread_id = start_listening(my_callback_on_key_arrival);
  timee=5000.000;
  for(num_dor=0;timee>=1000;)
  {
    for(num_word_har_dor=0;num_word_har_dor<10;)
    {
      print(7,discount);
      Sleep(timee);
    }
  }
}

words* createwords(char *word)
{
  words *newwords;
  newwords = (words *)malloc(sizeof(words));
  if(newwords == NULL)
  {
    printf("Memory can not be allocated.");
  }
  else
  {
    newwords->word=malloc(21*sizeof(char));
    newwords->word = word;
    newwords->next = NULL;
    newwords->back = NULL;
    return newwords;
  }
}

void push_back(char* word)
{
  words *newword=createwords(word),*cur;
  cur=head->next;
  if(head->next==NULL)
  {
    head->next=newword;
    newword->back=head;
  }
  else
  {
    while(cur->next!=NULL)
    {
      cur=cur->next;
    }
    cur->next=newword;
    newword->back=cur;
  }
}

void make_normal_words()
{
  char check[30];
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
  fclose(file);
}

void make_long_words()
{
   char check[30];
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
    fclose(file);
}

void make_hard_words()
{
  FILE *file=fopen("Hard Words.txt","w");

  for(int j=0;j<999;j++)
  {
    int randd=(rand()%20)+1;
    for(int i=0;i<randd;i++)
    {
      putc((rand()%94)+33,file);
    }
    fputs("\n",file);
  }
  fclose(file);
}

void print(int color,double discount)
{

  if(num_all_printed_word<max_word)
  {
    words *cur=head->next;
    for(int t=0;cur!=NULL&&t<=num_check_word;t++)
    {
      if(row==25)
        {
          game_over();
          return;
        }
      gotoxy(10,row-t);
      char s[30]="                             ";
      printf("%s",s);
      gotoxy(10,row-t);
      setcolor(color);
      printf("%s",cur->word);
      setcolor(1);
      gotoxy(17,27);
      printf("%d",scoree);
      cur=cur->next;
      if(row==25)
        {
          game_over();
          return;
        }
    }
    gotoxy(col,row);
    num_all_printed_word++;
    num_check_word++;
    num_word_har_dor++;
    row++;
    if(num_word_har_dor==10)
      {
        timee=timee*discount;
        num_dor++;
        num_word_har_dor=0;
      }
  }
}

char*chose_word_from_normal(char* word)
{
  word=malloc(11*sizeof(char));
  FILE *normal=fopen("Normal Words.txt","r+");
  int random=(rand()%9115);
    for(int i=0;i<random;i++)
    {
      fscanf(normal,"%s",word);
    }
  fclose(normal);
  return word;
}

char*chose_word_from_long(char* word)
{
  word=malloc(21*sizeof(char));
  FILE *longg=fopen("Long Words.txt","r+");
  int random=(rand()%741);
    for(int i=0;i<random;i++)
    {
      fscanf(longg,"%s",word);
    }
  fclose(longg);
  return word;
}

char*chose_word_from_hard(char* word)
{
  word=malloc(21*sizeof(char));
  FILE *hard=fopen("Hard Words.txt","r+");
  int random=(rand()%1000);
    for(int i=0;i<random;i++)
    {
      fscanf(hard,"%s",word);
    }
  fclose(hard);
  return word;
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void score(int x,int y)
{
   for(int i=0;i<=x;i++)
  {
    gotoxy(i,25);
    setcolor(6);
    char a=6;
    printf("%c",a);
    gotoxy(i,y+25);
    setcolor(6);
    printf("%c",a);
  }

  for(int j=25;j<25+y;j++)
  {
    gotoxy(0,j);
    setcolor(6);
    char a=6;
    printf("%c",a);
    gotoxy(x,j);
    setcolor(6);
    printf("%c",a);
  }
  gotoxy(10,27);

  setcolor(5);
  printf("Score:");
}

void game_over()
{
  clear();
  gotoxy(10,10);
  setcolor(4);
  printf("Game Over");
  setcolor(1);
  gotoxy(10,11);
  printf("%d",scoree);
  new_user.historyy[nobat_bazi].score=scoree;
  if(call==1)
  {
    new_user.historyy[nobat_bazi].level="easy";
    gotoxy(10,12);
    setcolor(2);
    printf("easy");
  }
  else if(call==2)
  {
    new_user.historyy[nobat_bazi].level="medium";
    gotoxy(10,12);
    setcolor(2);
    printf("medium");
  }
  else if(call==3)
  {
    new_user.historyy[nobat_bazi].level="hard";
    gotoxy(10,12);
    setcolor(2);
    printf("hard");
  }
  gotoxy(10,13);
  setcolor(3);
  printf("%d",num_dor);
  new_user.historyy[nobat_bazi].turn=num_dor;
  gotoxy(0,14);
  setcolor(7);
  int day, month, year;
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  day = local->tm_mday;            
  month = local->tm_mon + 1;      
  year = local->tm_year + 1900;   
  new_user.historyy[nobat_bazi].day=day;
  new_user.historyy[nobat_bazi].month=month;
  new_user.historyy[nobat_bazi].year=year;
  new_user.historyy[nobat_bazi].turn=num_dor;
  if(nobat_bazi==2)
  {
    nobat_bazi=-1;
  }
  new_user.nobat_bazi=nobat_bazi+1;
  fwrite(&new_user,sizeof(user),1,file);
  fclose(file);
  Sleep(5000);
  exit(1);
}

void victory()
{
  clear();
  gotoxy(10,10);
  setcolor(4);
  printf("You Got It");
  setcolor(1);
  gotoxy(10,11);
  printf("%d",scoree);
  new_user.historyy[nobat_bazi].score=scoree;
  if(call==1)
  {
    new_user.historyy[nobat_bazi].level="easy";
    gotoxy(10,12);
    setcolor(2);
    printf("easy");
  }
  else if(call==2)
  {
    new_user.historyy[nobat_bazi].level="medium";
    gotoxy(10,12);
    setcolor(2);
    printf("medium");
  }
  else if(call==3)
  {
    new_user.historyy[nobat_bazi].level="hard";
    gotoxy(10,12);
    setcolor(2);
    printf("hard");
  }
  gotoxy(0,13);
  setcolor(7);
  int day, month, year;
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  day = local->tm_mday;            
  month = local->tm_mon + 1;      
  year = local->tm_year + 1900;   
  new_user.historyy[nobat_bazi].day=day;
  new_user.historyy[nobat_bazi].month=month;
  new_user.historyy[nobat_bazi].year=year;
  new_user.historyy[nobat_bazi].turn=num_dor;
  if(nobat_bazi==2)
  {
    nobat_bazi=-1;
  }
  new_user.nobat_bazi=nobat_bazi+1;
  fwrite(&new_user,sizeof(user),1,file);
  fclose(file);
  Sleep(5000);
  exit(1);
}


