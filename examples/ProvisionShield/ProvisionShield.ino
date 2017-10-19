
byte written=0;
void setup() {
    Serial.begin(9600); // Serial output begin. Only needed for debug
    Serial1.begin(9600); // Serial output begin. Only needed for debug
    Serial.write("Write the number of the controller into the console above and hit enter.");
}

void dump(){
  int start = millis();
  
  while(Serial1.available()<=0){
    if((millis()-start)>5000){
      Serial.print("\r\nNO RESPONSE\r\n");
      return;
    }
    delay(1);
  }
  while(Serial1.available()>0){
      byte val=Serial1.read();
      if(val>8 && val< 127){
        written++;
        Serial.write(val);
      }
      delay(1);
  }
}

void write (String s){
  //written=0;
  Serial.print("\r\n");
  Serial.print(s);
  Serial.print("\r\n");
  Serial1.print(s);
}


void initializeContolMode(){
          /*
       * This section is a secret code: 
       * ~ 0x0  0x4  0x8  0x1 A  P  e
       * sent by XCTU to kick the module into AT mode
       * This needs to be sent before initating AT mode
       */
      Serial1.write('~');
      Serial1.write(0x4);
      Serial1.write(0x8);
      Serial1.write(0x1);
      Serial1.write('A');
      Serial1.write('P');
      Serial1.write('e');
      start();
      write("ATAP\r");
      dump();
      write("ATHV\r");
      dump();
      write("ATVR\r");
      dump();
      write("ATSH\r");
      dump();
      write("ATSL\r");
      dump();
      write("ATMY\r");
      dump();
      write("ATAC\r");
      dump();
      write("ATBD\r");
      dump();
      write("ATNB\r");
      dump();
      write("ATSB\r");
      dump();
      write("ATAP\r");
      dump();
      write("ATCN\r");
      dump();
}


void start(){

      delay(1500);
      Serial1.write("+++");
      Serial.write("+++");
      delay(1000);
      dump();
}

void end(){
      write("ATWR\r");
      dump();
      write("ATAC\r");
      dump();
      write("ATCN\r");
      dump();
}

void loop() {
  if(Serial.available()>1){
    String number = Serial.readString();
      Serial.write("\r\nProvisioning...");
      Serial.print(number);
      initializeContolMode();
     
      start();
      write("ATIDB");
      write(number);
      write("\r");
      dump();
      end();
      
      start();
      write("ATCE1\r");
      dump();
      end();

      //Close up connection

      if(written>1){
        Serial.write("\r\nDone!");
      }else{
          Serial.write("\r\nFailed!! module dead..");
        
      }
     
    }
  
  
}
