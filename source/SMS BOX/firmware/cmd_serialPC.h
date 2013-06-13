#ifndef __SERIALPC_CMD__
#define __SERIALPC_CMD__

#define BUFFER_DATA_LEN   (180+32)

//! general commands
#define CMD_HELLO             0x01        //! HELLO command
#define CMD_MODEM             0x02        //! MODEM command
#define CMD_ASC               0x03        //! ASC (Annother Sim Card) command. Command used for change the sim card
#define CMD_SONDA             0x04        //! SONDA command. This command is used for verify state of communication of SMS Box
#define CMD_STATUS            0x05        //! STATUS. Status of operation of SMS Box
//  #define ACK                   0x06
#define CMD_VERSION           0x07        //! firmware version

//! Log operations commands
#define CMD_GET_LOG           0x0A        //! Get the log

// device commands
#define CMD_SET_DEV_ST        0x0B        //! set the device state. For device information give a look in the device module
#define CMD_GET_DEV_ST        0x0C        //! get the device state.

//! boot loader comands
#define CMD_BOOTLOADER_UPLOAD_FW  0x0D        //! do the firmware upload (in a point of view of Host PC)
#define CMD_BOOTLOADER_GETCRC32   0x0E        //! get the CRC32 of the firmware peviously downloaded
#define CMD_BOOTLOADER_CHANGEFW   0x0F        //! Change the firmware

//!@
#define ACK                   0x06        //! Acknowledge
#define NACK                  0x15        //! not Acknowledge

// errors code for NACK
//---------------------------------
#define DONT_CONNECTED        0x01        
#define DONT_NOT_FUNC         0x02
#define NO_MORE_DATA          0x03
#define DEV_SET_STATE_ERROR   0xFF
//---------------------------------

#endif
