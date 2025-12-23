# **Investment Simulator**



###### A simple command-line investment simulation game shows how monthly contributions and market changes affect a portfolio. The simulator supports various market conditions, displays a month-by-month progression, and can create PNG charts for growth and comparison.



#### **Highlights**

* ###### Interactive command-line menu
* ######  Set initial amount, monthly contribution, duration (up to 36 months), and loss threshold
* ###### Market types: Stable, Volatile, Bullish, Bearish, Crisis
* ###### Generates two PNG charts: investment\_growth.png and investment\_comparison.png
* ###### Built with C++11 and CMake (Ninja is recommended)

#### 

#### **Prerequisites**

* ###### CMake >= 3.10
* ###### A C++ compiler with C++11 support (MSVC, GCC, or Clang)
* ###### Ninja (recommended generator)
* ###### Git
* ###### Optional (Windows): Open the repository in Visual Studio and use the CMake Targets window.



#### **Build (Ninja)**



###### Open a terminal at the repository root and run:

###### 

###### Configure with Ninja: cmake -S . -B build -G "Ninja"



###### Build: cmake --build build --config Release

###### 

###### The executable will be placed in build/bin/:

###### 

###### \- Windows: build\\bin\\InvestmentSimulator.exe

###### \- Linux/macOS: build/bin/InvestmentSimulator



#### **Run:**

###### From the repository root:

###### 

###### \- Windows (PowerShell or cmd): build\\bin\\InvestmentSimulator.exe

###### \- Linux/macOS: ./build/bin/InvestmentSimulator

#### 

#### **Menu (what each option does)**

* ###### Start New Investment Simulation: Set initial amount, monthly contribution, duration (≤36 months), loss threshold (20–100%), and choose a market type. The simulator will run month by month.
* ###### View Investment Summary: Displays initial amount, monthly contribution, total invested, current value, profit/loss, and return %.
* ###### Generate Growth Chart: Creates investment\_growth.png (portfolio value vs. month).
* ###### Generate Comparison Chart: Creates investment\_comparison.png (Initial vs Total Invested vs Final Value).
* ###### Reset Investment: Clears stored simulation data.
* ###### How to Play: Provides brief guidance and tips.
* ###### Exit: Quits.



###### Follow the on-screen prompts. Any non-numeric input will be rejected, and you'll be asked again.



#### **Example Walkthrough**



###### Choose 1 to start a simulation.

###### 

###### Enter initial amount, for example, 1000.

###### 

###### Enter monthly contribution, for example, 100.

###### 

###### Enter duration, for example, 12.

###### 

###### Enter loss threshold, for example, 30.

###### 

###### Select market type (1–5).

###### 

###### Once the simulation is complete, choose 3 or 4 to generate charts. PNG files are saved to the program's working directory (usually build/bin/).



##### **Output files:**

1. ###### investment\_growth.png — line (scatter) chart of portfolio value by month.
2. ###### investment\_comparison.png — bar chart comparing initial, total invested, and final value.

###### Open the files with any image viewer.



##### **Troubleshooting:**

* ###### C++ standard errors: Ensure your compiler supports C++11 and that CMake uses the correct compiler.
* ###### Charts not generated: The project includes pbPlots.hpp and supportLib.cpp. Make sure the executable has write permission for the output directory.
* ###### Inputs appear to hang: The program expects numeric input. Invalid input will be rejected, and you will be prompted again.
* ###### If using Visual Studio, open the folder and check the CMake Targets window or set up a Ninja CMake preset.



##### **Note:** This is an educational demo only; it is not financial advice.

