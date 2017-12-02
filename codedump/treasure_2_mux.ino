/*
fft_adc_serial.pde
guest openmusiclabs.com 7.7.14
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library

int start1 = 0;
int start2 = 0;
int start3 = 0;

int s1 = 10;
int s0 = 4;

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS2);
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
}

void loop(){
  
  //for (int q = 0; q < 3; q++){
  //    Serial.println(q);
  //    byte treasure = treasure_detect(q);//q);
  //}
  byte treasure = treasure_detect(1);
}

byte treasure_detect(int test ){
  int maximum = 0;
  int index = 0;
  byte i = 0;
  
  char TIMSK0_temp = TIMSK0;
  char ADCSRA_temp = ADCSRA;
  char ADMUX_temp = ADMUX;
  char DIDR0_temp = DIDR0;

  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS2);
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  
  byte treasure = 0;

  if ( test == 0 ){
    digitalWrite(s1, LOW);
    digitalWrite(s0, LOW);
    Serial.println("This is pin 0");
    delay(50000);
  }
  if ( test == 1 ){
    digitalWrite(s1, LOW);
    digitalWrite(s0, HIGH);
    Serial.println("This is pin 1");
    delay(50000);
  }
  if (test == 2 ){
    digitalWrite(s0, LOW);
    digitalWrite(s1, HIGH);
    Serial.println("This is pin 2");
    delay(50000);
  }
  
  
  while(1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
    
    for ( i = 0; i < FFT_N/2 ; i++) { 
      if (fft_log_out[i] > maximum ) {
        if (i > 5)
        {
          maximum = fft_log_out[i];
          Serial.print("This is i: ");
          Serial.println(String(i));
          Serial.println(String(maximum));
          index = i;
        }
      }

      if (i == 127) {  //last bin
        //Serial.println(String(index)); // send out the data
        if (index == 45 || index == 46 || index == 47) {      //7K
          start1++;
          if (start1 > 5) {
            digitalWrite(8, HIGH);
            delay (1000);
            treasure = B00000001;
            Serial.println("7k detected");
            digitalWrite(8, LOW); 
          }
        }

        else {
          start1 = 0;
        }

        if (index == 79 || index == 80 || index == 81) {      //12K
          start2++;
          if (start2 > 5) {
            Serial.println("12k detected");
            digitalWrite(9, HIGH);
            delay (1000);
            treasure = B00000010;
            digitalWrite(9, LOW); 
          }
        }

        else {
          start2 = 0;
        }

        if (index == 113 || index == 114 || index == 115) {      //17K
          start3++;
          if (start3 > 5) {
            Serial.println("17k detected");
            digitalWrite(10, HIGH);
            delay (1000);
            treasure = B00000011;
            digitalWrite(10, LOW);             
          }
        }

        else {
          start3 = 0;
        }
        
        maximum = 0; //resets maximum checking at the end of the loop
        index = 0; 
        //Serial.println(index);
      }
    }
    
  TIMSK0 = TIMSK0_temp;
  ADCSRA = ADCSRA_temp;
  ADMUX = ADMUX_temp;
  DIDR0 = DIDR0_temp;
  return treasure;
  }
//}
}


