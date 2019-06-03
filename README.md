-------------------------------------------------------------------------------
ProtoKitApp I2C example
-------------------------------------------------------------------------------

Requirements
------------
Tool: ModusToolbox™ IDE 1.1
Programming Language: C
Associated Parts: All PSoC 6 MCU parts

Supported Kits
--------------
PSoC 6 CY8CPROTO-063-BLE

Overview
--------
This example project demonstrates the basic operation of the I2C master resource. 
The I2C master SCB sends commands to get data from TSL251 Ligth Sensor board.
https://www.adafruit.com/product/439

Import , Build and Program
-----------------
1. Clone repository
git clone https://github.com/mtuxpe/cypress_psoc63.git
or get the zip file from repository
https://github.com/mtuxpe/cypress_psoc63/archive/master.zip
2. Open ModusToolBox IDE
2.1 Click on "New application" choose CY8CPROTO-063-BLE and click Next
2.2 Click on "Import..."
2.3 Goto app main directory and select file "modus.mk"
3. Click on "Build Protokit app"
4. Click on "Launch Protokit app program (KitProg 3)
5. Setup UART console to 115200,8,N,1 to see light sensor data

Code Example Document
---------------------
To do 
-------------------------------------------------------------------------------
