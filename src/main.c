/*
 * 3DS Configuration Dumper
 * v0.1a, by drsn0w
 * main.c
 */

#include <3ds.h>
#include <stdio.h>
#include "cfgutables.h"

int main(int argc, char **argv) {

  //Initialize service
  gfxInitDefault();
  cfguInit();

  //Define placeholder values
  u8 language = 0;
  u8 region = 0;
  u8 model = 0;

  //Get system language
  CFGU_GetSystemLanguage(&language);

  //Get system region
  CFGU_SecureInfoGetRegion(&region);

  //Get system model
  CFGU_GetSystemModel(&model);

  //Initialize and setup bottom screen UI
  consoleInit(GFX_BOTTOM, NULL);
  printf("CONTROLS WILL GO HERE!\n");
  printf("Nothing to see here, press Start to exit\n");

  //Initialize and setup top screen information
  consoleInit(GFX_TOP, NULL);
  printf("3DS Configuration Dumper v0.1a by drsn0w\n");
  printf("In friendly mode for now!\n");
  printf("Console-Unique Hash: xxx\n");
  printf("Model: %s\n", CFGU_MODEL_TABLE[(int)model]);
  printf("System Region: %s\n", CFGU_REGION_TABLE[(int)region]);
  printf("System Language: %s\n", CFGU_LANGUAGE_TABLE[(int)language]);

  //Main loop
  while(aptMainLoop()) {
    hidScanInput();

    u32 kDown = hidKeysDown();
    if (kDown & KEY_START) break; //break to get back to wherever your 3DS wants to go at that moment ;-;

    //Flush and swap framebuffers
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
  }

  //Exit services
  cfguExit();
  gfxExit();
  return 0;
}
