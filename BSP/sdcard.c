/*
		sdcard.c file is Board Support Package.
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

#include "sdcard.h"

FATFS fatfs;
FATFS *pfatfs;
// state Holders
uint8_t state_mount = 0;
uint8_t state_unmount = 0;
//

#define MAX_BUFFER 512
char Buffer[MAX_BUFFER];

void clearBuffer(void)
{
	 for(int s = 0; s <= MAX_BUFFER; s++)
			Buffer[s] = (char) 0;
}

void insertBuffer(char *data)
{
	 sprintf(Buffer , "%s" , data);
}

void InitSdcard(void)
{
		initGpio();
		initSpi();
		MX_FATFS_Init();
}

void _mountSdcard(void)
{

	if(state_mount == SDCARD_MOUNTED)
			return;
	else
	{
			if(f_mount(&fatfs , "" , 0) != FR_OK)
			{
				sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to mount sdcard");
				state_mount = SDCARD_NOT_MOUNTED;
			}
			else
			{
				state_mount = SDCARD_MOUNTED;
				state_unmount = SDCARD_NOT_UNMOUNTED;
			}
	}
}

void _unmountSdcard(void)
{

	if(state_unmount == SDCARD_UNMOUNTED)
			return;
	else
	{
			if(f_mount(NULL , "" , 1) != FR_OK)
			{
				sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to unmount sdcard");
				state_unmount = SDCARD_NOT_UNMOUNTED;
			}
			else
			{
				state_unmount = SDCARD_UNMOUNTED;
				state_mount = SDCARD_NOT_MOUNTED;
			}
	}
}

void _writeString(char *str , FIL *fil)
{
		f_puts(str , fil);
}

void _readString(char *buffer , size_t read_size , FIL *fil)
{

}

void _openfile(char *file_name , openType_t type , FIL *fil)
{

		if(type == READ_WRITE_FILE)
		{

				if(f_open(fil , file_name , FA_OPEN_ALWAYS | FA_READ | FA_WRITE))
					sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to open -R/W file");

		}
		else if(type == READ_FILE) {

			if(f_open(fil , file_name , FA_READ))
				sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to open -R file");
		}
		else if(type == WRITE_FILE)
		{
				if(f_open(fil , file_name , FA_OPEN_ALWAYS | FA_WRITE))
					sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to open -W file");
		}
		else return;
}

void _closefile(FIL *fil)
{
	 if(f_close(fil) != FR_OK)
		 sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to close file");
}

storage_info_t getSpaceInfo()
{
	 storage_info_t info;
	 DWORD fre_clus;
	 //
	 if(f_getfree("" , &fre_clus , &pfatfs) != FR_OK)
		 sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to get space info");

	 info.totalsize = (uint32_t)((pfatfs->n_fatent - 2) * pfatfs->csize * 0.5);
	 info.freesize = (uint32_t)(fre_clus * pfatfs->csize * 0.5);

	 if(info.freesize < 1)
		 sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Low space in memory");

	 return info;
}

void _makeDirectory(char *dir_name)
{
		_mountSdcard();

		if(f_mkdir(dir_name) != FR_OK)
		 sdcardErrorHandle(SDCARD_ERROR_MOUNT , "Failed to get space info");

		_unmountSdcard();
}

void sdcardErrorHandle(uint8_t error_code , char *error_message)
{
		// Handle Errors
}

file_state_t getFileState(char *file)
{
		file_state_t file_state;
		FRESULT fr;
		FILINFO fno;

		fr = f_stat(file , &fno);

		if(fr == FR_OK)
			file_state = FILE_EXSITS;
		else
			file_state = FILE_NOT_EXISTS;

		return file_state;
}

void SdcardWriteAction(char *file_name , char *data)
{
		FIL fil;
		FRESULT fr;

		clearBuffer();
		insertBuffer(data);

		_mountSdcard();
		_openfile(file_name , WRITE_FILE , &fil);

		fr = f_lseek(&fil , f_size(&fil));
		if(fr != FR_OK)
			return;

		_writeString(Buffer , &fil);
		_closefile(&fil);
		_unmountSdcard();
}
