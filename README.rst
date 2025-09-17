.. zephyr:code-sample:: thesis_project
   :name: thesis_project

Overview
********


Flash the memory of the device images from a hand gesture dataset and then use a customtrained model based on MobileNetV2 in order to make predictions.
In order to run this project for yourself , make sure the paths for the files are correct in all the scripts to locate the dataset and the directories
,then execute the initiation_script in order to invoke a prediction from the model.


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

