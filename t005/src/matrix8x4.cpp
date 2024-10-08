#include <Arduino.h>

#define RNUM   4
#define ROW1   2
#define ROW2   3
#define ROW3   4
#define ROW4   5

#define CNUM   8
#define COL1   24
#define COL2   25
#define COL3   26
#define COL4   27
#define COL5   28
#define COL6   29
#define COL7   30
#define COL8   31

int dots[4][8];
int rows[4] = {2,3,4,5};
int cols[8] = {24,25,26,27,28,29,30,31};

void setup(void) {
  char txt[40];
  void clear_dots(void);
  int i,j;
  Serial.begin(115200);
  //  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    //  }
  clear_dots();
  //  dots[][] = {
  //    {0,1,0,1,0,1,0,1},
  //    {1,0,1,0,1,0,1,0},
  //    {0,1,0,1,0,1,0,1},
  //    {1,0,1,0,1,0,1,0}
  //  };
  for (i=0;i<RNUM;i++) {
    for (j=0;j<CNUM;j++) {
      dots[i][j] = ((i%2)+j)%2;
    }
  }
  for (i=0;i<RNUM;i++) {
    for (j=0;j<CNUM;j++) {
      sprintf(txt,"%d x %d = %d",i,j,dots[i][j]);
      Serial.println(txt);
    }
  }
}

void loop(void) {
  int i,j;
  void clear_dots(void);
  for (i=0;i<RNUM;i++) {
    for (j=0;j<CNUM;j++) {
      if (dots[i][j]==1) {
        digitalWrite(rows[i],HIGH);
        digitalWrite(cols[j],HIGH);
      } else {
        digitalWrite(cols[i],LOW);
        digitalWrite(rows[j],LOW);
      }
    }
  }
}

void clear_dots(void) {
  int i;
  for (i=0;i<RNUM;i++) {
    pinMode(rows[i],OUTPUT);
    digitalWrite(rows[i],LOW);
  }
  for (i=0;i<CNUM;i++) {
    pinMode(cols[i],OUTPUT);
    digitalWrite(cols[i],LOW);
  }
}

