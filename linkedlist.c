#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 250

struct clip *build_a_lst();
struct clip *append();
void print_a_lst();
void split_line();

struct clip {
  int views;
  char *users;
  char *ids;
  char *titles;
  char *times;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  head = build_a_lst(*(argv+1));
  print_a_lst(head);
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[4];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  if ( (fp = fopen(fn, "r")) ) {
    while ( fgets(line, LINE_LENGTH, fp) ){
      //printf("%s", line);
      split_line(fields, line);
      //printf("%s %s %s %s\n", fields[0], fields[1], fields[2], fields[3]);
      hp = append(hp, fields);
    }
  }
  fclose(fp);
  return hp;
}

void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",";
  token = strtok(line, delim);
  do {
    fields[i] = malloc(strlen(token));
    strcpy(fields[i++], token);
  } while ( (token = strtok( NULL, delim )) );
}

struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;

  tp = malloc(sizeof(struct clip));

  tp->views = atoi(*five);
  tp->users = malloc(strlen(five[1]));
  strcpy(tp->users, five[1]);
  tp->ids = malloc(strlen(five[2]));
  strcpy(tp->ids, five[2]);
  tp->titles = malloc(strlen(five[3]));
  strcpy(tp->titles, five[3]);
  tp->times = malloc(strlen(five[4]));
  strcpy(tp->times, five[4]);

  if( !hp ) { hp = tp; }
  else {
    cp = hp;
    while ( cp->next ) { cp = cp->next; }
    cp->next = tp;
  }
  return hp;
}

void print_a_lst(struct clip *cp) {
  //int x = 1;
  while ( cp ) {
    printf("%d,%s,%s,%s,%s\n",cp->views,cp->users,cp->ids,cp->titles,cp->times);
    //printf("%d\n", x++);
    cp = cp->next;
  }
}

/* end */
