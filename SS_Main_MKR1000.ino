#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleWiFiShield101.h>

#define BLYNK_PRINT SerialUSB
#define Red "#C0392B"
#define Green "#1ABC9C"
#define Orange "#F39C12"
#define Brown "#9E4700"
#define White "#FFFFFF"
#define Grey "#333333"
#define Blue "#0097E2"

String zname[17] = {
  "Main Door",
  "Thatha Room",
  "Kitchen",
  "Backdoor",
  "Service Area",
  "GF Hall",
  "Visitor Room",
  "Arvind Room",
  "FF Hall",
  "OTS Door",
  "Master Bedroom",
  "Ashwath Room",
  "SF Main Door",
  "SF hall",
  "SF room",
  "SF bathroom"
};

char auth[] = "87f7088def35485ea826f5b02cdd2ea8";

char ssid[] = "Home";
char pass[] = "3pvmravi5";

int ozstatus [17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int zstatus[17];
//1 is closed and 0 is open
int ozbypass [17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int zbypass[17];
//1 is bypassed 0 is unbypassed
String zcolor[17] = {};
int inlist[17] = {};
int arm = 0;
int stat = 0;
bool a = true;
int b = 0;
int c = 0;
String i = "";
String j;
String m;
String cmd = "";
int rowId;
int w;
int x;
int buzz;


BlynkTimer timer;

BLYNK_WRITE(V17) {
  zbypass[0] = param.asInt();
}

BLYNK_WRITE(V18) {
  zbypass[1] = param.asInt();
}

BLYNK_WRITE(V19) {
  zbypass[2] = param.asInt();
}

BLYNK_WRITE(V20) {
  zbypass[3] = param.asInt();
}

BLYNK_WRITE(V21) {
  zbypass[4] = param.asInt();
}

BLYNK_WRITE(V22) {
  zbypass[5] = param.asInt();
}

BLYNK_WRITE(V23) {
  zbypass[6] = param.asInt();
}

BLYNK_WRITE(V24) {
  zbypass[7] = param.asInt();
}

BLYNK_WRITE(V25) {
  zbypass[8] = param.asInt();
}

BLYNK_WRITE(V26) {
  zbypass[9] = param.asInt();
}

BLYNK_WRITE(V27) {
  zbypass[10] = param.asInt();
}

BLYNK_WRITE(V28) {
  zbypass[11] = param.asInt();
}

BLYNK_WRITE(V29) {
  zbypass[12] = param.asInt();
}

BLYNK_WRITE(V30) {
  zbypass[13] = param.asInt();
}

BLYNK_WRITE(V31) {
  zbypass[14] = param.asInt();
}

BLYNK_WRITE(V32) {
  zbypass[15] = param.asInt();
}

WidgetTerminal terminal(V38);

BLYNK_WRITE(V38) {
  i = param.asStr();
}

BLYNK_WRITE(V100) {
  m = param.asStr();
}

BLYNK_WRITE(V0) {
  arm = param.asInt();
}

BLYNK_WRITE(V39) {
  cmd = param[0].asStr();
  rowId = param[1].asInt();
  b = 0;
}


void setup()
{


  int row = 0;
  SerialUSB.begin(38400);
  Blynk.begin(auth, ssid, pass);
  pinMode(6, OUTPUT);
  timer.setInterval(2000L, push);
  Blynk.virtualWrite(V39, "clr");
  Blynk.virtualWrite(V39, "add", row, "Change The Pin", row + 1);
  row++;
  Blynk.virtualWrite(V39, "add", row, "Toggle Arming", row + 1);
  row++;
  Blynk.virtualWrite(V39, "add", row, "Show Zone List", row + 1);
  row = 0;
  Blynk.virtualWrite(V37, "clr");
}


void loop()
{
  while (not(WiFi.status() == WL_CONNECTED || WiFi.status() == WL_AP_CONNECTED))
  {
    Blynk.begin(auth, ssid, pass);
    a = true;
    delay(2000);
  }
  if ( a == true)
  {
    Blynk.syncVirtual(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16);
    delay(2750);
    Blynk.syncVirtual(V0, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V100, V40);
    a = false;
    delay (3500);
  }

  if (SerialUSB.available())
  {
    for (int z = 0; z <= 15; z++)
    {
      zstatus[z] = SerialUSB.read() - '0';
    }
    SerialUSB.print("OK");
  }
  if (cmd == "")
  {
    for ( int z = 0; z <= 15; z++)
    {
      if (zbypass[z] != ozbypass[z])
      {
        c++;
      }
    }
    if (c != 0)
    {
      Blynk.virtualWrite(V37, "clr");
      for (int z = 0; z <= 15; z++)
      {
        if (zbypass[z] == 1)
        {
          Blynk.virtualWrite(V37, "add", z, zname[z], "z" + String(z + 1));
          delay(200);
        }
      }
      c = 0;
    }
  }

  if (ozstatus[0] != zstatus[0] || ozbypass[0] != zbypass[0]) {
    zcolor[0] = colr(zstatus[0], zbypass[0]);
    stat = zstat(zstatus[0], zbypass[0]);
    Blynk.virtualWrite(V1, stat);
    Blynk.syncVirtual(V17);
    Blynk.setProperty(V1, "color", zcolor[0]);
    ozstatus[0] = zstatus[0];
    ozbypass[0] = zbypass[0];
  }
  if (ozstatus[1] != zstatus[1] || ozbypass[1] != zbypass[1]) {
    zcolor[1] = colr(zstatus[1], zbypass[1]);
    stat = zstat(zstatus[1], zbypass[1]);
    Blynk.virtualWrite(V2, stat);
    Blynk.syncVirtual(V18);
    Blynk.setProperty(V2, "color", zcolor[1]);
    ozstatus[1] = zstatus[1];
    ozbypass[1] = zbypass[1];
  }
  if (ozstatus[2] != zstatus[2] || ozbypass[2] != zbypass[2]) {
    zcolor[2] = colr(zstatus[2], zbypass[2]);
    stat = zstat(zstatus[2], zbypass[2]);
    Blynk.virtualWrite(V3, stat);
    Blynk.syncVirtual(V19);
    Blynk.setProperty(V3, "color", zcolor[2]);
    ozstatus[2] = zstatus[2];
    ozbypass[2] = zbypass[2];
  }
  if (ozstatus[3] != zstatus[3] || ozbypass[3] != zbypass[3]) {
    zcolor[3] = colr(zstatus[3], zbypass[3]);
    stat = zstat(zstatus[3], zbypass[3]);
    Blynk.virtualWrite(V4, stat);
    Blynk.syncVirtual(V20);
    Blynk.setProperty(V4, "color", zcolor[3]);
    ozstatus[3] = zstatus[3];
    ozbypass[3] = zbypass[3];
  }
  if (ozstatus[4] != zstatus[4] || ozbypass[4] != zbypass[4]) {
    zcolor[4] = colr(zstatus[4], zbypass[4]);
    stat = zstat(zstatus[4], zbypass[4]);
    Blynk.virtualWrite(V5, stat);
    Blynk.syncVirtual(V21);
    Blynk.setProperty(V5, "color", zcolor[4]);
    ozstatus[4] = zstatus[4];
    ozbypass[4] = zbypass[4];
  }
  if (ozstatus[5] != zstatus[5] || ozbypass[5] != zbypass[5]) {
    zcolor[5] = colr(zstatus[5], zbypass[5]);
    stat = zstat(zstatus[5], zbypass[5]);
    Blynk.virtualWrite(V6, stat);
    Blynk.syncVirtual(V22);
    Blynk.setProperty(V6, "color", zcolor[5]);
    ozstatus[5] = zstatus[5];
    ozbypass[5] = zbypass[5];
  }
  if (ozstatus[6] != zstatus[6] || ozbypass[6] != zbypass[6]) {
    zcolor[6] = colr(zstatus[6], zbypass[6]);
    stat = zstat(zstatus[6], zbypass[6]);
    Blynk.virtualWrite(V7, stat);
    Blynk.syncVirtual(V23);
    Blynk.setProperty(V7, "color", zcolor[6]);
    ozstatus[6] = zstatus[6];
    ozbypass[6] = zbypass[6];
  }
  if (ozstatus[7] != zstatus[7] || ozbypass[7] != zbypass[7]) {
    zcolor[7] = colr(zstatus[7], zbypass[7]);
    stat = zstat(zstatus[7], zbypass[7]);
    Blynk.virtualWrite(V8, stat);
    Blynk.syncVirtual(V24);
    Blynk.setProperty(V8, "color", zcolor[7]);
    ozstatus[7] = zstatus[7];
    ozbypass[7] = zbypass[7];
  }
  if (ozstatus[8] != zstatus[8] || ozbypass[8] != zbypass[8]) {
    zcolor[8] = colr(zstatus[8], zbypass[8]);
    stat = zstat(zstatus[8], zbypass[8]);
    Blynk.virtualWrite(V9, stat);
    Blynk.syncVirtual(V25);
    Blynk.setProperty(V9, "color", zcolor[8]);
    ozstatus[8] = zstatus[8];
    ozbypass[8] = zbypass[8];
  }
  if (ozstatus[9] != zstatus[9] || ozbypass[9] != zbypass[9]) {
    zcolor[9] = colr(zstatus[9], zbypass[9]);
    stat = zstat(zstatus[9], zbypass[9]);
    Blynk.virtualWrite(V10, stat);
    Blynk.syncVirtual(V26);
    Blynk.setProperty(V10, "color", zcolor[9]);
    ozstatus[9] = zstatus[9];
    ozbypass[9] = zbypass[9];
  }
  if (ozstatus[10] != zstatus[10] || ozbypass[10] != zbypass[10]) {
    zcolor[10] = colr(zstatus[10], zbypass[10]);
    stat = zstat(zstatus[10], zbypass[10]);
    Blynk.virtualWrite(V11, stat);
    Blynk.syncVirtual(V27);
    Blynk.setProperty(V11, "color", zcolor[10]);
    ozstatus[10] = zstatus[10];
    ozbypass[10] = zbypass[10];
  }
  if (ozstatus[11] != zstatus[11] || ozbypass[11] != zbypass[11]) {
    zcolor[11] = colr(zstatus[11], zbypass[11]);
    stat = zstat(zstatus[11], zbypass[11]);
    Blynk.virtualWrite(V12, stat);
    Blynk.syncVirtual(V28);
    Blynk.setProperty(V12, "color", zcolor[11]);
    ozstatus[11] = zstatus[11];
    ozbypass[11] = zbypass[11];
  }
  if (ozstatus[12] != zstatus[12] || ozbypass[12] != zbypass[12]) {
    zcolor[12] = colr(zstatus[12], zbypass[12]);
    stat = zstat(zstatus[12], zbypass[12]);
    Blynk.virtualWrite(V13, stat);
    Blynk.syncVirtual(V29);
    Blynk.setProperty(V13, "color", zcolor[12]);
    ozstatus[12] = zstatus[12];
    ozbypass[12] = zbypass[12];
  }
  if (ozstatus[13] != zstatus[13] || ozbypass[13] != zbypass[13]) {
    zcolor[13] = colr(zstatus[13], zbypass[13]);
    stat = zstat(zstatus[13], zbypass[13]);
    Blynk.virtualWrite(V14, stat);
    Blynk.syncVirtual(V30);
    Blynk.setProperty(V14, "color", zcolor[13]);
    ozstatus[13] = zstatus[13];
    ozbypass[13] = zbypass[13];
  }
  if (ozstatus[14] != zstatus[14] || ozbypass[14] != zbypass[14]) {
    zcolor[14] = colr(zstatus[14], zbypass[14]);
    stat = zstat(zstatus[14], zbypass[14]);
    Blynk.virtualWrite(V15, stat);
    Blynk.syncVirtual(V31);
    Blynk.setProperty(V15, "color", zcolor[14]);
    ozstatus[14] = zstatus[14];
    ozbypass[14] = zbypass[14];
  }
  if (ozstatus[15] != zstatus[15] || ozbypass[15] != zbypass[15]) {
    zcolor[15] = colr(zstatus[15], zbypass[15]);
    stat = zstat(zstatus[15], zbypass[15]);
    Blynk.virtualWrite(V16, stat);
    Blynk.syncVirtual(V32);
    Blynk.setProperty(V16, "color", zcolor[15]);
    ozstatus[15] = zstatus[15];
    ozbypass[15] = zbypass[15];
  }

  if (i != "" && b != 0)
  {
    if (b == 1)
    {
      if (i == m)
      {
        terminal.println("> Enter The New Pin:");
        terminal.flush();
        b = 2;
      }
      else
      {
        terminal.println("> Incorrect Pin. Please Retry !");
        terminal.flush();
        b == 0;
      }
      i = "";
    }
    if (b == 2 && i != "")
    {
      Blynk.virtualWrite(V100, i);
      terminal.println("> Pin Change Successful !");
      terminal.flush();
      Blynk.syncVirtual(V100);
      i = "";
      b = 0;
    }
    if (b == 3)
    {
      if (i == m)
      {
        w = 0;
        for (int z = 0; z <= 15; z++)
        {
          if (zbypass[z] == 0)
          {
            inlist[w] = z;
            w++;
          }
        }
        x = 0;
        for (int z = 0; z <= w; z++)
        {
          if (zstatus[inlist[z]] != 0)
          {
            x++;
          }
        }
        if (x == 0)
        {
          arm = 255;
          terminal.println("> System Armed !");
          terminal.flush();
        }
        else
        {
          terminal.println("> " + String(x) + " Included Zone(s) Open!");
          terminal.flush();
          inlist[15] = {};
        }
        b = 0;
        x = 0;
      }
      else
      {
        terminal.println("> System Not Armed !");
        terminal.flush();
      }
      i = "";
    }
    if (b == 4)
    {
      if (i == m)
      {
        arm = 0;
        w = 0;
        buzz = 0;
        digitalWrite(6, LOW);
        terminal.println("> System Disarmed !");
        terminal.flush();
        b = 0;
      }
      else
      {
        terminal.println("> System Still Armed !");
        terminal.flush();
      }
      i = "";
    }
  }
  else if (b == 0)
  {
    i = "";
  }


  if (cmd == "select") {
    switch (rowId)
    {
      case 0:
        {
          if (arm == 255)
          {
            terminal.println("> Please Disarm System And Try Again!");
            terminal.flush();
          }
          else
          {
            terminal.println("> Enter Existing Pin:");
            terminal.flush();
            b = 1;
          }
          break;
        }
      case 1:
        {
          if (arm == 0)
          {
            terminal.print("> Pin Please:");
            terminal.flush();
            b = 3;
          }
          else
          {
            terminal.print("> Pin Please:");
            terminal.flush();
            b = 4;
          }
          break;
        }
      case 2:
        {
          b = 0;
        }
    }
    cmd = "";
  }
  else
  {
    if (rowId == 2 && b == 0)
    {
      Blynk.virtualWrite(V37, "clr");
      for (int z = 0; z <= 15; z++)
      {
        Blynk.virtualWrite(V37, "add", z, zname[z], "z" + String(z + 1));
        delay(200);
      }
      b = 10;
    }
  }

  if (arm == 255)
  {
    for (int z = 0; z <= w; z++)
    {
      if (zstatus[inlist[z]] != 0)
      {
        buzz = 255;
        digitalWrite(6, HIGH);
      }
    }
  }

  Blynk.run();
  timer.run();
}

String colr(int stat, int bypas)
{
  String zcolor;
  if (stat == 0)
  {
    if (bypas == 0)
    {
      zcolor = Green;
    }
    else
    {
      zcolor = Orange;
    }
  }
  else
  {
    if (bypas == 0)
    {
      zcolor = Red;
    }
    else
    {
      zcolor = Orange;
    }
  }
  return zcolor;
}

int zstat(int stat, int bypas)
{
  int state;
  if (stat == 0)
  {
    state = 255;
  }
  else
  {
    if (bypas == 0)
    {
      state = 255;
    }
    else
    {
      state = 100;
    }
  }
  return state;
}

void push()
{
  Blynk.virtualWrite(V33, WiFi.RSSI());
  Blynk.virtualWrite(V0, arm);
  analogWrite(6, buzz);
}

