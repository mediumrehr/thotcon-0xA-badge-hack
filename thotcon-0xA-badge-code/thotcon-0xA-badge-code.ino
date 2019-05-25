#include "SoundData.h";
#include "XT_DAC_Audio.h";

XT_DAC_Audio_Class DacAudio(26,0); 

XT_Wav_Class soundHackit(hackit_sound);
XT_Wav_Class soundCrackit(crackit_sound);
XT_Wav_Class soundThotit(thotit_sound);
XT_Wav_Class soundAttackit(attackit_sound);

int threshold = 40;
bool touchSelect = false;

void gotTouch5() {
 touchSelect = true;
}

int score = 0;
bool started = false;
int command = 0;
int gameSpeed = 1000;
int nextCommand = 0;

void blinkLEDs();

void setup() {
  Serial.begin(115200);
  while (!Serial) ;

  Serial.println("THOT IT");
  
  touchAttachInterrupt(T2, gotTouch5, threshold);

  pinMode(13, INPUT); //T4
  pinMode(14, INPUT); //T6
  pinMode(15, INPUT); //T3
  pinMode(27, INPUT); //T7
  
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);

  score = 0;
  started = false;
  command = 0;
  nextCommand = 0;

  blinkLEDs();
}

void loop() {
  DacAudio.FillBuffer();
  if (started) {
    if (!command) {
      digitalWrite(16, LOW); // right eye
      digitalWrite(17, LOW); // right ear
      digitalWrite(18, LOW); // left stache
      digitalWrite(19, LOW); // left eye
      digitalWrite(21, LOW); // left ear
      digitalWrite(5, LOW); // right stache

      delay(gameSpeed);
      
      command = random(4) + 1;
      // 1: forward
      // 2: left
      // 3: backward
      // 4: right
      switch(command) {
        case 1:
          digitalWrite(18, HIGH);
          digitalWrite(5, HIGH);
          DacAudio.Play(&soundHackit);
          break;

        case 2:
          digitalWrite(21, HIGH);
          DacAudio.Play(&soundCrackit);
          break;

        case 3:
          digitalWrite(16, HIGH);
          digitalWrite(19, HIGH);
          DacAudio.Play(&soundThotit);
          break;

        case 4:
          digitalWrite(17, HIGH);
          DacAudio.Play(&soundAttackit);
          break;

        default:
          break;
      }

      nextCommand = millis() + gameSpeed;
    }
    
    bool correct = false;
    bool wrong = false;

    int currTime = millis();
    if (currTime > nextCommand) {
      wrong = true;
    }
  
    // back
    if (digitalRead(13)) {
      if (command == 1) {
        correct = true;
      } else {
        wrong = true;
      }
    }
  
    // left
    if (digitalRead(14)) {
      if (command == 2) {
        correct = true;
      } else {
        wrong = true;
      }
    }
  
  
    // front
    if (digitalRead(15)) {
      if (command == 3) {
        correct = true;
      } else {
        wrong = true;
      }
    }
  
    // right
    if (digitalRead(27)) {
      if (command == 4) {
        correct = true;
      } else {
        wrong = true;
      }
    }

    if (correct) {
      score++;
      command = 0;
      if (!(score % 2)) {
        gameSpeed -= 50;
      }
    }

    if (wrong) {
      Serial.print("score: ");
      Serial.println(score);
      blinkLEDs();
      score = 0;
      command = 0;
      started = false;
      touchSelect = false;
      gameSpeed = 1000;
    }
  } else {
    if (touchSelect) {
      touchSelect = false;
      
      delay(200);

      started = true;
    }
  }
}

void blinkLEDs() {
  digitalWrite(16, HIGH); // right eye
  digitalWrite(17, HIGH); // right ear
  digitalWrite(18, HIGH); // left stache
  digitalWrite(19, HIGH); // left eye
  digitalWrite(21, HIGH); // left ear
  digitalWrite(5, HIGH); // right stache
  delay(200);
  digitalWrite(16, LOW); // right eye
  digitalWrite(17, LOW); // right ear
  digitalWrite(18, LOW); // left stache
  digitalWrite(19, LOW); // left eye
  digitalWrite(21, LOW); // left ear
  digitalWrite(5, LOW); // right stache
  delay(200);
  digitalWrite(16, HIGH); // right eye
  digitalWrite(17, HIGH); // right ear
  digitalWrite(18, HIGH); // left stache
  digitalWrite(19, HIGH); // left eye
  digitalWrite(21, HIGH); // left ear
  digitalWrite(5, HIGH); // right stache
  delay(200);
  digitalWrite(16, LOW); // right eye
  digitalWrite(17, LOW); // right ear
  digitalWrite(18, LOW); // left stache
  digitalWrite(19, LOW); // left eye
  digitalWrite(21, LOW); // left ear
  digitalWrite(5, LOW); // right stache
  delay(200);
  digitalWrite(16, HIGH); // right eye
  digitalWrite(17, HIGH); // right ear
  digitalWrite(18, HIGH); // left stache
  digitalWrite(19, HIGH); // left eye
  digitalWrite(21, HIGH); // left ear
  digitalWrite(5, HIGH); // right stache
  delay(200);
  digitalWrite(16, LOW); // right eye
  digitalWrite(17, LOW); // right ear
  digitalWrite(18, LOW); // left stache
  digitalWrite(19, LOW); // left eye
  digitalWrite(21, LOW); // left ear
  digitalWrite(5, LOW); // right stache

  return;
}

