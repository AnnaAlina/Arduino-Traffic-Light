int stoplight1[]={7,8,11};          //creates array for stoplight 1
int stoplight2[]={A0,A1,A2};        //creates array for stoplight 2
int lightTimes[]={5,2,1};           //stoplight 1 light time array
int lightTimes2[]={5, 2, 1};        //stoplight 2 light time array
int crosswalk = 2;                  //declaring interrupt pin#
int Walktime = 8;                   //declaring walktime variable
bool button = false;                //boolean for when button is pushed
bool crossing = false;              //boolean to use for lcd display while pedestrian is crossing

void Walk();                        //making Walk function global


#include <LiquidCrystal.h>         //includes LiquidCrystal library

LiquidCrystal lcd(10,9,5,4,3,12);  //name object called lcd

void setup() {  
  digitalWrite(A2, HIGH);
  pinMode(crosswalk, INPUT_PULLUP);   //initializes the pedestrian button utilizing the interal resistor
  
  for(int i=0; i <3;i++){
    pinMode(stoplight1[i], OUTPUT);   //uses a for loop to set the LEDs of each stoplight array 
    pinMode(stoplight2[i], OUTPUT);       //to output mode
  }
  attachInterrupt(0, Walk, FALLING);  //interrupt that calls the Walk function
  lcd.begin(16,2);                    //initializes lcd with 16 columns and 2 rows
  lcd.clear();                        //clears lcd screen
}

void loop() {
   for(int i=0;i<3;i++){
    if(i==0){                             //when i is in the first position of the array
      digitalWrite(stoplight1[2], LOW);   //turn off the red1 led
    }
    digitalWrite(stoplight1[i], HIGH);    //runs through the first stoplight array turning each led on
    for(int x=0; x < lightTimes[i]; x++){   
      if (crossing){                      //when the pedestrian is crossing 
        lcd.clear();                      //clear lcd screen
        lcd.setCursor(0,0);               //set cursor to top left corner
        lcd.print("Walk");                //print walk
        lcd.setCursor(0,1);               //go to second row on the left
        lcd.print(Walktime);              //print the seconds countdown
        Walktime--;                       //subtract 1 from the walktime each second/loop
      }
      else if(!crossing){                 //while the person is not crossing
        lcd.clear();                      //clear lcd display
        lcd.setCursor(0,0);               //set cursor to top left
        lcd.print("Don't Walk!");         //prints don't walk
        }
      if(button){                         //if button is pressed
        break;                            //exits for loop
      }
      delay(1000);                        //waits 1 second
    }
    if(i!=2){                             //if it is not on the red led
      digitalWrite(stoplight1[i], LOW);   //turn that light off
    }else if(crossing){                   //if the pedestrian is crossing
      lcd.clear();                        //clear lcd
      crossing = false;                   //reset crossing to false afterwards
      lcd.setCursor(0,0);                 //sets cursor to top left
      lcd.print("Don't Walk!");           //prints don't walk
    }
  }
  for(int i=0;i<=2;i++){                  //for loop to count through three positions
    if(i==0){                             //if i is in the green2 position
      digitalWrite(stoplight2[2], LOW);   //turn red2 off
    }
    digitalWrite(stoplight2[i], HIGH);          //write i position HIGH
    for (int x = 0; x < lightTimes2[i]; x++){
      if(button && i != 1){                     //if button is pressed and i is not on yellow2
        continue;                               //continue this for loop
      }
      else if(button && i==1){                  //if button is pressed and it is on yellow
        button = false;                         //reset button to false
        crossing = true;                        //turn on pedestrian crossing
      }
      delay(1000);                        //waits a second
    }
    if(i!=2){                             //if i is not red
      digitalWrite(stoplight2[i], LOW);   //turn red off
    }
  }
}

void Walk(){        //Walk function
  button = true;    //sets button to true
  Walktime = 8;     //resets Walktime to 8
}


