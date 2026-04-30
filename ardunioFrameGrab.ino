#define ALDL_PIN 2
char bitGrouping[9]; //grouping 9 bits for a byte, first bit is always 0, +8 of data bits
int bitGroupIndex = 0;

const unsigned long noiseWidths = 100; // noise filter
const int frameLengthBytes = 25; // byte lenght of one frame
byte frame[frameLengthBytes]; //frame array of frame length
int frameIndex = 0;
bool lockFF = false;
const unsigned long quietTimeBetween = 50000; // gap between messages
const unsigned long minReadableZero = 250;// short pulse = logic 0, 1 after invert
const unsigned long minReadableOne = 2500; // long pulse = logic 1, 0 after invert
const unsigned long bitTime = 6250; // one bit time (~160 baud)

// Wait for ALDL signal change or times out after one bit, handle long runs of same signal level
void waitForLineStateChange(int &currentState, unsigned long &changeTime) 
{
  int entryState = digitalRead(ALDL_PIN); //entry current signal level
  unsigned long entryTime = micros(); //time started watching for signal 

  while (true) 
  { //keeps checking reading

    int currentRead = digitalRead(ALDL_PIN); //keep checking digital read
    unsigned long current = micros();  //keep recording time

    // edge detected
    if (currentRead != entryState) //if not the same then found edge, signal coming in 
    {

      unsigned long detectedTime = micros();
      delayMicroseconds(noiseWidths); // filter noise

      if (digitalRead(ALDL_PIN) == currentRead) 
      {
        currentState = currentRead;
        changeTime = detectedTime;
        return;
      }
    }

    if ((current - entryTime) > bitTime)   // if no change within one bit time, force a edge
    // keeps bit timing consistent even if signal doesn't toggle
    {
      currentState= (entryState == HIGH)?LOW : HIGH;
      changeTime = micros();
      return;
    }
  }
}


byte groupToByte() // convert a 9-bit ALDL unit into an 8-bit byte, first bit is 0 always so ignore, use last 8
{ 
  byte value = 0;

  for (int i = 1; i < 9; i++) {
    value <<= 1;
    if (bitGrouping[i] == '1') value |= 1;
  }

  return value;
}


bool frameStartCheck() //check if current 9-bit group is all 1s, 111111111, or FF in hex. Tells start of frame
{
  for (int i = 0; i < 9; i++) {
    if (bitGrouping[i] != '1') return false;
  }
  return true;
}

void setup() 
{
  pinMode(ALDL_PIN, INPUT);
  Serial.begin(115200);
}




//loop continuously decode ALDL signal
void loop() {
  int prevState;
  unsigned long prevTime;
  int currentState;
  unsigned long currentTime;

  waitForLineStateChange(currentState, currentTime); // wait for first transition to start timing
  prevState = currentState;
  prevTime = currentTime;

  while (true) 
  {
    waitForLineStateChange(currentState, currentTime); // wait for next transition

    unsigned long interval = currentTime - prevTime;//pulse length calculation
    prevState = currentState;
    prevTime = currentTime;

    // reset on gap between frames
    if (currentState == LOW && interval > quietTimeBetween) 
    {
      lockFF = false;
      bitGroupIndex = 0;
      frameIndex = 0;
      continue;
    }

    if (currentState == HIGH) //when signal goes HIGH a LOW pulse just ended, LOW pulse length determines the bit value 
    {
      char bitChar;

      // invert because of the circuit we have
      if (interval >= minReadableOne)
      {
        bitChar = '0';
      } else if (interval >= minReadableZero) 
      {
        bitChar = '1';
      } else {
        continue;
      }

      bitGrouping[bitGroupIndex++] = bitChar;  //store bit in current 9-bit group

      if (bitGroupIndex == 9) // complete once have 9 bits
      {
        bitGroupIndex = 0; //reset index

        if (!lockFF) //look for lock if not locked on 111111111/ FF
        {
          if (frameStartCheck()) 
          {
            lockFF = true;
            frameIndex = 0;
          }
          continue;
        }

        byte byteHexiValue = groupToByte(); //convert group to byte and store in frame

        if (frameIndex < frameLengthBytes) 
        {
          frame[frameIndex++] = byteHexiValue; //store hexi value in frame
        }

        if (frameIndex >= frameLengthBytes) //if we have all values in frame
        {

          Serial.println(); 
          for (int i = 0; i < frameLengthBytes; i++)
          {
            if (frame[i] < 16) {
              Serial.print('0');
            }

            Serial.print(frame[i], HEX);
            Serial.print(' ');
          }
          Serial.println();

          frameIndex = 0;
          lockFF = false; // wait for next 111111111 / FF
        }
      }
    }
  }
}