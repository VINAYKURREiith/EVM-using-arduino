#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

// Push buttons
#define pb1 A0  // TDP
#define pb2 A1  // YCP
#define pb3 A2  // INC
#define pb4 A3  // OTH
#define pb5 A4  // Show Result
#define pb6 A5  // Clear Votes

int vote1 = 0, vote2 = 0, vote3 = 0, vote4 = 0;

void setup()
{
  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
  pinMode(pb3, INPUT);
  pinMode(pb4, INPUT);
  pinMode(pb5, INPUT);
  pinMode(pb6, INPUT);

  pinMode(12, OUTPUT); // Green LED
  pinMode(13, OUTPUT); // Red LED

  // Enable internal pull-up resistors
  digitalWrite(pb1, HIGH);
  digitalWrite(pb2, HIGH);
  digitalWrite(pb3, HIGH);
  digitalWrite(pb4, HIGH);
  digitalWrite(pb5, HIGH);
  digitalWrite(pb6, HIGH);

  lcd.begin(16, 2);
  lcd.print("  VOTING SYSTEM ");
  lcd.setCursor(0, 1);
  lcd.print(" Circuit Design ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Button to  ");
  lcd.setCursor(0, 1);
  lcd.print("Cast Your Vote   ");
}

void loop()
{
  if (digitalRead(pb1) == LOW)
  {
    vote1++;
    showConfirmation();
    while (digitalRead(pb1) == LOW);
  }

  if (digitalRead(pb2) == LOW)
  {
    vote2++;
    showConfirmation();
    while (digitalRead(pb2) == LOW);
  }

  if (digitalRead(pb3) == LOW)
  {
    vote3++;
    showConfirmation();
    while (digitalRead(pb3) == LOW);
  }

  if (digitalRead(pb4) == LOW)
  {
    vote4++;
    showConfirmation();
    while (digitalRead(pb4) == LOW);
  }

  if (digitalRead(pb5) == LOW)
  {
    showResults();
    while (digitalRead(pb5) == LOW);
    delay(1000);
  }

  if (digitalRead(pb6) == LOW)
  {
    vote1 = vote2 = vote3 = vote4 = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Votes Cleared...");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Button to  ");
    lcd.setCursor(0, 1);
    lcd.print("Cast Your Vote   ");
    while (digitalRead(pb6) == LOW);
  }
}

void showConfirmation()
{
  digitalWrite(12, HIGH); // Green LED
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vote Successful!");
  lcd.setCursor(0, 1);
  lcd.print("Thanks for Voting");
  delay(2000);
  digitalWrite(12, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Next Voter >>  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Button to  ");
  lcd.setCursor(0, 1);
  lcd.print("Cast Your Vote   ");
}

void showResults()
{
  digitalWrite(13, HIGH); // Red LED

  int votes[4] = { vote1, vote2, vote3, vote4 };
  const char *names[4] = { "TDP", "YCP", "INC", "OTH" }; // <-- Updated Party Names

  // Step 1: Find max vote
  int maxVote = 0;
  for (int i = 0; i < 4; i++)
    if (votes[i] > maxVote)
      maxVote = votes[i];

  // Step 2: Collect winners
  String winners = "";
  for (int i = 0; i < 4; i++)
    if (votes[i] == maxVote)
    {
      if (winners.length() > 0) winners += " & ";
      winners += names[i];
    }

  // Step 3: Mark winners
  bool isWinner[4] = { false, false, false, false };
  for (int i = 0; i < 4; i++)
    if (votes[i] == maxVote)
      isWinner[i] = true;

  // Step 4: Find second-highest vote
  int secondMax = 0;
  for (int i = 0; i < 4; i++)
    if (!isWinner[i] && votes[i] > secondMax)
      secondMax = votes[i];

  // Step 5: Collect second-place names
  String secondPlace = "";
  for (int i = 0; i < 4; i++)
    if (votes[i] == secondMax && !isWinner[i])
    {
      if (secondPlace.length() > 0) secondPlace += " & ";
      secondPlace += names[i];
    }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (maxVote == 0)
    lcd.print("No Votes Cast   ");
  else {
    lcd.print("Winner: ");
    lcd.print(winners);
  }

  lcd.setCursor(0, 1);
  if (secondPlace.length() == 0)
    lcd.print(" ");
  else {
    lcd.print("2nd: ");
    lcd.print(secondPlace);
  }

  delay(1000);
  digitalWrite(13, LOW);
}
