const int BUZZER = 8;
const int DECIBELIMETER = 0;
const int MEMORY = 250;
const int DIF_MEMO = 50;

float volume_array[MEMORY];
float volume_dif_array[DIF_MEMO];
float volume_dif_sum = 0;
float volume_sum = 0;

int dif_index;
int index;
  
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DECIBELIMETER, INPUT);

  for(dif_index=0;dif_index<DIF_MEMO;dif_index++){
    volume_dif_array[dif_index] = 0;
  }
  for(index=0;index<MEMORY;index++){
    volume_array[index] = 0;
  }
}

float get_dif_mean(float volume_mean){
  if (dif_index < DIF_MEMO-1){
    dif_index++;
  } else {
    dif_index = 0;
  }
  
  volume_dif_sum -= volume_dif_array[dif_index];
  volume_dif_array[dif_index] = analogRead(DECIBELIMETER) - volume_mean;
  if (volume_dif_array[dif_index] < 0) {
    volume_dif_array[dif_index] = -volume_dif_array[dif_index];
  }
  volume_dif_sum += volume_dif_array[dif_index];

  return volume_dif_sum/DIF_MEMO;
}

float get_mean() {
  if (index < MEMORY-1){
    index++;
  } else {
    index = 0;
  }
  
  volume_sum -= volume_array[index];
  volume_array[index] = analogRead(DECIBELIMETER);
  volume_sum += volume_array[index];

  return volume_sum/MEMORY;
}

void send_plotter_data(float volume_dif_mean, float volume_mean){
  Serial.print(analogRead(DECIBELIMETER));
  Serial.print(",");
  Serial.print(volume_dif_mean);
  Serial.print(",");
  Serial.println(volume_mean);
}

void reset_memory() {
  int i;
  volume_sum = 0;
  volume_dif_sum = 0;
  for (i = 0; i < MEMORY; i++){
    volume_array[i] = analogRead(DECIBELIMETER);
    volume_sum += volume_array[i];
    if (i >= MEMORY - DIF_MEMO) {
      volume_dif_array[i - (MEMORY - DIF_MEMO)] = 0;
    }
  }
  volume_dif_sum += 0;
}

void loop() {
  float volume_mean = get_mean();
  float volume_dif_mean = get_dif_mean(volume_mean);
  
  send_plotter_data(volume_dif_mean, volume_mean);

  if (volume_dif_mean > 50) {
    tone(BUZZER, 1500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    noTone(BUZZER);
    delay(5000);
    reset_memory();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    noTone(BUZZER);
  }
}
