#include <SPI.h>
#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>

// Ethernet設定
byte mac[] = { 0x02, 0xA2, 0x73, 0x10, 0x00, 0x00 }; // TeensyのMACアドレス
IPAddress ip(192, 168, 31, 100);                     // TeensyのIPアドレス
IPAddress snmpServer(192, 168, 31, 188);               // SNMPサーバーのIPアドレス
const int snmpPort = 161;                           // SNMPポート (通常161)

// SNMP設定
const char* community = "private"; // SNMPコミュニティ名 (v1用)
const char* oid =  "\x2b\x06\x01\x02\x01\x01\x05\x00"; // 設定するOID (例: sysName.0)
const char* value = "Teensy_SNMP";     // 設定する値

EthernetUDP udp;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("SNMP Set Example for Teensy 4.1");

  // Ethernet初期化
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip); // DHCP失敗時に静的IPを設定
  }

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  // UDP/SNMPの初期化
  udp.begin(snmpPort);
}

void sendSnmpSet() {
  byte packet[1024]; // SNMPパケットを格納する配列
  int packetSize = 0;

  // SNMPメッセージを構築
  packet[packetSize++] = 0x30;                          // Sequence
  packet[packetSize++] = 0;                            // Length (後で計算)

  packet[packetSize++] = 0x02;                          // Integer (Version)
  packet[packetSize++] = 0x01;
  packet[packetSize++] = 0x00;                          // SNMP v1

  packet[packetSize++] = 0x04;                          // Octet String (Community)
  packet[packetSize++] = strlen(community);            // Community名の長さ
  memcpy(&packet[packetSize], community, strlen(community));
  packetSize += strlen(community);

  packet[packetSize++] = 0xA3;                          // SNMP SET Request
  packet[packetSize++] = 0;                            // Length (後で計算)

  packet[packetSize++] = 0x02;                          // Integer (Request ID)
  packet[packetSize++] = 0x01;
  packet[packetSize++] = 0x01;

  packet[packetSize++] = 0x02;                          // Integer (Error Status)
  packet[packetSize++] = 0x01;
  packet[packetSize++] = 0x00;

  packet[packetSize++] = 0x02;                          // Integer (Error Index)
  packet[packetSize++] = 0x01;
  packet[packetSize++] = 0x00;

  packet[packetSize++] = 0x30;                          // Sequence (Varbind List)
  packet[packetSize++] = 0;                            // Length (後で計算)

  packet[packetSize++] = 0x30;                          // Sequence (Varbind)
  packet[packetSize++] = 0;                            // Length (後で計算)

  packet[packetSize++] = 0x06;                          // Object Identifier
  packet[packetSize++] = strlen(oid);                  // OIDの長さ
  memcpy(&packet[packetSize], oid, strlen(oid));
  packetSize += strlen(oid);

  packet[packetSize++] = 0x04;                          // Octet String (Value)
  packet[packetSize++] = strlen(value);                // 値の長さ
  memcpy(&packet[packetSize], value, strlen(value));
  packetSize += strlen(value);

  // Varbindの長さを更新
  packet[29] = packetSize - 30;

  // Varbind Listの長さを更新
  packet[27] = packetSize - 28;

  // SNMP SET Requestの長さを更新
  packet[15] = packetSize - 16;

  // 全体の長さを更新
  packet[1] = packetSize - 2;

  // パケットを送信
  udp.beginPacket(snmpServer, snmpPort);
  udp.write(packet, packetSize);
  udp.endPacket();

  Serial.println("SNMP SET request sent!");
}


void loop() {
    sendSnmpSet();
    // 5秒待機
    delay(5000);
}
