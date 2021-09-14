# Smart Elevator Systems using Embedded Machine Learning and Fire Safety Mechanisms

April - June 2021 | Micro Project in SY BTech | Read: [Project Report](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/Project%20Report.pdf)
*Awarded "Best Project" out of a pool of 1000+ projects at the 5th IEEE National Level Project Competition.*

## Introduction

Using an approach of Embedded Machine Learning, we built a multi-tenant architecture to facilitate a contactless elevator system. It consists of two parts – person detection and speech recognition. To create an effective pipeline, we used multiple signal processing techniques to extract necessary features from the input signals. Further, we developed a fire safety system using basic yet functional sensors in two methods – using a microcontroller and using an operational amplifier. These systems are deployed outside and inside an elevator, respectively. Lastly, we built a PCB to house all these components and make a holistically deployable product.



## High-Level Process Flow

First, we would want a person to come and stand in front of the elevator, indicating that he wants to use it. 
Then, the person would speak the floor number he would like to visit, and the elevator system recognizes the floor number which was spoken. The elevator then operates as it should and the doors should open for him. The overall flow of the system is shown in the figure below.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/Process%20Flowchart.png)



## System Overview

The project a three-part system encompassing the following subsystems:

1. Person recognition (VWW Detection) and voice recognition (KWS) to operate the elevator.

2. Fire safety mechanism inside the elevator to drop installed oxygen masks and signal the main elevator interface.

3. Fire safety and detection system outside the elevator on different floors bundled with the features mentioned in point (1).

A generic block diagram of the entire system is shown below.

   ![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/Overall%20Block%20Diagram.png?raw=true)



## Contactless Operation using KWS and VWW CNN Models

The KWS and VWW models are combined in a multi-tenant architecture. In such a structure, only one of the two models runs inference on the input data at a time. This allows for fast inferences and efficient memory allocation when and wherever required. As our development board of choice - *Arduino Nano 33 BLE Sense*, has limited resources available on board (1MB CPU Flash Memory, 256KB SRAM), the neural network on the system had to be memory and energy efficient compared to a whole scale neural network model. Further post-training quantization methods were implemented to reduce the size of the model (KWS model: 26,720 bytes; VWW model: 3,00,568 bytes; Total size after compilation: 207712 bytes 79% of dynamic memory) and latency of the inferences in real time.

#### Visual Wake Word (VWW) Model for Person Detection

The Visual Wake Word model used for our elevator use case is based on an existing MobileNets model. The core concept behind the architecture is depthwise separable convolution. This is a variant of classical two-dimensional convolutions that works in a much more efficient way, without compromising on accuracy greatly. The model has various steps, as shown in the figure below. Namely, these steps are Initialization, Pre-Processing, Model Inference, and Response.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/VWW%20Model.jpg)

#### Keyword Spotting (KWS) Model for Speech Recognition

To enable a completely contactless experience for the elevator interface, we implemented a speech recognition approach to choose the floor number that a given user would like to go to. We went on to implement a KWS (Keyword Spotting) model to satisfy this requirement. The chosen keywords were floor numbers in the lower order “One”, “Two”, “Three” and “Four”. Like the VWW model, the KWS model has 4 high level steps in the system as shown in the figure below. Compared to the prior, this model is relatively lightweight and takes lesser time for training and inference.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/KWS%20Model.jpg)

To make it easier for the CNN to process and classify the audio signals into different categories, we extract the features of the buffer audio sample before passing it into an inference pipeline. The various steps of feature extraction are:

- Fast Fourier Transform (FFT)
- Frequency Domain Spectrograms
- Mel Frequency Cepstral Coefficient Spectrograms

#### Multitenant Architecture for Running KWS and VWW Simultaneously

Due to the memory and power constraints on any embedded microcontroller, running two CNN inference engines simultaneously is a challenge. Our approach to this problem was to implement a multi-tenant architecture for combining the KWS and VWW model. In such a structure, only one of the two models runs inference on the input data at a time. Both models share the TensorArena and use the same memory allocations. This allowed for fast inferences and efficient memory allocation when and wherever required. There is also no requirement for the synchronization of data streams from the camera module and the microphone, both of which are running at different sampling rates.



## Fire Safety System

Elevator shafts may be exposed to smoke and that smoke could reach occupants not just inside the elevator but on other floors as well. In such situations, the elevator is advised to return to the ground floor of the building immediately. The most efficient way to develop a fire safety system which protects the occupants of an elevator is to design a system which works in tandem with it the smoke/flammable gas detectors and temperature sensors directly. To maximize the efficiency of such a system, we developed a pipeline in which the main elevator interface has direct inputs from the smoke detection units. Depending on the levels obtained from the sensors, the elevator interface can further be commanded to execute a specific set of instructions, for example taking the elevator to the lowest floor immediately in the case of a fire.

To implement our approach, we chose to use a MQ-2 Smoke/Flammable Gas Detector and a LM-35 Temperature sensor.



## Implementation and Results

The hardware required for the implementation of the contactless elevator system, i.e., the VWW and KWS models was readily available with us, namely the Arduino Nano 33 BLE Sense and OV7675 Camera Module. They are mounted on a shield for the scope of this experiment. Further into the implementation, we designed our own shield to house the OV7675 and Arduino module along with other peripherals.

Once the shield was properly positioned, we ran inference by standing inside and outside the frame of the camera. As discussed in the System Architecture chapter, each inference returns a probability value between -127 and +127, where higher numbers indicate a higher probability of a human subject being present in the frame.

The camera input of greyscale QCIF images of size 144 x 176 pixels with human subject are shown below.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/QCIF%20Input%20Images.png)

Once the inference engine is run, the probability values are generated. These values are printed on the serial monitor of the Arduino IDE. When a person is entering the frame or in motion, the camera is unable to pick up the fast movement due to the low frame rate. At such moments, the model is decisive of whether a person is the frame or not. Hence, while classifying as a human detected in the field of view, we chose to keep a minimum Person score of 25. This threshold value reduces the number of false positives. If a person is detected in the frame, the green RGB light on the Arduino is lit up, whereas when there is no person detected, the red RGB light is lit up.

Once a person has been detected in the frame, the KWS model inference engine is triggered, and the system starts listening for keywords spoken by the user to communicate the floor number which they would like to go to. These numbers are chosen to be “One”, “Two”, “Three”, and “Four”. The incoming audio is sampled at 16 kHz and ran inference on every one second. Whenever the Arduino is listening for a keyword, the yellow light rapidly blinks, and upon positive inference, the blue RGB light is lit up. The different LED states are shown in the image below.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/LED%20Indicators.png)

The fire safety system outside the elevator bundled with the deployed unit was simulated on Proteus. The system consisted of the following components:
1. MQ-2 Smoke Detector System
2. LM-35 Temperature Sensor
3. 7 Segment Display using Shift Register
4. Alarm and Connection to Main Elevator Interface

Since the Arduino Nano 33 BLE Sense was not available as a library for simulation, we used the Arduino Nano baseline model for it. The architecture is similar and hence is adequate for the purposes of the project. For the sake of completeness in the project, we chose to go create a pseudo-main elevator interface using an Arduino Uno in the simulation. A 4 x 16 LCD Display was also added for us to keep track of the system status. The figure below shows the circuit schematic for the project on Proteus. The Arduino Nano is interfaced with a LM-35 and MQ-2 sensor, a 7 Segment Display and an alarm system which is triggered when the system is simulating a fire scenario.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/Proteus%20Simulation.png)

#### PCB Design

To house the components of this project, we created a Printed Circuit Board design using KiCAD, an open-source EDA software. Some key specifications of the PCB are:

1. The PCB consists of 4 Copper layers.

2. Front and Back Copper Layers are signal layers.
3. Inner1 Copper layer contains a Power Plane.
4. Inner2 Copper layer contains a Ground Plane.
5. All components used utilize Through Hole Technology (THT) except for 74AHC1G86 Dual Input Single Output EX-OR Gate which uses SMT.

![](https://github.com/anwaypimpalkar/smartElevatorSystem/blob/main/src/PCB%20Render.png)



## Demonstration

The hardware required was implemented as a proof of concept for the evaluation of the project. An unnarrated [video demonstration](https://youtu.be/mMH1OMFZL_I) has been documented. 



## Group Details

This project was created under the guidance of Dr. Deeplaxmi Niture by a group of 3 students: Esha Dorle, Sayali Gadre and myself - all second year students in the Electronics and Telecommunications Department at College of Engineering, Pune.
