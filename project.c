#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include <windows.h>
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
  struct words *back;
}words;

words *head;
words *tail;
words *cur_ptr;
int len=0,row=1,col=15,num_word_har_dor=0,cruser=1,num_dor=0,num_all_words=0;
double timee;
HANDLE thread_id;
words* createwords(char* word);

void push_back(char* word);

void pop_front();

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
void print(int color);
char*chose_word_from_normal(char* word);
char*chose_word_from_long(char* word);
char*chose_word_from_hard(char* word);
void hidecursor();


int main()
{
  head=createwords(NULL);
  tail=createwords(NULL);
  cur_ptr=createwords(NULL);
  cur_ptr=head;
  srand(time(NULL));
  make_normal_words();
  make_long_words();
  make_hard_words();
  hidecursor();
  // menu();
  easy();
  WaitForSingleObject(thread_id,INFINITE);
  return 0;
}

void my_callback_on_key_arrival(char c)
{
  
  if(head->next->word[len]==c)
  {
    gotoxy(col,row-1);
    setcolor(4);
    printf("%c",head->next->word[len]);
    setcolor(15);
    col++;
    len++;
    if(len==strlen(head->next->word))
    {
      pop_front();
      num_all_words--;
      row--;
      len=0;
      col=15;
      print(15);
      return;
    }
  }
  else if(head->next->word[len]!=c)
  {
    gotoxy(col,row-1);
    setcolor(6);
    printf("%c",head->next->word[len]);
    setcolor(15);
    col++;
    len++;
    if(len==strlen(head->next->word))
    {
      pop_front();
      num_all_words--;
      row--;
      len=0;
      col=15;
      print(15);
      return;
    }
  }

  
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
  FILE *file=fopen(new_user.username,"w");
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
  make_board(40,40); 
  timee=10000.000;
  for(int t=0;timee>1000.000;t++)
  {
    char word[21][50];
    int num_normal_word=10,num_hard_word=10-num_normal_word;
    for(int i=0;i<50;i++)
    {
      int choose = (rand()%10)+1;
      if(choose>num_hard_word)
      {
        push_back(chose_word_from_normal(word[i]));
      }
      else
      {
        int choose1=(rand()%num_hard_word)+1;
        if(choose1==3)
        {
          push_back(chose_word_from_hard(word[i]));
        }
        else
        {
          push_back(chose_word_from_long(word[i]));
        }
      }      
    }
    num_normal_word=num_normal_word*(.935);
    timee =timee*(0.8);
  }
  thread_id = start_listening(my_callback_on_key_arrival);
  timee=10000.000;
  for(num_dor=0;timee>1000.000;num_dor++)
  {
    for(num_word_har_dor=0;num_word_har_dor<10;)
    {
      print(15);
      // words *cur=head->next;
      // for(int t=0;cur!=NULL&&t<=num_all_words;t++)
      // {
      //   printf("\n");
      //   setcolor(15);
      //   gotoxy(15,row-t);
      //   char s[20]="                ";
      //   printf("%s",s);
      //   gotoxy(15,row-t);
      //   printf("%s%d%d",cur->word,num_word_har_dor,num_dor);
      //   gotoxy(15,row-t);
      //   cur=cur->next;
      //   if(row==40)
      //     {
      //       gotoxy(0,41);
      //       exit(0);
      //     }
      // }
      // gotoxy(col,row);
      // num_all_words++;
      // num_word_har_dor++;
      // row++;
      // if(row==40)
      // {
      //   gotoxy(0,41);
      //   exit(0);
      // }
      Sleep(timee);
    }
  }
}


void medium()
{

}

void hard()
{

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
    tail->back=newword;
  }
  else
  {
    while(cur->next!=NULL)
    {
      cur=cur->next;
    }
    cur->next=newword;
    newword->back=cur;
    tail->back=newword;
  }
}

void pop_front()
{
  words *temp = head->next;
  if(head->next==NULL)
  {
      printf("Impossible to delete from empty Singly Linked List");
      return;
  }
  head->next=head->next->next;
  free(temp);
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
  fclose(file);
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
      putc((rand()%96)+32,file);
    }
    fputs("\n",file);
  }
  fclose(file);
}

void print(int color)
{
  words *cur=head->next;
  for(int t=0;cur!=NULL&&t<=num_all_words;t++)
  {
    setcolor(color);
    gotoxy(15,row-t);
    char s[20]="                ";
    printf("%s",s);
    gotoxy(15,row-t);
    printf("%s%d%d",cur->word,num_word_har_dor,num_dor);
    cur=cur->next;
    if(num_word_har_dor==9)
    {
      num_dor++;
      timee=timee*0.8;
      printf("\n%lf\n",timee);
      num_word_har_dor=0;
      if(timee<=1000)
      {
        gotoxy(0,41);
        exit(0);
      }
    }
    if(row==40)
      {
        gotoxy(0,41);
        exit(0);
      }
  }
  gotoxy(col,row);
  num_all_words++;
  num_word_har_dor++;
  row++;
}

char*chose_word_from_normal(char* word)
{
  word=malloc(21*sizeof(char));
  FILE *normal=fopen("Normal Words.txt","r+");
  int random=(rand()%9115);
    for(int i=0;i<random;i++)
    {
      fscanf(normal,"%s",word);
    }
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


