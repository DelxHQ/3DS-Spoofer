#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>,
#include <sys/stat.h>

#define N 7
#define V1 1
#define V2 0
#define V3 2

#define COLUMN 11
#define ROW ((26 - N) / 2)

void refresh(int option, PrintConsole topScreen, char *menu[], int n) {
	consoleSelect(&topScreen);
	for (int i = 0; i < n; i++) {
		if (i == option) 
			printf("\x1b[%d;%dH> %s", ROW + i, COLUMN, menu[i]);
		else 
			printf("\x1b[%d;%dH  %s", ROW + i, COLUMN, menu[i]);
	}
}


int main() {
	gfxInitDefault(); 
	sdmcInit();
	//romfsInit();
	
	PrintConsole topScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleSelect(&topScreen);
	
	mkdir("sdmc:/luma", 0777);
	
	int option = 0;
	bool exit = false;
	char* menu[N] = {"Enable spoofer", "Exit to home menu"};
	
	printf("\x1b[%d;%dH\x1b[32m3DS firmware spoofer", ROW - 2, COLUMN, V1, V2, V3);
	refresh(option, topScreen, menu, N);
	consoleSelect(&topScreen);
	printf("\x1b[%d;%dHPress A to select an option.", ROW + N + 1, COLUMN);
	printf("\x1b[%d;%dHThis app support \x1b[31mLuma3DS >6.3\x1b[0m", ROW + N + 3, COLUMN);
	printf("\x1b[%d;%dHonly.", ROW + N + 4, COLUMN);

	while(aptMainLoop() && !exit) {
		gspWaitForVBlank();
		hidScanInput();
		
		if (hidKeysDown() & KEY_DUP) {
			if (option == 0) option = N - 1;
			else if (option > 0) option--;		
			
			refresh(option, topScreen, menu, N);
		}
    }
