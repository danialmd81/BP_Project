#include <stdlib.h>
#include "helper_windows.h"
#include "colorize.h"

typedef struct 
{

}data;

void my_callback_on_key_arrival(char c);

void make_board();

void fill_board();

int main()
{

  
  
  HANDLE thread_id = start_listening(my_callback_on_key_arrival);



  WaitForSingleObject(thread_id, INFINITE);
  return 0;
}

void my_callback_on_key_arrival(char c)
{
}

void make_board()
{
    for(int i=0 ;i<40;i++)
    {
        gotoxy(i,3);
        setcolor(3);
        printf("#");
        gotoxy(i,40);
        setcolor(3);
        printf("#");
    }

  for(int j=3;j<40;j++)
    {
        gotoxy(0,j);
        setcolor(3);
        printf("#");
        gotoxy(40,j);
        setcolor(3);
        printf("#");
    }
}