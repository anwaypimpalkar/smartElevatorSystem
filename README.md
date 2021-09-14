# Smart Elevator Systems using Embedded Machine Learning and Fire Safety Mechanisms

April - June 2021 | Micro Project in SY BTech

## Introduction

Using an approach of Embedded Machine Learning, we built a multi-tenant architecture to facilitate a contactless elevator system. It consists of two parts – person detection and speech recognition. To create an effective pipeline, we used multiple signal processing techniques to extract necessary features from the input signals. Further, we developed a fire safety system using basic yet functional sensors in two methods – using a microcontroller and using an operational amplifier. These systems are deployed outside and inside an elevator, respectively. Lastly, we built a PCB to house all these components and make a holistically deployable product.

## System Overview

The project a three-part system encompassing the following subsystems:

1. Person recognition (VWW Detection) and voice recognition (KWS) to operate the elevator.

2. Fire safety mechanism inside the elevator to drop installed oxygen masks and signal the main elevator interface.

3. Fire safety and detection system outside the elevator on different floors bundled with the features mentioned in point (1).

A generic block diagram of the entire system is shown below.

   ![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Overall%20Block%20Diagram.png)



## Data Management and Quasar VueJS App

This subsystem was my primary responsibility and contribution to the project. 

To fulfill my purposes, I chose to use the cheap and readily available ESP-8266 NodeMCU development board with a built-in Wi-Fi module for internet connectivity. The data was stored and sent to the cloud for easy user access. 

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Data%20Subsystem%20Block%20Diagram.png)

For storing the incoming sensor data from the Arduino Uno, I created two channels - online and offline storage:

- **Online Storage:** In the presence of a connection to the internet, the data was sent to a Google Firebase Realtime Database. This was chosen because of the low latency and cross-platform API availability. The sensor data was stored in the database by using the APIs provided using the [Firebase-ESP8266 library](https://github.com/mobizt/Firebase-ESP8266).
- **Offline Storage:** To facilitate the storage of data even in the absence of a stable internet connection, I interfaced a microSD card to the ESP8266 using a [HW-125 card reader](https://datasheet.octopart.com/32312-Parallax-datasheet-13552938.pdf). Whenever the internet connection resumed, the offline data is synced to online database.

To make the data easily accessible, I built an app on the [VueJS Quasar Framework ](https://quasar.dev/). On a high-level, the app has the following features:

- **Tabular Data Overview:** All the data uploaded to the Firebase database is displayed reverse chronologically in a tabular fashion on the home screen of the app. The data is retrieved from the database using the provided [Firebase JavaScript SDK](https://firebase.google.com/docs/reference/js).
- **Graphical Analytics:** To analyze data trends with more ease, the home screen also contains graphical representations of all the datasets individually. This was executed using the [ApexCharts.js](https://apexcharts.com/) library.
- **Device Online/Offline Status (KeepAlive System):** The ESP8266 sends a KeepAlive message to Firebase every 5 seconds when the device is online. It is immediately reflected in the app as well. If the device misses 3 such KeepAlive pings, the device status changes to offline.
- **View Device Sensor Health:** If a particular sensor malfunctions on the Arduino Uno, the ESP8266 updates the database about the sensor error for the user to check. 
- **Update Acceptable Sensor Reading Parameters:** Through the app, users are able to change the acceptable values of the on-board sensors which decide whether a given user is within the acceptable SpO₂ and temperature ranges. 
- **View Basic Overview of Project:** A page including the project details, links and references is also added to the app.

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/App%20Screenshots%201.png)

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/App%20Screenshots%202.png)

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Firebase%20Screenshot.png)

## Hardware Demonstration

The hardware required was implemented in a makeshift manner as a proof of concept for the evaluation of the project.  An unnarrated [video demonstration](https://youtu.be/aAD6R5BNwCo) has been documented. The [presentation slides](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/CovPrev%20Presentation%20Slides.pdf) of this project are also made available.

![Hardware Assembly](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Hardware%20Assembly.png)

## Group Details

This project was created by a group of 5 students: Kushagra Shrivastava, Shubham Mujumdar, Esha Dorle, Ishita Rathor and myself - all second year students in the Electronics and Telecommunications Department at College of Engineering, Pune.
