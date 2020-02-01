#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Red "#C0392B"
#define Green "#1ABC9C"
#define Orange "#F39C12"
#define Brown "#A54A00"
#define LGrey "#A5A5A5"
#define White "#FFFFFF"
#define Blue "#0097E2"

char auth[] = "8945708cd84b440a95b71a1ea3420b2c";
char ssid[] = "Home";
char pass[] = "3pvmravi5";

int area = 2;
int oarea = 2;
int p[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int op[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int mp[5] = {1, 1, 1, 1};
int s[3] = {0, 0};
int os[3] = {0, 0};
String c[10] = {"", "", "", "", "", "", "", "", ""};
String oc[10] = {"", "", "", "", "", "", "", "", ""};
String orc[10] = {"", "", "", "", "", "", "", "", ""};
int in;

BLYNK_WRITE(V0) {
  area = param.asInt();
}

BLYNK_WRITE(V1) {
  p[0] = param.asInt();
}

BLYNK_WRITE(V2) {
  p[1] = param.asInt();
}

BLYNK_WRITE(V3) {
  p[2] = param.asInt();
}

BLYNK_WRITE(V4) {
  p[3] = param.asInt();
  if (p[3] == 0)
  {
    Blynk.setProperty(V4, "onLabel", s[0]);
  }
}

BLYNK_WRITE(V5) {
  p[4] = param.asInt();
  if (p[4] == 0)
  {
    Blynk.setProperty(V5, "onLabel", s[1]);
  }
}

BLYNK_WRITE(V6) {
  p[5] = param.asInt();
}

BLYNK_WRITE(V7) {
  p[6] = param.asInt();
}

BLYNK_WRITE(V8) {
  p[7] = param.asInt();
}

BLYNK_WRITE(V9) {
  p[8] = param.asInt();
}

BLYNK_WRITE(V14) {
  s[0] = param.asInt();
  Blynk.setProperty(V4, "onLabel", s[0]);
}

BLYNK_WRITE(V15) {
  s[1] = param.asInt();
  Blynk.setProperty(V5, "onLabel", s[1]);
}

void setup() {
  Serial.setTimeout(100);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
  digitalWrite(D3, 1);
  digitalWrite(D4, 1);
  digitalWrite(D5, 1);
  digitalWrite(D6, 1);
  digitalWrite(D7, 1);
  digitalWrite(D8, 1);
  Blynk.syncVirtual(V0);
  delay(1000);
}

void loop() {
  switch (area)
  {
    case 1:
      {
        orc[0] = LGrey;
        orc[1] = LGrey;
        orc[2] = LGrey;
        orc[3] = LGrey;
        orc[4] = LGrey;
        orc[5] = Brown;
        orc[6] = Brown;
        orc[7] = White;
        orc[8] = White;
        break;
      }
    case 2:
      {
        orc[0] = LGrey;
        orc[1] = LGrey;
        orc[2] = LGrey;
        orc[3] = Brown;
        orc[4] = Brown;
        orc[5] = White;
        orc[6] = White;
        orc[7] = White;
        orc[8] = White;
        break;
      }
  }
  if (area == 2) {
    if (oarea != area)
    {
      if (op[0] != p[0]) {
        p[0] = op[0];
        Blynk.virtualWrite(V1, p[0]);
      }
      if (op[1] != p[1]) {
        p[1] = op[1];
        Blynk.virtualWrite(V2, p[1]);
      }
      if (op[2] != p[2]) {
        p[2] = op[2];
        Blynk.virtualWrite(V3, p[2]);
      }
      if (op[3] != p[3]) {
        p[3] = op[3];
        Blynk.virtualWrite(V4, p[3]);
      }
      if (op[4] != p[4]) {
        p[4] = op[4];
        Blynk.virtualWrite(V5, p[4]);
      }
      if (op[5] != p[5]) {
        p[5] = op[5];
        Blynk.virtualWrite(V6, p[5]);
      }
      if (op[6] != p[6]) {
        p[6] = op[6];
        Blynk.virtualWrite(V7, p[6]);
      }
      if (op[7] != p[7]) {
        p[7] = op[7];
        Blynk.virtualWrite(V8, p[7]);
      }
      if (op[8] != p[8]) {
        p[8] = op[8];
        Blynk.virtualWrite(V9, p[8]);
      }
    }

    for (int z = 0; z <= 8; z++)
    {
      c[z] = orc[z];
    }

    digitalWrite(D0, p[0]);
    digitalWrite(D1, p[1]);
    digitalWrite(D2, p[2]);
    digitalWrite(D3, p[3]);
    digitalWrite(D4, p[4]);
    digitalWrite(D5, p[5]);
    digitalWrite(D6, p[6]);
    digitalWrite(D7, p[7]);
    digitalWrite(D8, p[8]);

    if (oc[0] != c[0]) {
      Blynk.setProperty(V1 , "color", c[0]);
      oc[0] = c[0];
    }
    if (oc[1] != c[1]) {
      Blynk.setProperty(V2 , "color", c[1]);
      oc[1] = c[1];
    }
    if (oc[2] != c[2]) {
      Blynk.setProperty(V3 , "color", c[2]);
      oc[2] = c[2];
    }
    if (oc[3] != c[3]) {
      Blynk.setProperty(V4 , "color", c[3]);
      oc[3] = c[3];
    }
    if (oc[4] != c[4]) {
      Blynk.setProperty(V5 , "color", c[4]);
      oc[4] = c[4];
    }
    if (oarea != area) {
      delay(500);
    }
    if (oc[5] != c[5]) {
      Blynk.setProperty(V6 , "color", c[5]);
      oc[5] = c[5];
    }
    if (oc[6] != c[6]) {
      Blynk.setProperty(V7 , "color", c[6]);
      oc[6] = c[6];
    }
    if (oc[7] != c[7]) {
      Blynk.setProperty(V8 , "color", c[7]);
      oc[7] = c[7];
    }
    if (oc[8] != c[8]) {
      Blynk.setProperty(V9 , "color", c[8]);
      oc[8] = c[8];
    }
  }
  else
  {
    for (int z = 0; z <= 8; z++)
    {
      oc[z] = orc[z];
      if (oarea == 2 && oarea != area)
      {
        op[z] = p[z];
      }
    }
  }
  oarea = area;


  if (os[0] != s[0] || os[1] != s[1])
  {
    for (int i = 3; i >= 0; i--) {
      if ((s[0] >> i) & 1)
      {
        Serial.print("1");
      }
      else
      {
        Serial.print("0");
      }
    }
    for (int i = 3; i >= 0; i--) {
      if ((s[1] >> i) & 1)
      {
        Serial.print("1");
      }
      else
      {
        Serial.print("0");
      }
    }
    os[0] = s[0];
    os[1] = s[1];
  }
  if (Serial.available())
  {
    in = Serial.parseInt();
    switch (in)
    {
      case 0:
        {
          if (mp[0] == 1)
          {
            p[0] = op [0] = 0;
          }
          else
          {
            p[0] = op[0] = 1;
          }
          mp[0] = p[0];
          if (area == 2)
          {
          Blynk.virtualWrite(V1, p[0]);
          }
          digitalWrite(D0, p[0]);
          break;
        }
      case 1:
        {
          if (mp[1] == 1)
          {
            p[1] = op[1] = 0;
          }
          else
          {
            p[1] = op[1] = 1;
          }
          mp[1] = p[1];
          if (area == 2)
          {
          Blynk.virtualWrite(V2, p[1]);
          }
          digitalWrite(D1, p[1]);
          break;
        }
      case 2:
        {
          if (mp[3] == 1)
          {
            p[3] = op[3] = 0;
          }
          else
          {
            p[3] = op[3] = 1;
          }
          mp[3] = p[3];
          if (area == 2)
          {
          Blynk.virtualWrite(V4, p[3]);
          }
          digitalWrite(D3, p[3]);
          break;
        }
      case 3:
        {
          if (mp[4] == 1)
          {
            p[4] = op[4] = 0;
          }
          else
          {
            p[4] = op[4] = 1;
          }
          mp[4] = p[4];
          if (area == 2)
          {
          Blynk.virtualWrite(V5, p[4]);
          }
          digitalWrite(D4, p[4]);
          break;
        }
        in = 5;
    }
  }
  Blynk.run();
}
