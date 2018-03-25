/*
Name:		The Supplemental Spinner (MSJC 2018)
Created:	1/5/2018 4:56:11 PM
Modified:	3/24/2018 (Version 3 Update: Fixed lower speed bug)
Author:	MINICOM SOFTWARE || Programmed by Steven Wilson (@SCMowns)
Description: Source file for the "The Supplemental Spinner" game. The code below can be used for educational purposes and has been documented for your
pleasure. Contact Steven (scmowns@yahoo.com) if there are any concerns. Please do not expect perfect code.

############### Useful References that I used: ################
https://www.arduino.cc/en/Reference/HomePage
https://www.arduino.cc/en/tutorial/potentiometer
Update 3 solution: http://forum.arduino.cc/index.php?topic=28177.0 (comment credit: Korman)

Plugin used for visual studios: https://marketplace.visualstudio.com/items?itemName=VisualMicro.ArduinoIDEforVisualStudio

*/

/*
Global variables for accessing throughout Arduino game (*Essential data for game to work properly)
*/

//array of PINS used for LED lights (Winning light = PIN 22, or defined below as variable winnerLight) 

int ledLights[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };

int currentLEDvalue;			//integer that stores selected LED while in game
int winnerLight = 22;			//Winning LED on board
int delaySpeed; 				//stores the speed the potentiometer reads using analogRead (user adjusts this in game)
int fanActivation = 13;			//FAN pin is on 13
int userButton = 7;				//user button is now on pin 7 (update 3)

void setup() {

	/*
	Assignment of the ledLights
	*/

	pinMode(ledLights[0], OUTPUT);
	pinMode(ledLights[1], OUTPUT);
	pinMode(ledLights[2], OUTPUT);
	pinMode(ledLights[3], OUTPUT);
	pinMode(ledLights[4], OUTPUT);
	pinMode(ledLights[5], OUTPUT);
	pinMode(ledLights[6], OUTPUT);
	pinMode(ledLights[7], OUTPUT);
	pinMode(ledLights[8], OUTPUT);
	pinMode(ledLights[9], OUTPUT);
	pinMode(ledLights[10], OUTPUT);
	pinMode(ledLights[11], OUTPUT);
	pinMode(ledLights[12], OUTPUT);
	pinMode(ledLights[13], OUTPUT);
	pinMode(ledLights[14], OUTPUT);
	pinMode(ledLights[15], OUTPUT);
	pinMode(fanActivation, OUTPUT);

	//update version 3 (next two lines):
	pinMode(userButton, INPUT);
	digitalWrite(userButton, HIGH);

	Serial.begin(9600);			//begin Arduino connection and usage after data is loaded above

	TurnOnAllLights();			//reveals to the player all of the LEDs before start.

								//LEDdebugger();			//Ideal location for debugging the LED lights. Comment out above function: TurnOnAllLights()

	PrepareGameSettings();	    //Enter game settings before the start of the game
}

/*#######				#######
#######	METHODS		#######
#######				#######
*/

/*
Method: LEDdebugger
Description: Checks all lights and blinks each as it cycles through the 'totalLED' count. Since there are 16
LED's I used 16 as a constant number. The debugger will cycle through each LED pin and display it's activation by printing
'ledLights[i]' (i = which count it is on) and turning on the LED on the board. After ten seconds the LED will light off and
the debugger has successfully shown that the LED works or not.

*/

void LEDdebugger() {
	int totalLED = 16;
	int count = 0;
	for (int i = 0; i < totalLED; i++) {
		Serial.print("ledLights[");
		Serial.print(count);
		Serial.println("]");
		count++;
		digitalWrite(ledLights[i], HIGH);
		delay(10000);
		digitalWrite(ledLights[i], LOW);
	}
	Serial.println("Finish");

}


/*
Method: PrepareGameSettings
Description: This method prepares the game by indicating with an LED that the power is on (the LED is green on the board),
and when it lights up the game can begin. The SI Leader can use the potentiometer to adjust
the speed of the game before starting. The speed is adjusted based on the potentiometer's value which gives this
program a new delay speed. So if the potentiometer reads 1000 that means the delay speed is one second.

*/
void PrepareGameSettings() {

	Serial.println("Launching game settings...");		//since no logger is being used, this Serial will be displayed if console is used

	int gameIsReadyGreenLight = 12;						//currentlyOnStatus = status of the power whether on or off
	digitalWrite(gameIsReadyGreenLight, HIGH);
	digitalWrite(fanActivation, HIGH);					//activate fan when greenlight is on

	getPotentiometerSpeed();							//read the user's desired speed option

}




/*
.:	LIGHT MODIFICATION METHODS	:.
Descriptions:

LightLED: Method for recieving the current LED that is being cycled and turnng it on. Recieves the current led and sets it
as 'ledToLight'. Returns NOTHING.

TurnOffLED: Method that does the opposite of 'LightLED', it simply turns off the given LED paseed through the argument. Returns: NOTHING

TurnOnAllLights: Method for turning every light on the board on.

TurnOffAllLights; Method for turning every light on the board off.

BlinkLight: Method for blinking the LED sent through the argument. Returns: NOTHING

winningAnimationOne, Two, Three: Different end game winning displays for the victor.

*/
void LightLED(int ledToLight) {
	digitalWrite(ledLights[ledToLight], HIGH);
}

void TurnOffLED(int ledToOff) {
	digitalWrite(ledLights[ledToOff], LOW);
}

void TurnOnAllLights() {
	for (int i = 0; i <= sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], HIGH);
	}
}

void TurnOffAllLights() {
	for (int i = 0; i <= sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], LOW);
	}
}

void TurnOffAllLightsSlowly() {
	for (int i = 0; i <= sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], LOW);
		delay(100);
	}

}

void BlinkLight() {
	digitalWrite(ledLights[currentLEDvalue], HIGH);
	delay(500);
	digitalWrite(ledLights[currentLEDvalue], LOW);
	delay(500);
}

void winningAnimationOne() {

	//First light show:
	for (int i = 1; i != 2; i++) {
		TurnOnAllLights();
		delay(500);
		TurnOffAllLights();
		delay(500);
	}

	//second light show:
	for (int i = 0; i < sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], HIGH);
		delay(50);
	}
	for (int i = sizeof(ledLights) / 2; i != -1; i--) {
		digitalWrite(ledLights[i], LOW);
		delay(50);
	}
	for (int i = sizeof(ledLights) / 2; i != -1; i--) {
		digitalWrite(ledLights[i], HIGH);
		delay(50);
	}
	for (int i = 0; i < sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], LOW);
		delay(50);
	}


	//third light show:
	int halfdown;
	int halfup;

	for (int k = 0; k < 2; k++) {
		halfdown = 9;
		halfup = 9;
		for (int i = 0; i <= 8; i++) {
			digitalWrite(ledLights[halfdown], HIGH);
			digitalWrite(ledLights[halfup], HIGH);
			delay(75);
			digitalWrite(ledLights[halfdown], LOW);
			digitalWrite(ledLights[halfup], LOW);

			if (halfdown == 3) {
				halfdown = 1;
			}
			else {
				halfdown--;
			}

			if (halfup == 16) {
				halfup = 0;
			}
			else {
				halfup++;
			}
		}
	}

	for (int i = 0; i <= 2; i++) {
		BlinkLight();				//Blink the light twice before ending winner results.
	}

}



void winningAnimationTwo() {
	//to draw a smile face on pins 35 (right eye) and 25 (left eye)
	LightLED(3);
	LightLED(13);
	for (int i = 5; i <= 11; i++) {	//lighting the smile

		LightLED(i);

	}


	for (int i = 0; i <= 2; i++) {
		BlinkLight();				//Blink the light twice before ending winner results.
	}

	delay(1000);

	LightLED(3);
	LightLED(13);
	delay(500);
	TurnOffLED(3); //this is the wink
	delay(500);
	LightLED(3);
	delay(200);

	TurnOffAllLightsSlowly();
}



void winningAnimationThree(int numoftimes, int startSpeed) {

	for (int i = 0; i <= 15; i += 2) {

		digitalWrite(ledLights[i], HIGH);
	}

	delay(startSpeed);
	for (int i = 0; i <= 15; i += 2) {

		digitalWrite(ledLights[i], LOW);
	}
	for (int i = 1; i <= 15; i += 2) {

		digitalWrite(ledLights[i], HIGH);
	}
	delay(startSpeed);
	for (int i = 1; i <= 15; i += 2) {

		digitalWrite(ledLights[i], LOW);
	}

	if (numoftimes == 0) {

		return;							//return after number of recursive loops finish 
	}

	if (startSpeed <= 250) {

		startSpeed = 1000;				//makes sure speed is adjust and not slow beyond a certain point

	}
	winningAnimationThree(numoftimes - 1, startSpeed / 2);

}
/*
Method: LoadGameResults
Description: Gather game results from the user's button press action. If the winnerLight is true
the user has won. If not the game blinks the losing light and then returns to PrepareGameSettings. This method always returns to PrepareGameSettings
to call on a random start for the next user.
*/

void LoadGameResults() {
	Serial.println("Load game results...");

	if (ledLights[currentLEDvalue] == winnerLight) {			//check whether the winning light was chosen or not
		digitalWrite(ledLights[currentLEDvalue], HIGH);
		delay(500);


		int winningAnimationSelector = random(0, 3);			//randomly displays up to 3 winning animations for the victor

		switch (winningAnimationSelector) {
		case 0:
			winningAnimationOne();
			break;
		case 1:
			winningAnimationTwo();
			break;
		case 2:
			winningAnimationThree(3, 500);
			TurnOffAllLights();
			for (int i = 0; i <= 2; i++) {
				BlinkLight();									//Blink the light twice before ending winner results.
			}
			break;
		default:
			winningAnimationTwo();
			break;

		}
	}
	else {
		for (int i = 0; i <= 2; i++) {
			BlinkLight();				//Blink the lost to indicate result.
		}
	}
}


/*
Method: getPotentiometerSpeed
Description: Gathers the speed indicated on the back of The Supplemental Spinner. If the Potentiometer reads values greater than 714 then the user requested
the device to turn off all the lights. There are 6 different fixed speeds available.
*/

void getPotentiometerSpeed() {

	int temp = analogRead(3);				//gather the speed from the Analog In section under A3

	//Serial.print("Current game speed: ");
	//Serial.println(temp);

	while (temp > 714) {					//leader requested for lights to be turned off

		temp = analogRead(3);				//gather input until value is no longer in the "OFF" state of the device
		TurnOffAllLights();
	}

	if (temp > 607) {
		//level one speed (The slowest):
		delaySpeed = 370;

	}
	else if (temp > 486) {
		//level 2
		delaySpeed = 188;

	}
	else if (temp > 343) {
		//level 3
		delaySpeed = 106;

	}
	else if (temp > 226) {
		//level 4
		delaySpeed = 55;

	}
	else if (temp > 90) {
		//level 5
		delaySpeed = 31;

	}
	else {
		//level 6 (The fastest)
		delaySpeed = 15;

	}
}

/*
Method: loop (default arduino infinite loop method)
Description: The game begins here once sent from method 'PrepareGameSettings'. The game will enter an infinate lopp tp wait
for the player's responce to start the game. The game then after activation will cycles through each LED with the value 'currentLEDvalue'.
currentLEDvalue is a random number created in method 'PrepareGameSettings'. The potentiometer can
still adjust the speed during the game for LIVE edits.  If the player presses the button, the game enters
the 'LoadGameResults' method to check which LED was selected.
*/
void loop() {
	/*
	#####				#####
	#####	Begin Game	#####
	#####				#####
	*/
	Serial.println("Starting game...");

	while (digitalRead(userButton) == 1) {		//this is to wait for user activation for the game to start.

		currentLEDvalue = random(0, 13);					//creating random number between 0 and 13 (13 total variables) for random start

	}

	digitalWrite(fanActivation, HIGH);

	delay(1000);	
	//delay for button to enter next function as 'OFF' because it can still record as being pressed
	while (digitalRead(userButton) == 1) {			//reads A0 in the analog pin section

		LightLED(currentLEDvalue);							//light the randomly selected LED/ light the increment LED

		delay(delaySpeed);									//sets the speed of the game

		TurnOffLED(currentLEDvalue);						//Turn off current LED before looping 
		currentLEDvalue++;									//increment to next LED on board

		if (currentLEDvalue == sizeof(ledLights) / 2) {		//Boundary to check if currentLEDvalue is going beyond the array's range
			currentLEDvalue = 0;
		}

		getPotentiometerSpeed();							//this call is to enable "live" speed updates - DISABLED as of version 3
	}

	/*
	#### End of game & results ####

	*/

	Serial.println("Ending game...");
	delay(200);												//delay for button to enter next function as 'OFF'
	LoadGameResults();										//gather results once button is pressed
	PrepareGameSettings();									//restart game
}