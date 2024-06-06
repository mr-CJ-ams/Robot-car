# Sumobot and Pathfinder Robot in a One System Robot Car

Overview
The "Sumobot and Pathfinder Robot in a One System Robot Car" project integrates the competitive features of a sumo-bot with the navigational abilities of a pathfinder robot into a single, adaptable robotic platform. Leveraging Arduino for control, this robot is designed to excel in both sumo wrestling matches and complex obstacle navigation tasks. A simple switch allows users to toggle between Sumobot mode and Pathfinder mode, making it easy to adapt the robot's behavior for different challenges.

**System Components**

Arduino Uno, Ultrasonic Sensors, DC Motors, Wires, IR Sensors, SPDT Switch, SPST Switch

**Operational Modes**

**Sumobot Mode:**

Tornado Mode: The robot starts by spinning in place, a defensive maneuver to scan for opponents.

Attack Mode: When the front ultrasonic sensor detects an enemy, the robot stops spinning and charges forward aggressively to push the opponent out of the ring.

The Sumobot leverages its front ultrasonic sensor to identify the opponent and initiate a forceful attack. This mode is optimized for rapid response and powerful movements to dominate sumo matches.

**Pathfinder Mode:**

Navigation Logic: The robot uses three ultrasonic sensors to evaluate distances to obstacles on its front, left, and right. Based on these measurements, it determines the best path to proceed.

Proportional Control: If the robot deviates from its intended path or comes too close to obstacles, it employs a proportional control algorithm to correct its course and stay centered.

Error Correction: The robot constantly monitors its position. If it nears a collision on either side, it adjusts its motor speeds proportionally to steer back to the center.

**Schematic Diagram**

![image](https://github.com/mr-CJ-ams/Robot-car/assets/110215820/f58f3860-6a70-47cd-ad50-ad4b13752216)

**Project Output**

![441511826_442710778711932_3796913298322508990_n](https://github.com/mr-CJ-ams/Robot-car/assets/110215820/4bf49cb9-f61f-4d40-835a-cfedfe16f2c2)

![441924905_361804740250197_2196158691020582833_n](https://github.com/mr-CJ-ams/Robot-car/assets/110215820/98bea9f6-fa31-4a4f-b21e-508ce489e60f)

![441929606_776368778030737_5923227439963569195_n](https://github.com/mr-CJ-ams/Robot-car/assets/110215820/f0017b03-29ed-4b35-83fc-f37e4fa8683e)





