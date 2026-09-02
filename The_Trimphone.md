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
## TESTING HOOK SWITCH

Let's start buy testing that the hook switch works properly. We will test *continuity*, and make an LED turn ON/OFF when pushing the switch. 

- Look at the TERMINAL BLOCK: aligned set of screws on the phone's circuit. They go from T1 to T19. See [this reference image](https://github.com/kingston-hackSpace/Rotary_Dial_Phone/blob/main/Screws.jpg)

- T2 and T6 should internally connect the hook switch. Make a continuity test using a tester to confirm. Press the hook switch when you make the test. If you need further guidance, ask a hackSpace technician. 

- Clamp a coloured crocodile clip to T2, and a black crocodile clip to T6. From the other side of the crocodile clips, clamp a wire, and then follow this [LED wiring diagram]()
