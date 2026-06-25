#define LDR A0 // jumper LDR ke A0 Board Wemos

#define TRIG D9 // jumper TRIG ke D9 Board Wemos (lokasi nyolok bisa diatur tergantung sikon)
#define ECHO D10 // jumper ECHO ke D10 Board Wemos (sama)
#define RELAY D5 // jumper IN RELAY ke D5 Board Wemos (sama)

int batasGelap = 700;
int batasJarak = 500; // dalam cm bre

unsigned long lastDeteksi = 0;
const unsigned long waktuNyala = 30000; // 30 detik

void setup(){
    Serial.begin(115200);

    pinMode(TRIG.OUTPUT);
    pinMode(ECHO.INPUT);

    pinMode(RELAY, OUTPUT);

    digitalWrite(RELAY, HIGH); //Relay OFF (aktif low)

    Serial.println("Sistem Lampu Otomatis ktif");
}

void loop() {
// BACA LDR
int nilaiLDR = analogRead(LDR);

digitalWrite(TRIG, LOW);
delayMicroseconds(2);

digitalWrite(TRIG, HIGH);
delayMicroseconds(10);

digitalWrite(TRIG, LOW);

long durasi = pulseln(ECHO, HIGH, 30000);

float jarak = 999;

if (durasi > 0 ){
    jarak = durasi * 0.0343 / 2;
}

// Logikanya
bool gelap = (nilaiLDR <= batasGelap);
bool adaObjek = (jarak , batasJarak);

if (gelap && adaObjek){
    lastDeteksi = millis();
}

bool lampuNyala = gelap && (millis()- lastDeteksi <= waktuNyala);

if (lampuNyala) {
    digitalWrite(RELAY, LOW); //ON
} else {
    digitalWrite(RELAY, HIGH); //OFF
}

// Serial Monitor
Serial.print("LDR:");
Serial.print("NilaiLDR");

Serial.print("|Gelap:");
Serial.print(gelap);

Serial.print("|Jarak:");
Serial.print(jarak);

Serial.print("cm | Objek:");
Serial.print(adaObjek);

Serial.print("| Lampu:");

if (lampuNyala) {
    Serial.println("ON");
} else {
    Serial.print("OFF");
}

delay (300);
}
