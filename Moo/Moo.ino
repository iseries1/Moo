// Moo game
// Back in 1975 I found this program
// It was written in BASIC at the time
// Reproduced here for your enjoyment
//

#include <Arduino.h>

// Butterfly
#define Green 38
#define Red 13
#define Blue 26


int num[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int ans[4];
int cows;
int bulls;
int guesses;
int guess;
int games;
float average;

void instructions()
{
  Serial.println("The microcontroller has picked a 4 digit code using the numbers 0 to 9");
  Serial.println("None of the numbers repeat in the combination");
  Serial.println("For each number you guess that is one of the numbers in the combination");
  Serial.println("you will get one cow.  For each number in the combination that is in the");
  Serial.println("correct position you will get one bull.");
  Serial.println("The object is to get 4 bulls in 7 tries or less!");
  Serial.println("You have a 1 in 5,000 chance of picking the right code in one try.");
}

void makecode()
{
  int x = random(10);
  for (int i=0;i<10;i++)
  {
    x = random(10);
    int s = num[i];
    num[i] = num[x];
    num[x] = s;
  }
//  for (int i=0;i<4;i++)
//    Serial.print(num[i]);
}

void get4()
{

  while (Serial.available() > 0)
    Serial.read();
  Serial.print("Enter 4 numbers: ");
  while (Serial.available() < 4);
  for (int i=0;i<4;i++)
    ans[i] = Serial.read() - '0';
}

void LED(int n)
{
  switch (n)
  {
    case 0: digitalWrite(Green, LOW);
            digitalWrite(Red, HIGH);
            digitalWrite(Blue, HIGH);
            break;
    case 1: digitalWrite(Green, HIGH);
            digitalWrite(Red, LOW);
            digitalWrite(Blue, HIGH);
            break;
    case 2: digitalWrite(Green, HIGH);
            digitalWrite(Red, HIGH);
            digitalWrite(Blue, LOW);
            break;
    default:digitalWrite(Green, HIGH);
            digitalWrite(Red, HIGH);
            digitalWrite(Blue, HIGH);
  }
}

void setup() {
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Blue, OUTPUT);

  delay(1000);
  
  makecode();
  Serial.begin(38400);
  int i = 0;
  while (Serial.available() == 0)
  {
    Serial.println("Press enter to begin");
    LED(i++);
    if (i > 2)
      i = 0;
    makecode();
    delay(500);
  }
  LED(3);
  Serial.println(" ");
  instructions();
  Serial.println(" ");
  guesses = 0;
  guess = 0;
  games = 0;
}

void loop() {
  bulls = 0;
  cows = 0;
  get4();
  guess++;
  Serial.print(" ");Serial.print(guess);Serial.print(") ");
  for (int i=0;i<4;i++)
  {
    Serial.print(ans[i]);
  }
  Serial.print(" ---> ");
  
  for (int i=0;i<4;i++)
  {
    for (int j=0;j<4;j++)
      if (ans[i] == num[j])
        if (i == j)
          bulls++;
        else
          cows++;
          
  }
  for (int i=0;i<bulls;i++)
    Serial.print("B");
  for (int i=0;i<cows;i++)
    Serial.print("C");
  if (bulls == 4)
  {
    Serial.print(" You got the code! ");
    games++;
    guesses = guesses + guess;
    average = (float)guesses / games;
    Serial.print("Games: ");Serial.print(games);Serial.print(" Average: ");Serial.println(average);
    Serial.print("<<<New code>>>");
    makecode();
    guess = 0;
  }
  Serial.println(" ");
}

