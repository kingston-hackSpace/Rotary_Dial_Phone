# The Trimphone

[About The Trimphone](https://www.londonmuseum.org.uk/collections/v/object-726842/telephone/), by the London Museum. 

[How did the phone sound?](https://www.youtube.com/watch?v=lYEIRegf22k)

---
# Tutorial
---
## DESCRIPTION

In this tutorial, we will trigger the phone to **ring** via the **"hook switch**. We will also play a soundtrack directly on the **handset**.

*This tutorial doesnt cover using the phone's dial.* 

---
## HARDWARE

- A Trimphone

- Multimeter

- Arduino UNO

- Dual H-Bridge motor driver (L298N)

- MP3 Shield + hamburger speaker

- micro SD card

- 12V power supply

- button

- LED

- 220ohms Resistor

- 3.5 Audio Jack connector with 4 screw terminals (male)

- Crocodile clips

- Breadboard

---
## OPENING THE PHONE

- You need to remove 2 screws to open the phone:

  - One on the underside of the phone
 
  - One at the front, under the handset.

- Put the dial aside, just pick it up carefully.

---
## IDENTIFYING THE PARTS

Identify :

  - Handset

  - Dial

  - Hook switch

  - Transducer (ringer)

See [reference image here](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/Phone_parts.jpg)

---
## TESTING the HOOK SWITCH

Let's start by testing that the hook switch works properly. We will test *continuity*, and make an LED turn ON/OFF when pushing the switch. 

- Look at the TERMINAL BLOCK: aligned set of screws on the phone's circuit. They go from T1 to T19. See [this reference image](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/Screws.jpg)

- T2 and T6 are internally connected to the hook switch. Make a continuity test using a tester to confirm. Press the hook switch when you make the test. The multimeter should "beep" when the switch is pressed. If you need further guidance, ask a hackSpace technician. 

- Clamp a coloured crocodile clip to T2, and a black crocodile clip to T6. From the other side of the crocodile clips, clamp a wire, and then follow this [LED wiring diagram](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_hook-switch.jpg)

- Upload [this code](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_hook-switch.ino) to your Arduino Board.

- The LED should turn ON/OFF when you press the phone's hook switch.

---
## TESTING the TRANSDUCER (ringer)

**STEP 1: the Transducer**

A transducer is an electronic component that converts an electrical signal directly into sound. This is the component that emits the "calling ringing sound" in a Trimphone. 

*NOTE: Older dial phones use mechanical bells instead of transducers. If you are hacking one of those, the following instruction will differ.*

- Identify the tranducer in the phone's circuit board, and identify its positive and negative terminal screws. You should see a positive icon (+) on it. See this [reference image](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/transducer.jpg)

- Clamp a red crocodile clip on the positive terminal (+), and a black crocodile clip on the negative terminal.

- We will revisit this part later, leave it like that for now. 

**STEP 2.1: The H-Bridge Motor Driver**

You will need an H-bridge motor driver to make the transducer "ring". 

The transducer needs an AC signal to produce sound, but Arduino pins only output steady DC. The H-Bridge lets us rapidly flip polarity under Arduino control, simulating the AC signal required.

You will need a 12V Power Supply to power the H-bridge driver. 

- Follow this [wiring diagram](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_transducer_bb.jpg)

- Upload [this code](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_transducer.ino) to your Arduino board.

- As a result, the transducer should ring if the hook switch is not pressed (handset lifted), and stop ringing if the switch is pressed. 

 **STEP 2.2: Exploring ringing patterns (OPTIONAL)**

The ringing pattern in the previous code has been programmed to sound that way. If you would like it to sound different, you can re-programme the pattern.

The ringing pattern is entirely controlled by one array in your code:

    const unsigned long ringPattern[] = {400, 200, 400, 2000};

This is a sequence, cycling through 4 steps (array of 4 values), in which the values are durations in milliseconds for each step. Change these values to explore different patterns:

    const unsigned long ringPattern[] = {100, 0, 300, 100};

    const unsigned long ringPattern[] = {200, 150, 200, 1200};

 **STEP 2.3: Exploring sound pitch (OPTIONAL)**

 Identify the following variables in your code:

     const unsigned long pitchA = 400;
     const unsigned long pitchB = 350;

pitchA and pitchB are the two frequencies your code alternates between to create the warble sound. Test the following values:

     const unsigned long pitchA = 800; // ~625Hz
     const unsigned long pitchB = 500; //~1000Hz

Curiosity: Check [how this phone used to sound here](https://www.youtube.com/watch?v=lYEIRegf22k)

**STEP 3: Installing libraries**

To be able to use the MP3 shield you will need to install some libraries. 

Follow the instructions here: [Using the SFEMP3Shield Library](https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup-guide-v15/all#using-the-sfemp3shield-library)

Once you have installed the libraries, test that they are working properly by following the example available at the same link: "Upload an Example Sketch".

Ask a technician if you need further support

**STEP 4: MP3 on the SD card**

Your MP3 shield KIT should include an SD card. 

Use your computer to upload an MP3 track to the SD card. The track **MUST** be titled as follows:

    track001.mp3

**STEP 5: MP3 Shield**

- To do the following step, you will need to remove the wires from the Arduino UNO. Remember their pin numbers.
  
- Mount the MP3 shield on top of your Arduino UNO.

- Re-wire as before, but now on the MP3 shield.

- Plug the hamburger-speaker into the MP3 shield's 3.5 jack connector. 

- Upload [this code](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_mp3-shield.ino) to your board.

- The track should play when the hook switch is pressed (handset down)


- **STEP 6: Listening via the handset**

For our last step, we want to use the handset instead of the hamburger-speaker. 

- Unwire the handset from the phone's circuit board (unscrew the wires, 4 in total)

- Rewire them to a **3.5 Audio Jack connector with 4 screw terminals (male)**. See connections below or [this photo](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/jack_connector.jpg):

    - White > GND
 
    - Red > V
 
    - Blue > R
 
    - Green > L
 
- Remove the hamburger-speaker from the MP3 shield, and connect the **3.5 Audio Jack connector with 4 screw terminals (male)** instead. 

- This should be enough. You should now hear the sounds coming from the handset.
