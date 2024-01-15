 /*
 Project: Intro-3-Loops                 Activity: mirobo.tech/arps-intro-3
 Date:    January 12, 2024
 
 This introductory programming activity for the mirobo.tech ARPS circuit
 demonstrates the use of both while-loop and for-loop structures to change
 the brightness of an LED using PWM (Pulse-Width Modulation).
 
 Additional program analysis and programming activities introduce the concepts
 of local and global variables and demonstrate the analogWrite() function to
 generate PWM output.
*/

// Define I/O pins used for human interface devices
const int SW2 = 0;      // ARPS pushbuttons SW2 and SW3 are supported on
const int SW3 = 1;      // Arduino UNO R4 Minima and Arduino UNO R4 WiFi
const int SW4 = 2;      // ARPS pushbuttons SW4 and SW5 work on all
const int SW5 = 3;      // Arduino UNO R3 and Arduino UNO R4 circuit boards

const int LED2 = 5;     // ARPS top-side LEDs
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;

const int BEEPER = 11;  // ARPS Piezo beeper LS1
const int onboardLED = 13;  // Arduino on-board LED

// Define program variables
int SW2state;
int SW3state;
int SW4state;
int SW5state;

int LED2level = 127;  // LED2 brightness (PWM on-time) value
int pwmCounter;       // Counter for PWM generation loop

void setup() {
  pinMode(onboardLED,OUTPUT);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BEEPER,OUTPUT);
  tone(BEEPER,4000,100);  // Say hello!
}

void loop() {
  // Read pushbuttons
  SW4state = digitalRead(SW4);
  SW5state = digitalRead(SW5);

  // Decrease brightness
  if(SW5state == LOW && LED2level > 0) {
    LED2level -= 1;
  }

  // Increase brightness
  if(SW4state == LOW && LED2level < 255) {
    LED2level += 1;
  }

  // PWM LED2
  pwmCounter = 255;
  while(pwmCounter != 0) {
    if(LED2level == pwmCounter) {
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
 *      value of the LED2level variable. What range of values do they
 *      allow the LED2level variable to be?
 * 
 * 2.   The main loop() of this program can be considered an an infinite,
 *      condition-less loop. The while() loop inside the program's main
 *      loop implements a condition, so it should act as a finite loop.
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
 *      digit difference in the value of the LED2level variable.
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
 *      once when the condition is true, while statements keep re-evaluating
 *      their condition and repeating the code inside their braces while the
 *      condition is true.
 * 
 *      3) An expression is needed to modify the variable inside the while()
 *      condition. If the variable is never modified the program will appear
 *      to get stuck in the loop and never go on to run any other code – this
 *      is known as an infinite loop. The statement 'pwmCounter --;' uses a
 *      decrement operator to decrease the value of the loop variable by 1. 
 *
 *      A for() loop is an alternative to a while() loop and incorporates the
 *      same three parts of a while structure in a single statement. Compare
 *      the structure of the while() loop in the program with the for() loop,
 *      below. What is an advantage of using a for() loop instead of a while()
 *      loop? 
 *    
 *      Replace the entire while structure in the program with this for() loop:

  for(int pwmCounter = 255; pwmCounter != 0; pwmCounter --) {
    if(LED2level == pwmCounter) {
      digitalWrite(LED2,HIGH);
    }
    delayMicroseconds(20);
  }
  digitalWrite(LED2,LOW);
        
 *      Compile the program and upload it into your circuit to try it out. Does
 *      it work the same way as the program did when using the while() loop?
 * 
 * 6.   The pwmCounter variable defined in the program's header is known as a 
 *      'global' variable because it is available to all parts of the program.
 *      The for() loop, added above, *redefines* the pwmCounter variable as a
 *      'local' variable just for use within the for() loop using the 
 *      initialization statement: 'for(int pwmCounter = 255; ...'
 * 
 *      While both pwmCounter variables share the same name, they are different,
 *      and the contents of the second variable won't be accessible outside of
 *      the for() loop. As you can imagine, having two different variables with
 *      the same variable name can potentially lead to unexpected problems in 
 *      your program and should always be avoided – we're only doing it here to
 *      prove the point that it can be a problem! Let's see if this is really
 *      the case, or not.
 * 
 *      Add the line:

  pwmCounter = 128;

 *      above the for() loop in your program, and add the following lines below
 *      the for() loop to determine if the global pwmCounter variable will be 
 *      modified by the for() loop:
        
  if(pwmCounter == 128) {
    digitalWrite(LED4,HIGH);
  }
  else {
    digitalWrite(LED4,LOW);
  }
        
 *      What value should pwmCounter variable local to the for() loop have
 *      when the loop finishes? Build and upload the program into your
 *      circuit. If LED4 is lit, we know that the global pwmCounter variable 
 *      has not been modified by the for() loop. Do you think your prediction
 *      for the value of the local pwmCounter variable is correct?
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
    if(LED2level == pwmCtr) {
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
 *      pins – these are usually marked on with a tilde '~' character on
 *      the Arduino I/O headers, representing an analog wave. The inclusion
 *      of this instruction means that all of the previous PWM code can be
 *      replaced with a single analogWrite() statement. Replace all of the
 *      code below the switch input if conditions with these three lines:

   // PWM LED2
  analogWrite(LED2,LED2level);
  delay(10);

 *      What purpose does the 'delay(10);' statement serve in this program? 
 *      What happens if you comment the 'delay(10);' statement out?
 *
 * 10.  All of the work that went into generating and testing our own PWM
 *      algorithm might seem like wasted effort after realizing that that
 *      a single instruction can replace all of our code, but that is not
 *      the case. Developing and testign an algrithm to accomplish a task
 *      is an important skill, and will begood preparation for creating our
 *      own functions for new or un-supported hardware. Our code may even
 *      work more efficiently than pre-made functions which may contain
 *      extra code to support additional features or capabilities that our
 *      program may not need.
 *
 *      Look up the analogWrite() instruction in the Arduino reference
 *      documentation. What limitiations does analogWrite() have? Can you
 *      think of any applications that might benefit from different PWM
 *      frequencies, different PWM resolution (the number of distinct
 *      output levels), or more PWM outputs? Could our PWM code algorithm
 *      be modified to overcome some of the limitations in analogWrite()?
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
 *      pressed, create a program that uses a for() loop to slowly increase an
 *      LED's brightness when a button is pressed. In addition to gradually
 *      changing light level this could be a useful feature to soft-start an
 *      electric motor, potentially preventing the stresses caused by suddenly
 *      applying full power to a mechanical system. Either add a second button
 *      or use the same button as a toggle button to turn off the LED by
 *      gradually decreasing its output level.
 *
 * 4.   Make a program that automatically creates a repeated, visual 'pulse',
 *      by continuously brightening and dimming one or more of the LEDs.
 * 
 * 5.   Try making a 'chirp' or 'pew-pew' sound effect by using a for loop to
 *      sweep through a range of frequencies from low to high, or high to low,
 *      in response to a button press.
 */
