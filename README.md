# MINT_EEGAcquisitionSystem

### Background
UBC MINT is developing an EEG Acquisition System for the 2020 NeurotechX competition Fixed Challenge. The goal is to design a board that can collect EEG potentials accurately and effectivley. The system will utilize a PIC32MX microcontroller to send data aquired from the specialized biopotential measurment device (ADS1299) to a PC, where the data will be analyzed and live-plotted.

The choice to use these components were based on reasearch which showed the prevalance of the ADS1299 in literature. Additionally, MINT wanted to develop a smaller and more compact design than previous submissions.

## Electrical

### Initial concept
The initial concept idea was to use a similar approach as to previous years. That being implementing instrumentation amplifiers, along with active filters in order to aquire our signal. 

After testing with various amplifiers and topologies, performing some research, and receiving input from colleagues, the choice was made to move to using the ADS1299 chip with passive and software filters instead.

### Microcontrolelr
![](Images/MCU.JPG)
The PIC32MX400 family is being utilized for this project. The microcontroller was chosen due to its....

![](Images/USB.JPG)
To interface with a PC for data transfer, we have implemented an FT232R USB UART IC. This device connects to the UART peripherals of the PIC32 in order to transfer data to and from a PC with a wired USB-A connection.

### ADS1299
![](Images/ADS1299.JPG)

### Power Electronics
![](Images/Power%20circuit%20for%20documentation.JPG)

### Note: 
Due to the global ourbreak of COVID-19 the electrical subteam has been limited in our access to resources required to finish and test the electrical componentes of the EEG aquisiton board.

## Software

### Board Firmware
Unfinished - see programminginfo.txt

### Data processing (PC)
unfinished

### Note:
Due to the global ourbreak of COVID-19 the electrical subteam has been limited in our access to resources required to finish the the EEG aquisiton board, and thus have been limited in firmware and software development.

## Budget
Below is the rough breakdown of costs, for those who want to replicate this design:

---
