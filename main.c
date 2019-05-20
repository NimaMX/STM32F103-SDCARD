#inlcude "../BSP/sdcard.h"

int main(void)
{
		InitSdcard();
		SdcardWriteAction("test.txt" , "Hello \r\n");
		while(1);
}
