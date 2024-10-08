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

int dots[32];
int dot_lines[4][8];
int rows[4] = {2,3,4,5};
int cols[8] = {24,25,26,27,28,29,30,31};
char txt[40];

void setup(void) {
  int i;
  void clear_dots(void);
  void select_row_col(int,int);
  void select_bnum(int);
  
  Serial.begin(115200);
  //  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    //  }
  clear_dots();
  //  dots[4][8] = {
  //    {0,1,0,1,0,1,0,1},
  //    {1,0,1,0,1,0,1,0},
  //    {0,1,0,1,0,1,0,1},
  //    {1,0,1,0,1,0,1,0}
  //  };
  for(i=0;i<8;i++) {
    dot_lines[0][i] = i % 2;
    dot_lines[1][i] = (i % 2)+1;
    dot_lines[2][i] = i % 2;
    dot_lines[3][i] = (i % 2)+1;
  }
}

void loop(void) {
  void matrix8x4(void);
  matrix8x4();
  // int i,j;
  // void clear_dots(void);
  // for (i=0;i<RNUM;i++) {
  //   for (j=0;j<CNUM;j++) {
  //     if (dots[i][j]==1) {
  //       digitalWrite(rows[i],HIGH);
  //       digitalWrite(cols[j],HIGH);
  //     } else {
  //       digitalWrite(cols[i],LOW);
  //       digitalWrite(rows[j],LOW);
  //     }
  //   }
  // }
}

void matrix8x4(void) {
  int r,c;
  for(r=0;r<4;r++) {
    digitalWrite(rows[r],HIGH);
    for(c=0;c<8;c++) {
      if (dot_lines[r][c]==1) {
        digitalWrite(cols[c],HIGH);
      } else {
        digitalWrite(cols[c],LOW);
      }
    }
    delay(1);
    digitalWrite(rows[r],LOW);
  }
}

void select_bnum(int b) {
  int i,r,c;
  void clear_dots(void);
  void select_row_col(int,int);
  
  if ((b<0)||(b>32)) return;
  if (b==0) {
    clear_dots();
    for(i=0;i<32;i++) {
      dots[i]=0;
    }
    return;
  }
  c = (b-1) % 8;
  r = (b-1) / 8;
  c++;
  r++;
  select_row_col(r,c);
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

void select_row_col(int r,int c) {
  int i;
  r--;
  c--;
  for(i=0;i<RNUM;i++) {
    if (r==i) {
      digitalWrite(rows[i],HIGH);
    } else {
      digitalWrite(rows[i],LOW);
    }
  }
  for(i=0;i<CNUM;i++) {
    if (c==i) {
      digitalWrite(cols[i],HIGH);
    } else {
      digitalWrite(cols[i],LOW);
    }
  }
}
