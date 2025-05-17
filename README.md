# Smart Autonomous Robot

A multifunctional autonomous robot capable of:

- 🛣️ **Line Following**
- 🚧 **Obstacle Avoidance**
- 🎨 **Color Sorting** (Red, Green, Blue)

This project demonstrates a robust integration of sensors and control algorithms, enabling the robot to navigate paths, detect and avoid obstacles, and sort objects by color in real time.

## ⚙️ Features

### 1. Line Following
The robot uses **IR sensors** to detect black/white contrast on the floor, allowing it to follow a predefined line path smoothly.

### 2. Obstacle Avoidance
An **ultrasonic distance sensor** constantly checks for nearby obstacles. If an object is detected within a certain range, the robot:
- Stops or reroutes,
- Resumes its path after clearing the obstacle.

### 3. Color Sorting
Utilizes the **HW067 color sensor** to detect object colors. The robot:
- Identifies the color (Red, Green, or Blue),
- Sorts the object accordingly using a **servo motor** and drop mechanism.

## 🧠 Components Used

| Component               | Description                          |
|------------------------|--------------------------------------|
| IR Sensors             | For line following                   |
| Ultrasonic Sensor      | For obstacle detection               |
| HW067 Color Sensor     | For RGB color detection              |
| Servo Motor            | For mechanical sorting mechanism     |
| DC Motors              | For robot movement                   |
| Motor Driver Module    | Controls the motors                  |
| Microcontroller (e.g. Arduino Uno) | Central control unit             |
| Chassis                | Robot body                           |
| Power Supply           | Battery or external power            |

## 🛠️ How It Works

1. **Startup**: Robot calibrates its sensors.
2. **Navigation**: Follows the line using IR feedback.
3. **Obstacle Detected**: Halts or reroutes using distance feedback.
4. **Color Detection Zone**: Stops to scan object color.
5. **Sorting**: Activates servo to drop the object in the corresponding bin.

## 📷 Demo

![Robot Demo](link-to-your-demo-gif-or-image)

> _Tip: Upload demo images or a YouTube video link to showcase your robot in action._

## 🚀 Future Improvements

- Wireless control and monitoring (via Bluetooth or Wi-Fi)
- Machine learning-based color detection for more accuracy
- Enhanced PID control for smoother line following
- Integration with IoT dashboards for analytics

## 📁 Project Structure

```bash
Smart-Robot/
│
├── Code/
│   └── main.ino            # Arduino code
├── Images/
│   └── demo.png            # Demo animation
└── README.md               # Project documentation
