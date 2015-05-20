#include <Servo.h>
#include <SoftwareSerial.h>
// where, open, grab
Servo tu ; // 100, 0
Servo in ; // 160, 60
Servo mi ; // 150, 40
Servo ri ; // 130, 30
Servo li ; // 150, 40

int tem_ba = 100 ;
int ind_ba = 160 ;
int mid_ba = 150 ;
int rin_ba = 130 ;
int lit_ba = 150 ;

SoftwareSerial mySerial(2, 3); // RX, TX


char start = 0 ;
char total[27] = {
  0,
}
;
char lo[2] = {
  0, 0
}
;
int i = 0, j = 0, c = 0 ;

int thu = 0 ;
int ind = 0 ;
int mid = 0 ;
int rin = 0 ;
int lit = 0 ;

char tem1, tem2, tem3 ;

unsigned long count = 0 ;
int end_flag = 1 ;
int len = 24 ;


void setup()
{
  pinMode(13, OUTPUT) ;
  tu.attach(11) ;
  in.attach(10) ;
  mi.attach(9) ;
  ri.attach(8) ;
  li.attach(7) ;
  Serial.begin(9600);


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400);
  tu.write(tem_ba) ;
  in.write(ind_ba) ;
  mi.write(mid_ba) ;
  ri.write(rin_ba) ;
  li.write(lit_ba) ;
  Serial.println("start") ;
}

void loop() // run over and over
{
  if (mySerial.available()) {
    digitalWrite(13, HIGH) ;
    for ( i = 0; i < 27; i++) total[i] = 0 ;

    len = 0 ;
    total[0] = mySerial.read() ;
    if ((total[0] == '[') ) {
      mySerial.readBytes(lo, 2) ;
      len = ((lo[0] - '0') * 10) + (lo[1] - '0') - 1 ;
      mySerial.readBytes(total, len) ;
      if (scan(len, ']') != -1) {

        i = scan(len, 'a') ;
        if (i != -1 ) {
          c = scan(len, 'b') - i - 1 ;
          thu = 0 ;
          for ( j = (scan(len, 'b') - 1); i < j; j--) {
            thu += (total[j] - '0') * squ(10, (i - j + c)) ;
          }
          tu.write(thu) ;
          delay(50) ;
        }

        i = scan(len, 'c') ;
        if (i != -1 ) {
          c = scan(len, 'd') - i - 1 ;
          ind = 0 ;
          for ( j = (scan(len, 'd') - 1); i < j; j--) {
            ind += (total[j] - '0') * squ(10, (i - j + c)) ;
          }
          in.write(ind) ;
          delay(50) ;
        }

        i = scan(len, 'e') ;
        if (i != -1 ) {
          c = scan(len, 'f') - i - 1 ;
          mid = 0 ;
          for ( j = (scan(len, 'f') - 1); i < j; j--) {
            mid += (total[j] - '0') * squ(10, (i - j + c)) ;
          }
          mi.write(mid) ;
          delay(50) ;
        }

        i = scan(len, 'g') ;
        if (i != -1 ) {
          c = scan(len, 'h') - i - 1 ;
          rin = 0 ;
          for ( j = (scan(len, 'h') - 1); i < j; j--) {
            rin += (total[j] - '0') * squ(10, (i - j + c)) ;
          }
          ri.write(rin) ;
          Serial.println(rin) ;
          delay(50) ;
        }

        i = scan(len, 'i') ;
        if (i != -1 ) {
          c = scan(len, 'j') - i - 1 ;
          lit = 0 ;
          for ( j = (scan(len, 'j') - 1); i < j; j--) {
            lit += (total[j] - '0') * squ(10, (i - j + c)) ;
          }
          li.write(lit) ;
          Serial.println(lit) ;
          delay(50) ;
        }

        Serial.println(thu) ;
        Serial.println(ind) ;
        Serial.println(mid) ;
        Serial.println(rin) ;
        Serial.println(lit) ;
        Serial.println() ;

      }
    }
    digitalWrite(13, LOW) ;
    mySerial.flush() ;
  }
}

int scan(int len, char what)
{
  for (int sto = 0; sto < len; sto++) {
    if (total[sto] == what) return sto ;
  }
  return -1 ;
}


int squ(int num, int many)
{
  int squ = 1 ;
  for (int sto = 0; sto < many; sto++) squ *= num ;
  return squ ;
}

