#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  //pipe from parent to child
  int to_child[2];
  pipe(to_child);
  //pipe from child to parent
  int to_parent[2];
  pipe(to_parent);

  int f;
  f = fork(); //fork off one child
  int num = 20;

  int READ = 0;
  int WRITE = 1;

  //parent sending number to child
  if(f != 0){
    close(to_child[READ]);
    close(to_parent[WRITE]);
    write(to_child[WRITE], &num, sizeof(num));
    printf("child sending: %d\n", num);
  }
  //child receiving the number and performing arithmetic
  else{
    close(to_parent[READ]);
    close(to_child[WRITE]);
    int msg;
    read(to_child[READ], &msg, sizeof(msg));
    msg = msg * msg;
    write(to_parent[WRITE], &msg, sizeof(msg));
    printf("child doing math on: %d\n", msg);
  }
  //parent receiving the math-ed number
  if(f != 0){
    int final;
    read(to_parent[READ], &final, sizeof(final));
    printf("parent received: %d\n", final);
  }

}
