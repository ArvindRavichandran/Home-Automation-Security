byte s[9] = {0, 0, 0, 0, 0, 0, 0, 0};
int z;
int x;
bool in[5] = {0,0,0,0};
bool oin[5] = {0,0,0,0};

void setup() {
  Serial.begin(9600);
  for (z = 2; z <= 5; z++)
  {
    pinMode(z, INPUT);
  }
  for (z = 6; z <= 13; z++)
  {
    pinMode(z, OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 7)
  {
    s[0] = Serial.read() - '0';
    s[1] = Serial.read() - '0';
    s[2] = Serial.read() - '0';
    s[3] = Serial.read() - '0';
    s[4] = Serial.read() - '0';
    s[5] = Serial.read() - '0';
    s[6] = Serial.read() - '0';
    s[7] = Serial.read() - '0';
    x = 1;
  }
  if (x == 1)
  {
    for (z = 0; z <= 7; z++)
    {
      if (s[z] == 0)
      {
        s[z] = 1;
      }
      else
      {
        s[z] = 0;
      }
    }
    x = 0;
  }
  
    in[0] = digitalRead(2);
    in[1] = digitalRead(3);
    in[2] = digitalRead(4);
    in[3] = digitalRead(5);
  for (z = 0; z <= 3; z++)
  {
    if (in[z] != oin[z] && in[z] == 1)
    {
     Serial.print(z);
    }
    oin[z] = in[z];
  }
    digitalWrite(6, s[0]);
    digitalWrite(7, s[1]);
    digitalWrite(8, s[2]);
    digitalWrite(9, s[3]);
    digitalWrite(10, s[4]);
    digitalWrite(11, s[5]);
    digitalWrite(12, s[6]);
    digitalWrite(13, s[7]);
  }
