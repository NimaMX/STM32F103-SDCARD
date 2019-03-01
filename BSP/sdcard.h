/*
		sdcard.h file is Board Support Package.
    Copyright (C) 2018 Nima Mohammadi
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __SDCARD_H
#define __SDCARD_H

#include "stm32f10x.h"
#include "../lib/sdlib/fatfs.h"
#include "stdio.h"
#include "../Driver/spi.h"
#include "../Driver/gpio.h"

#define SDCARD_ERROR_OPEN_NORMAL	 		0x1
#define SDCARD_ERROR_OPEN_WRITE_MODE	0x2
#define SDCARD_ERROR_OPEN_READ_MODE	 	0x3
#define SDCARD_ERROR_CLOSE 						0x4
#define SDCARD_ERROR_WRITE 						0x5
#define SDCARD_ERROR_READ  						0x6
#define SDCARD_ERROR_MOUNT 						0x7
#define SDCARD_ERROR_UNMOUNT 					0x8
#define SDCARD_ERROR_READ_SIZE 				0x9
#define SDCARD_ERROR_CAPACITY 				0x10

#define SDCARD_MOUNTED 								0x01
#define SDCARD_NOT_MOUNTED 						0x00
#define SDCARD_UNMOUNTED 							0x01
#define SDCARD_NOT_UNMOUNTED 					0x00

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

		READ_FILE = 0 ,
		WRITE_FILE ,
		READ_WRITE_FILE,

} openType_t;

typedef enum {

		FILE_EXSITS ,
		FILE_NOT_EXISTS

} file_state_t;

typedef struct {

		uint32_t totalsize;
		uint32_t freesize;
		uint8_t percent;

} storage_info_t;


void InitSdcard(void);
//
void _mountSdcard(void);
void _unmountSdcard(void);
//
void _writeString(char *str , FIL *fil);
void _readString(char *buffer , size_t read_size , FIL *fil);
//
void _openfile(char *file_name , openType_t type , FIL *fil);
void _closefile(FIL *fil);
//
void clearBuffer(void);
void insertBuffer(char *data);
//
void _makeDirectory(char *dir_name);
//
file_state_t getFileState(char *file);
storage_info_t getSpaceInfo();

void sdcardErrorHandle(uint8_t error_code , char *error_message);
//
void SdcardEjected(void);
void SdcardInserted(void);
void SdcardWriteAction(char *file_name , char *buffer);


#ifdef __cplusplus
}
#endif

#endif
