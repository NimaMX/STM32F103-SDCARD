# STM32F103-SDCARD
STM32F103 sdcard implementation with spi access. this repository contains hardware driver level file, Board Support Packages, Middleware and application layer test api. communication to sdcard is spi connection and we have one gpio output for detecting if sdcard is inserted or not. the needed explanation to use this library is concluded as comment on source code.

<img src="https://c.76.my/Malaysia/micro-sd-card-module-arduino-stm-enewground-1511-10-Enewground@15.jpg" />

In this repository , we have four working layer that we used them altogether. the layer are :

* First Layer : Hardware Driver Layer
The Driver Directory in source code contains some source code that we are using as hardware driver. this files contains basic function that we use to control hardwares such as initializing spi , read/write data to spi actions. in this project we also have gpio driver for spi chip-selection and sdcard input detection functionality.

* Second Layer : Middleware
The Middleware is an externaly added layer to include fatfs base functions and actions.

* Third Layer : Library 
The Third Layer is customized library to coordinate fatfs middleware sources with driver layer. becuase the fatfs function for performing the read/write action on sdcard need direct connection. so we should link theme with drivers , and we done it with Library Layer.

* Fourth Layer : BSP
This Layer is the board support package layer. in this layer we gather all of the work that we done in lower level an provide an logical , easy and end-user api to write/read on sdacard.

After using this layer , the system is ready to use sdcard Api easily.
