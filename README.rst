.. zephyr:code-sample:: thesis_project
   :name: thesis_projectd

   Utilizing ZephyRTOS to build an embedded vision AI hand gesture predictor utilizing the RENESAS EK-RA8D1 board.

Overview
********

A simple code using Zephyr APIs to flash the memory of the EK-RA8D1 board by Renesas with an image C array representing a hand gesture.
A vision AI model that is flashed along with the image in the board, based on the MobileNetV2 will be used to classify hand gesture  using the device's resources.


Building and Running
********************

This application can be built and executed on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: src/main
   :host-os: Ubuntu 24.04LTS
   :board: EK-RA8D1
   :goals: run
   :compact:

To build for another board, change "EK-RA8D1" above to that board's name.

Packages versions used in the project:
Python version: 3.11.13
TF: 2.18.0
NumPy: 2.0.2
Keras version: 3.8.0

