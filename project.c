#include<stdio.h>
#include <stdlib.h>
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

int main()
{
  menu();
  

  HANDLE thread_id = start_listening(my_callback_on_key_arrival);



  // WaitForSingleObject(thread_id, 1000);
  
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
  printf("1-sign in");
  gotoxy(15,2);
  printf("2-register");
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
    Sleep(2000);
    
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
  
}

void game_menu_history()
{

}
