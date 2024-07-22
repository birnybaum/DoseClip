# DoseClip

## Overview

Human auditory frequency falls in the range of 20Hz – 20kHz. Prolonged exposure to high noise levels within this range can lead to permanent damage, such as sensorineural hearing loss. To mitigate this risk, individuals need continuous feedback on their noise exposure. The **DoseClip** project addresses this need by providing an affordable, wearable, and easy-to-use device for monitoring noise exposure.

## Project Description

### Motivation

Current noise dosimeters are often costly or inconvenient, making it challenging for individuals to monitor their noise exposure effectively. Our goal was to design a device that is both affordable and practical for everyday use, helping users to stay informed about their noise exposure and reduce the risk of hearing damage.

### Design Specification

Our proposed device, **DoseClip**, is designed to adhere to OSHA regulations for daily noise exposure. The device incorporates the following features:

- **Microphones**: Utilizes both Electric Condenser Microphone (ECM) and Micro-Electro-Mechanical System (MEMS) microphones to cover the full range of human hearing.
- **Regulatory Compliance**: Meets OSHA standards for noise dosimeters.
- **Design Evaluation**: The **DoseClip** was selected from a concept list using the Pugh method, ensuring it met the majority of our design requirements.

### Feasibility Testing

Feasibility testing involves:

- **Component Functionality**: Evaluating each component used in the **DoseClip** to ensure it operates as intended.
- **Integration**: Ensuring that all components work together seamlessly to provide accurate noise exposure measurements.


## Project Files

### `Final_DoseClip.ino`

This file contains the Arduino code used for the **DoseClip** device. It handles noise measurement using ECM and MEMS microphones and outputs the data.

**Key Features**:
- Reads noise levels from microphones.
- Outputs high noise levels and normal noise levels to the serial monitor.

**Usage**:
1. Upload the code to the Arduino board using the Arduino IDE.
2. Connect the board to your computer via USB to monitor the data.

### `5_second_measurements.py`

This Python script processes and analyzes noise level data collected from the **DoseClip** device. It includes functions for calculating average noise levels and plotting noise levels over time.

**Key Features**:
- Calculates average and maximum noise levels.
- Plots noise levels over time for visualization.

**Usage**:
1. Ensure you have the necessary Python libraries (`numpy`, `matplotlib`).
2. Run the script with your collected noise data to analyze and visualize it.

### `DoseClip MANUAL`

The user manual provides instructions on setting up and using the **DoseClip** device. It includes hardware setup, software setup, and usage instructions.

**Key Sections**:
- **Installation**: Details for hardware and software setup.
- **Usage**: Instructions for powering on the device and monitoring data.

### `DoseClip Final Report.pdf`

This document contains the complete project report from conception to final implementation. It includes the project idea, design specifications, development process, and testing.

**Key Sections**:
- **Idea Conception**: Initial project goals and inspiration.
- **Brainstorming**: Design goals and component selection.
- **Development**: Prototype creation, integration, and testing.
- **Finalization**: Final design and production.

## Getting Started

To get started with the **DoseClip** project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/birnybaum/DoseClip.git
   cd DoseClip
   ```

2. **Upload Arduino Code**:
   - Open `Final_DoseClip.ino` in the Arduino IDE.
   - Upload the code to your Arduino board.

3. **Run Python Analysis**:
   - Install the required Python libraries.
   - Modify `5_second_measurements.py` with your collected data and run the script.

4. **Refer to the User Manual**:
   - Consult `DoseClip Manual.md` for detailed setup and usage instructions.

5. **Read the Project Report**:
   - Review `DoseClip Final Report.pdf` for a comprehensive understanding of the project.

## Contact

For questions or further information, please contact [Andrew M. Birnbaum](mailto:BirnbaumAndrew@gmail.com).

## Acknowledgements

- Research and inspiration from existing noise dosimeters and patents.
- Department of Biomedical Engineering, The City College of New York.
- **Team Members**:
    - Andrew Birnbaum
    - Kristian Jacome
    - Daniel Khalil
    - Mohigul Nasimova
    - Sebastian Sauco-DeLima
- **Instructors**:
    - Professor Carriero
    - Professor Ahmed
- **Sponsor**:
    - Claus-Peter Richter, Northwestern University
