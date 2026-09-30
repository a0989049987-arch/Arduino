const int buttonPin = 2;  // 按鈕腳位
const int RledPin   = 3;  // R 腳位
const int GledPin   = 4;  // G 腳位
const int BledPin   = 5;  // B 腳位

// ---------- 變數 ----------
int buttonState = 0;          // 讀取按鈕狀態
int ledState = LOW;           // 閃爍狀態(LOW = 亮, HIGH = 滅)
int ledcolor    = 0;          // 目前顏色編號 (0~8)
bool ButtonPressed = false;   // 按鈕是否已被按下(避免按住連續切換)
String currentcolor = "led";  // 目前顏色名稱(顯示用)
unsigned long previousMillis = 0;  // 上次切換閃爍狀態的時間
const long interval = 1000;        // 閃爍間隔(毫秒)

void setup() {
  // 將 LED 腳位設為輸出
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  // 將按鈕腳位設為輸入(按下為 LOW,使用內建上拉電阻)
  pinMode(buttonPin, INPUT_PULLUP);

  // 序列埠鮑率設定
  Serial.begin(9600);
}

void loop() {
  // 讀取按鈕狀態
  buttonState = digitalRead(buttonPin);

  // 顯示目前顏色
  Serial.print("Current Color: ");
  Serial.println(currentcolor);

  // 剛按下(且之前是放開狀態)-> 切換到下一個顏色
  if (buttonState == LOW && !ButtonPressed) {
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
    delay(50);  // 按下防彈跳
  }

  // 放開按鈕 -> 重設旗標
  if (buttonState == HIGH && ButtonPressed) {
    ButtonPressed = false;
    delay(50);  // 放開防彈跳
  }

  // 每隔 interval 毫秒,切換一次閃爍狀態
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }

  // 依照 ledcolor 與 ledState 決定 LED 顏色與是否亮燈
  if (ledcolor == 0) {
    // 全滅
    currentcolor = "LED off";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1) {
    // RED 紅
    currentcolor = "Red";
    if (ledState == LOW) {
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 2) {
    // GREEN 綠
    currentcolor = "Green";
    if (ledState == LOW) {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 3) {
    // BLUE 藍
    currentcolor = "Blue";
    if (ledState == LOW) {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, LOW);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 4) {
    // YELLOW 黃(紅 + 綠)
    currentcolor = "Yellow";
    if (ledState == LOW) {
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 5) {
    // PURPLE 紫(紅 + 藍)
    currentcolor = "Purple";
    if (ledState == LOW) {
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, LOW);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 6) {
    // CYAN 青(綠 + 藍)
    currentcolor = "Cyan";
    if (ledState == LOW) {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, LOW);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 7) {
    // WHITE 白(紅 + 綠 + 藍)
    currentcolor = "White";
    if (ledState == LOW) {
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, LOW);
    } else {
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    }
  }
  else if (ledcolor == 8) {
    // 回到起點,重新循環
    ledcolor = 0;
  }
}
