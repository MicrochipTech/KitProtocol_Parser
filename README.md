Kit Protocol Parser Library
====================================================

Introduction
------------------------
The Kit Protocol promotes flexibility for applications that need to communicate with Kits,
Test Boards, and “Talker” boards of various kinds. When the Kit Protocol is supported by the application
and the board, the interchangeability of boards is achieved.

The Kit Protocol transports the bytes for the Chip commands to the Kit. The Kit can then parse the
command and respond to it by either calling the Chip Library or responding with a Kit-Level response.

This code base implements an object-oriented C library for Kit Protocol Parser.
The family of devices supported currently are:

- [ATECC608A](http://www.microchip.com/ATECC608A)
- [ATECC508A](http://www.microchip.com/ATECC508A)
- [ATECC108A](http://www.microchip.com/ATECC108A)
- [ATSHA204A](http://www.microchip.com/ATSHA204A)

Prerequisite skills:
  - strong C programming and code reading
  - Knowledge of flashing microcontrollers with new code
  - Familiarity with Microchip CryptoAuth device functionality



Configuration
-----------
In order to properly configured the library there must be a header file in your
project named `kitprotocol_parser_config.h` at minimum this needs to contain defines for the
hal being used:

```
/* KitProtocol Parser Configuration file */
#ifndef KITPROTOCOL_PARSER_CONFIG_H_
#define KITPROTOCOL_PARSER_CONFIG_H_

/* Include HALS */
#define KIT_HAL_I2C       //!< For I2C interface
//#define KIT_HAL_SWI       //!< For SWI interface
//#define KIT_HAL_SPI       //!< For SPI interface
//#define KIT_HAL_SWI2     //!< For New SWI2 interface

/* Include maximum number of devices to discover */
#define MAX_DISCOVER_DEVICES        8

#endif // KITPROTOCOL_PARSER_CONFIG_H_
```

Host Device Support
-------------------------
Kitprotocol parser will run on a variety of platforms. 
For example:
- CryptoAuth Trust Platform board (or)
- ATSAMG55 Xplained pro

Release notes
-----------
 3.0.1
  - Bug fixed related to SWI string

 3.0.0
  - Initial release of Kit Protocol Parser Library


KitProtocol Parser Architecture
---------------------------------
The parser library is structured to support portability to
  - Multiple hardware/microcontroller platforms
  - Multiple chip communication protocols (I2C, SPI, UART & SWI)

Directory Structure:
  - kitprotocol_parser – contain host_interface, hal_interface and device_info source code
  - kitprotocol_parser/kit_protcol – primary kitprotocol source code
  - kitprotocol_parser/utilities/crc – crc calculation

There are two primary files in KitProtocol Parser Library:
  - Host (host_interface)
  - Device (hal_interface)

HOST INTERFACE file contain host_iface_init() which initialize host side interface related buffers,
their lengths, hardware init, send and receive apis.

Example showing how the HOST HAL methods are initialized in the interface instance without having
the HAL implementation bleed into the top layers.

![KitProtocol Parser Architecture](./docs/kitprotocol_parser_host_interface.PNG "KitProtocol Parser Host Interface" )

HAL INTERFACE file contain hal_iface_init() which initialize standard HAL with physical hardware interface API.

Example showing how the Device HAL methods are initialized in the interface instance without having
the HAL implementation bleed into the top layers.

![KitProtocol Parser Architecture](./docs/kitprotocol_parser_hal_interface.PNG "KitProtocol Parser Hal Interface" )

Currently, most of the testing has been performed on:
  - [CryptoAuth Trust Platform board-DM320118](https://www.microchip.com/developmenttools/productdetails/DM320118) (SAMD21E18A)

If you need an example of how to use a Kitprotocol parser, these hosts and tests are a good place to reference.

Using Git to Incorporate Kitprotocol_parser library as submodule
------------------------------------------------------------------
You can include this project in your own project under git

Using kitprotocol_parser as a git submodule, you can maintain your application separately from kitprotocol_parser.

If your project is already in git but you haven’t yet integrated kitprotocol_parser, change to the directory
where you want to put kitprotocol_parser.

```bash
git submodule add -b master <giturl to kitprotocol_parser>
```

This adds kitprotocol_parser library as a subdirectory and separate git repo within your own project.
Changes and commits to your project vs kitprotocol_parser will remain separated into each respective repository.

If there is a project you want to checkout that already incorporates kitprotocol_parser as a submodule
if you clone the repo that incorporates kitprotocol_parser, after cloning, you'll still need to fill out the
kitprotocol_parser submodule after cloning:

```bash
git submodule init
git submodule update –remote
cd kitprotocol_parser
git checkout master
```

Incorporating kitprotocol_parser in a project
-----------------------------------------------

1) Add below methods in main function

  ```
  main()
  {
      ...
      ...

      host_iface_init();

      kit_protocol_init();

      hardware_interface_discover();

      while(1)
      {
          kit_protocol_task(NULL);
      }
  }
  ```

For more information, please refer one of the example projects.
Notes: i)  Before doing kit protocol task, it is necessary to discover the CryptoAuth Devices attached to host
           and update the device info structure.
       ii) While running python (jupyter notebook), make sure that host is communicating with correct Vendor id
           and Product id device.

