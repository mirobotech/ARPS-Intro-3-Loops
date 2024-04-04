 /*
 Project: Intro-3-Loops                 Activity: mirobo.tech/arps-intro-3
 Date:    April 3, 2024
 
 This introductory programming activity for the mirobo.tech ARPS circuit
 demonstrates the use of both while-loop and for-loop structures to change
 the brightness of an LED using PWM (Pulse-Width Modulation).
 
 Additional program analysis and programming activities introduce the
 concepts of local and global variables and demonstrate the analogWrite()
 function to generate PWM output.

  See the https://mirobo.tech/arps website for more programming activities.
*/

// Define I/O pins used by ARPS human interface devices
const int SW2 = 0;      // Pushbuttons SW2 and SW3 are supported on Arduino
const int SW3 = 1;      // UNO R4 Minima and Arduino UNO R4 WiFi
const int SW4 = 2;      // Pushbuttons SW4 and SW5 work on all Arduino UNO R3
const int SW5 = 3;      // and Arduino UNO R4 circuit boards

const int LED2 = 5;     // ARPS LEDs
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;

const int BEEPER = 11;  // ARPS Piezo beeper LS1

// Define program variables
int SW2State;
int SW3State;
int SW4State;
int SW5State;

int LED2Level = 127;  // LED2 brightness (PWM on-time) value
int pwmCounter;       // Counter for PWM generation loop

void setup() {
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BEEPER,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  tone(BEEPER,4000,100);  // Say hello!
}

void loop() {
  // Read pushbuttons
  SW4State = digitalRead(SW4);
  SW5State = digitalRead(SW5);

  // Decrease brightness
  if(SW5State == LOW && LED2Level > 0) {
    LED2Level -= 1;
  }

  // Increase brightness
  if(SW4State == LOW && LED2Level < 255) {
    LED2Level += 1;
  }

  // PWM LED2
  pwmCounter = 255;
  while(pwmCounter != 0) {
    if(LED2Level == pwmCounter) {
      digitalWrite(LED2,HIGH);
    }
    pwmCounter --;
    delayMicroseconds(10);
  }
  digitalWrite(LED2,LOW);
}

/* Learn More -- Program Analysis Activities
 * 
 * 1.   The main loop of this program starts with program statements that
 *      read two of the circuit's pushbuttons and conditionally modify the
 *      value of the LED2Level variable. What range of values do they
 *      allow the LED2Level variable to be?
 * 
 * 2.   The main loop() of this program can be considered to be an infinite,
 *      (condition-less) loop. The while() loop inside the program's main
 *      loop implements a condition and acts as a finite loop.
 * 
 *      What condition is being evaluated inside the while() statement's
 *      brackets? How many times will the contents of this inner loop run?
 * 
 * 3.   There is an 'if' condition inside the while loop. What condition is
 *      being evaluated by this 'if' condition? What will happen if the
 *      condition is true?
 * 
 * 4.   Pressing buttons SW4 and SW5 will change the brightness of LED D2 by
 *      turning it on and off for different relative lengths of time using a
 *      technique known as PWM (Pulse-Width Modulation).
 *
 *      How many levels of brightness can LED D2 have in this program?
 *      Calculate the percentage brightness change corresponding to a single
 *      digit difference in the value of the LED2Level variable.
 * 
 * 5.   A while() loop requires three statements to perform its function:
 * 
 *      1) An assignment statement sets the starting state. In this program,
 *      the statement 'pwmCounter = 255;' sets the starting value of the 
 *      pwmCounter variable.
 * 
 *      2) A condition statement determines whether or not the contents of
 *      the loop will repeat. The 'while(pwmCounter != 0)' structure keeps 
 *      running the loop until pwmCounter is equal to 0. Unlike 'if'
 *      statements, which run the code inside their conditional braces only
 *      once when a condition is true, while statements keep re-evaluating
 *      their conditions and repeating the code inside their braces while
 *      their conditions are true.
 * 
 *      3) An expression is required to modify the variable inside the while()
 *      condition. If the variable is never modified, the program will appear
 *      to get stuck in the loop and will never go on to run any other code –
 *      this is known as an infinite loop. The statement 'pwmCounter --;' uses
 *      a decrement operator to decrease the value of the loop variable by 1. 
 *
 *      A for() loop is an alternative to a while() loop and incorporates the
 *      same three parts of a while structure into a single program statement.
 *      Compare the structure of the while() loop in the program with the 
 *      for() loop, below. What is an advantage of using a for() loop instead 
 *      of a while() loop? 
 *    
 *      Replace the entire while structure in the program with this for() loop:

  for(int pwmCounter = 255; pwmCounter != 0; pwmCounter --) {
    if(LED2Level == pwmCounter) {
      digitalWrite(LED2,HIGH);
    }
    delayMicroseconds(10);
  }
  digitalWrite(LED2,LOW);
        
 *      Compile the program and upload it into your circuit to try it out. Does
 *      it work the same way as the program did when using the while() loop?
 * 
 * 6.   The pwmCounter variable defined in the program's header is known as a 
 *      'global' variable because it is available to all parts of the program.
 *      The for() loop which was added above redefines the pwmCounter variable
 *      as a 'local' variable just for use within the for() loop using the 
 *      initialization statement: 'for(int pwmCounter = 255; ...'
 * 
 *      While both pwmCounter variables share the same name, they are different,
 *      and the contents of the second variable won't be accessible outside of
 *      the for() loop. As you can imagine, having two different variables with
 *      the same variable name can potentially lead to unexpected problems in 
 *      your program and should always be avoided – we're only doing it here to
 *      prove the point that it can be a problem! Let's try to prove that the
 *      two pwmCounter variable really are different.
 * 
 *      Add the line:

  pwmCounter = 128;

 *      above the for() loop in your program, and add the following lines below
 *      the for() loop to determine if the global pwmCounter variable is 
 *      modified by the for() loop:
        
  if(pwmCounter == 128) {
    digitalWrite(LED4,HIGH);
  }
  else {
    digitalWrite(LED4,LOW);
  }
        
 *      What value should pwmCounter variable that was declared inside the
 *      for() loop have when the loop finishes? Build and upload the program
 *      into your circuit. If LED4 is lit, we know that the global pwmCounter
 *      variable has not been modified by the for() loop. Do you think your
 *      prediction for the value of the local pwmCounter variable is correct?
 * 
 * 7.   Remove the 'int' declaration from the for() loop statement so that it
 *      now looks like this:

   for(pwmCounter = 255; pwmCounter != 0; pwmCounter --) {

 *      Build and upload the program to your circuit and run it again. What
 *      do you think the value of the pwmCounter variable is when the for()
 *      loop finishes now? How can you know?
 *
 * 8.   Sometimes, a better solution for programs like this is to use a
 *      dedicated local variable inside the for() loop, and doing so always
 *      requires the variable to be initialized with the 'int' type 
 *      specifier as shown below:

   for(int pwmCtr = 255; pwmCtr != 0; pwmCtr --) {
    if(LED2Level == pwmCtr) {
      digitalWrite(LED2,HIGH);
    }
    delayMicroseconds(20);
  }
  digitalWrite(LED2,LOW);

 *      Replace the for() loop code in your program with this new code and
 *      test it to ensure that it works. This creates a new local variable
 *      just for use inside the for() loop. 
 *
 *      Next, remove the 'int' type specifier from in front of the pwmCtr
 *      variable declaration in the for() statement. Try to build and upload
 *      the program. What happens? Why?
 *
 * 9.   Arduino includes an analogWrite() instruction that automatically
 *      generates PWM outputs on up to six special purpose digital output
 *      pins – these are usually marked with a tilde '~' character on each
 *      PWM-capable Arduino I/O header pin (the '~' is meant to represent
 *      an analog wave). The inclusion of this instruction means that all
 *      of the previous PWM code can be replaced with a single analogWrite()
 *      statement. Replace all of the code below the switch input if
 *      conditions with these three lines:

   // PWM LED2
  analogWrite(LED2,LED2Level);
  delay(10);

 *      What purpose does the 'delay(10);' statement serve in this program? 
 *      What happens if you comment the 'delay(10);' statement out?
 *
 * 10.  All of the work that went into generating and testing our own PWM
 *      algorithm might seem like wasted effort after realizing that that
 *      a single instruction can replace all of our code, but that doesn't
 *      have to be the case. Developing and testing an new algrithm to 
 *      accomplish a specific task is an important skill, and this exercise
 *      will hopefully build your understanding of PWM and provide good
 *      preparation for creating your own functions for new or un-supported
 *      hardware devices. Our code may even work more efficiently than 
 *      pre-made functions, which often contain extra code to support
 *      additional features or capabilities that may not be needed by our
 *      program.
 *
 *      Look up the analogWrite() instruction in the Arduino reference
 *      documentation. What limitiations does analogWrite() have? Can you
 *      think of any applications that might benefit from different PWM
 *      frequencies, different PWM resolution (the number of distinct
 *      output levels), or more PWM outputs? Could our PWM code algorithm
 *      be modified to overcome some of the limitations when using the
 *      analogWrite() function?
 *
 * Programming Activities
 * 
 * 1.   Modify your program to control the brightness of two or more LEDs
 *      simultaneously. On an Arduino UNO R4, use SW2 and SW5 to increase and
 *      decrease the brightness of one LED while using SW3 and SW4 to control
 *      the brightness of a second LED.
 *
 *      On Arduino UNO R3, use SW4 to set the brightness of one LED and SW5 to
 *      set the brightness of a second LED.
 *
 * 2.   If you have access to an oscillscope, you can use it to view the PWM
 *      output waveform being sent to LED2. Measure the time period of the PWM
 *      wave and calculate the PWM frequency.
 * 
 * 3.   Instead of having an LED turn on at full brightness when a button is
 *      pressed, create a program that uses a for() loop to automatically
 *      increase an LED's brightness when a button is pressed one (instead of
 *      having to hold the up button as in the original program). In addition
 *      to gradually changing light level this program could be used to
 *      implement a soft-start capability for an electric motor, to order to
 *      prevent or reduce the stress caused by suddenly applying full power
 *      to a mechanical system.
 *
 * 4.   Either add a second button to the soft-start program, above, to
 *      gradually turn the LED off by automatically decreasing its output
 *      level (or use the same start button as a toggle button).
 *
 * 5.   Make a program that automatically creates a repeated, visual 'pulse',
 *      by continuously brightening and dimming one or more of the LEDs.
 * 
 * 6.   Try making a 'chirp' or 'pew-pew' sound effect by using a for loop to
 *      sweep through a range of frequencies from low to high, or high to low,
 *      in response to a button press.
 */
