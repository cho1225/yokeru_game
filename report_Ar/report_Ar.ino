#define IR_PIN 2            // IR Sensor pin

#define BEATTIME 500
#define SPEAKER 3

#define IR_BIT_LENGTH 32    // number of bits sent by IR remote
#define FirstLastBit 15     // divide 32 bits into two 15 bit chunks for integer variables. Ignore center two bits. they are all the same.
#define BIT_1 1500          // Binary 1 threshold (Microseconds)
#define BIT_0 450           // Binary 0 threshold (Microseconds)
#define BIT_START 4000      // Start bit threshold (Microseconds)
int remote_verify = 16128;  // verifies first bits are 11111100000000 different remotes may have different start codes

/* リモコンのキーに割り当てられた整数値を返す関数
 (例：power button ⇒ 整数値1429) */
int get_ir_key()
{
  int pulse[IR_BIT_LENGTH];
  int bits[IR_BIT_LENGTH];

  do {}
  while(pulseIn(IR_PIN, HIGH) < BIT_START);   //Wait for a start bit

  read_pulse(pulse);   // パルス長を読んで
  pulse_to_bits(pulse, bits); // パルス長をビット列に変換して
  RemoteVerify(bits);          // チェックをして
  return bits_to_int(bits);     // ビット列を正数値に変換する
}

/* パルスの長さ[msec] を保存 */
void read_pulse(int pulse[])
{
  for (int i = 0; i < IR_BIT_LENGTH; i++)
  {
        pulse[i] = pulseIn(IR_PIN, HIGH);
  }
}

/* パルスの長さ[msec] をビット列に変換 */
void pulse_to_bits(int pulse[], int bits[])
{
   for (int i = 0; i < IR_BIT_LENGTH; i++) {
      if ( pulse[i] > BIT_1 ) {
          bits[i] = 1;
      } else {
          if ( pulse[i] > BIT_0 ) {
                bits[i] = 0;
            } else {
                Serial.println("Error");
            }
      }
    }
}

/*
  check returns proper first 14 check bits
*/

void RemoteVerify(int bits[])
{
  int result = 0;
  int seed = 1;

  //Convert bits to integer
  for(int i = 0 ; i < (FirstLastBit) ; i++)
  {
    if(bits[i] == 1)
    {
    result += seed;
    }

    seed *= 2;
  }
  //verify first group of bits. delay for data stream to end, then try again.
  if (remote_verify != result) {delay (60); get_ir_key();} 
}


/* ビット列を整数値に変換 */
int bits_to_int(int bits[])
{
  int result = 0;
  int seed = 1;
  for (int i = (IR_BIT_LENGTH-FirstLastBit) ; i < IR_BIT_LENGTH ; i++)
  {
    if (bits[i] == 1) {
        result += seed;
    }
     seed *= 2;
  }
  return result;
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  int key = get_ir_key();

  digitalWrite(LED_BUILTIN, LOW);
  do_response(key);
  delay(50);

  if(Serial.available() > 0){
    char c = Serial.read();
    if(c == 'a'){
      tone(SPEAKER, 523, BEATTIME);
      delay(BEATTIME);
      tone(SPEAKER, 494, BEATTIME);
      delay(BEATTIME);
      tone(SPEAKER, 466, BEATTIME);
      delay(BEATTIME);
      tone(SPEAKER, 440, BEATTIME);
      delay(BEATTIME);
      tone(SPEAKER, 415, BEATTIME);
      delay(BEATTIME);
      tone(SPEAKER, 330, BEATTIME);
      delay(BEATTIME);
      c = 'b';
    }
  }
}


void do_response(int key){
  int p = 0;
  switch(key){
    case 30472:   // 2 >> up
      p = 2;
      Serial.write(p);
      break;

    case 30090:   // 4 >> left
      p = 1;
      Serial.write(p);
      break;
      
    case 29835:   // 6 >> right
      p = 3;
      Serial.write(p);
      break;

    case 29452:   // 8 >> down
      p = 4;
      Serial.write(p);
      break;
      
  }
}
