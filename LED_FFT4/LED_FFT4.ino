/*
fft_adc_serial.pde
guest openmusiclabs.com 7.7.14
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256/2 // set to 256 point fft
//#define FFT_N 256

#include <FFT.h> // include the library

int start1 = 0;
//int start2 = 0;
int other = 0;
long start_time;
int maximum;
int index;
boolean start;
int oldADCSRA;

  
void setup() {
  Serial.begin(9600); // use the serial port
  //TIMSK0 = 0; // turn off timer0 for lower jitter
  //ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  pinMode(9, OUTPUT);  
}

void loop() {
    oldADCSRA = ADCSRA;
    ADCSRA = 0xe5;
    ADMUX = 0x40;
    while(start != 1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 256 ; i += 2) { // save 256 samples
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
    for (byte i = 0 ; i < FFT_N/2 ; i++) {
      //Serial.println("FFT " + String(i) + " " + String(fft_log_out[i]));
      //If the value of this bin number is greater than the current maximum, store the value in maximum and the bin number in index. 
      if (fft_log_out[i] > maximum) {
        maximum = fft_log_out[i];
        index = i;
      }

      if (i == 63) {  //Checks what the maximum bin number was at the last bin  
                       //(FFT_N/2 - 1)
        Serial.println("start_time " + String(index));  //Used for debugging by displaying max bin.  
        if (index == 2) {      //Increment start1
          start1++;
        }

        if (index != 2) {      //Increment start2
          other++;
        }

        /*if (start1 == 20){     //Too many bin 2's indicate a 585 Hz Signal. Reset Start2.
          start2 = 0;
        }

        if (start2 == 20) {    //Too many bin 3's indicate a 735 Hz Signal. Reset Start1.
          start1 = 0;          
        }*/
        
        if (start1 > 30)    //A balance of bin 4's and 5's indicate a 660 Hz Signal. Shine the LED.
        {
          Serial.println("working");
          start = 1;
        }

        if (index != 2 && index != 3) {   //Resets both incrementers
          start_time = 0;
          start1 = 0;
        }
        maximum = 0; //resets maximum checking at the end of the loop
        index = 0; //resets the index at which a maximum occurs at the end of 
                   //the loop
      }
    }
  }
  ADCSRA = oldADCSRA;
}
