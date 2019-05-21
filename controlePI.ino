const int pwmPin = 10;
const int analogPin = 0;
const int MEMO = 20;

float volume[MEMO];
float volume_sum = 0;
float volume_mean = 0;

int i = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);
  pinMode(analogPin, INPUT);

  for(i=0;i<MEMO;i++){
    volume[i] = 0;
  }
}

void get_mean(){
  if (i >= MEMO-1){
    i = 0;
  } else {
    i++;
  }
  
  volume_sum -= volume[i];
  volume[i] = analogRead(analogPin)*5/1024;
  volume_sum += volume[i];

  return volume_sum/MEMO;
}

void send_serial_data(){
  // Serial.print(v);
  // Serial.print(",");
  Serial.println(volume_mean);
}

void loop() {
  volume_mean = get_mean();
  
  send_serial_data();

  analogWrite(pwmPin,v*256/5);
}
