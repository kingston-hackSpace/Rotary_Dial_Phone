# The Trimphone

[About the The Trimphone](https://www.londonmuseum.org.uk/collections/v/object-726842/telephone/), by the London Museum. 

[How did the phone sound?](https://www.youtube.com/watch?v=lYEIRegf22k)

---
# Tutorial
---
## DESCRIPTION

In this tutorial, we will trigger the phone's **ring** and **"hook switch**. We will also play a soundtrack directly on the **handset**.

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

Let's start buy testing that the hook switch works properly. We will test *continuity*, and make an LED turn ON/OFF when pushing the switch. 

- Look at the TERMINAL BLOCK: aligned set of screws on the phone's circuit. They go from T1 to T19. See [this reference image](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/Screws.jpg)

- T2 and T6 should internally connect the hook switch. Make a continuity test using a tester to confirm. Press the hook switch when you make the test. The multimeter should "bip" when the switch is pressed. If you need further guidance, ask a hackSpace technician. 

- Clamp a coloured crocodile clip to T2, and a black crocodile clip to T6. From the other side of the crocodile clips, clamp a wire, and then follow this [LED wiring diagram](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_hook-switch.jpg)

- Upload [this code](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_hook-switch.ino) into your Arduino Board.

- The LED should turn ON/OFF when you pressed the phone's hook switch.

---
## TESTING the TRANSDUCER (ringer)

**STEP 1: the Transducer**

A transducer is an electronic component that converts an electrical signal directly into sound. This is the component that emits the "calling ringing sound" in a Trimphone. 

*NOTE: Older dial phones use mechanical bells instead of transducers. If you are hacking one of those, the following instruction will differ.*

- Identify in the tranducer in the phone's circuit board, and identify its possitive and negative terminal screws. You should see a positive icon (+) on it. See this [reference image](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/transducer.jpg)

- Clamp a red crocodile clip on the positive terminal (+), and a black crocodile clip on the negative terminal.

- We will recap this part later, leave it like that for now. 

**STEP 2.1: The H-Bridge Motor Driver**

You will need a H-bridge motor driver to make the transducer "ring". 

The transducer needs an AC signal to produce sound, but Arduino pins only output steady DC. The H-Bridge lets us rapidly flip polarity under Arduino control, simulating the AC signal required.

You will need a 12V Power Supply to power the H-bridge driver. 

- Follow this [wiring diagram](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/test_transducer_bb.jpg)

- Upload [this code] to your Arduino board.

- As a result, the transducer should ring if the hook switch is not pressed (handset lifted), and stop ringing if the switch is pressed. 

 **STEP 2.2: Exploring ringing patterns (OPTIONAL)**




STEP 3: The code

Intall 2 libraries:
