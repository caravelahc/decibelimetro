const int buzzer = 10;
const int decibelimeter = 0;
const int MEMO = 100;

float volume_signal = 0;
float volume[MEMO];
float volume_sum = 0;
float volume_mean = 0;

int i = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(decibelimeter, INPUT);

  for(i=0;i<MEMO;i++){
    volume[i] = 0;
  }
}

float get_mean(){
  if (i >= MEMO-1){
    i = 0;
  } else {
    i++;
  }
  
  volume_sum -= volume[i];
  volume_signal = analogRead(decibelimeter); //*5/1024;
  volume[i] = volume_signal;
  volume_sum += volume[i];

  return volume_sum/MEMO;
}

void send_plotter_data(){
  Serial.print(volume_signal);
  Serial.print(",");
  Serial.println(volume_mean);
}

void reset_volume_memo() {
  int j;
  for (j = 0; j < MEMO; j++){
    volume[j] = 0;
  }
  volume_sum = 0;
}

void loop() {
  volume_mean = get_mean();
  
  send_plotter_data();

  if (volume_mean > 500) {
    tone(buzzer, 1500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    noTone(buzzer);
    delay(5000);
    reset_volume_memo();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    noTone(buzzer);
  }
}
