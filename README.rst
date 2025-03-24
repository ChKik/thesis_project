.. zephyr:code-sample:: thesis_project
   :name: thesis_projectd

   Flash the memory of the device with a C array that represents an image and read it after. 

Overview
********

A simple code using Zephyr APIs to flash the memory of the EK-RA8D1 board by Renesas with an image C array.

Building and Running
********************

This application can be built and executed on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: src/main
   :host-os: unix
   :board: qemu_x86
   :goals: run
   :compact:

To build for another board, change "qemu_x86" above to that board's name.

