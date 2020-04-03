# MINT_EEGAcquisitionSystem

### Background
UBC MINT is developing an EEG Acquisition System for the 2020 NeurotechX competition Fixed Challenge. The goal is to design a board that can collect EEG potentials accurately and effectivley. The system will utilize a PIC32MX microcontroller to send data aquired from the specialized biopotential measurment device (ADS1299) to a PC, where the data will be analyzed and live-plotted.

The choice to use these components were based on reasearch which showed the prevalance of the ADS1299 in literature. Additionally, MINT wanted to develop a smaller and more compact design than previous submissions.

## Electrical

### Initial concept
The initial concept idea was to use a similar approach as to previous years. That being implementing instrumentation amplifiers, along with active filters in order to aquire our signal. 

After testing and research with various amplifiers and topologies, the choice was made to move to using the ADS1299 chip with passive and software filters instead.

### Note: 
Due to the global ourbreak of COVID-19 the electrical subteam has been limited in our access to resources required to finish and test the electrical componentes of the EEG aquisiton board.

## Software

### Note:
Due to the global ourbreak of COVID-19 the electrical subteam has been limited in our access to resources required to finish the electrical componentes of the EEG aquisiton board, and thus have been limited in firmware and software development.

## Budget
Below is the rough breakdown of costs, for those who want to replicate this design:
