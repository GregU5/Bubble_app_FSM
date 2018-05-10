/*
 ============================================================================
 Name        : bubbles_sortFSM.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include "app.h"
#include <unistd.h>

/*
 * case : 's' - sortowanie
 * case : 'r' - dodaj 10 elementow
 * case : 'd' - wyswietl tablice
 * case : 'a' - dodaj 1 element
 * case : 'n' - neguj, cofnij
 * case : 't' - akcecptuj, dalej
 *
 */

int main(void)
{
  app_init();

  while(1) {
    if (app() < 0) {
      break;
    }
  }

  printf("\nEND OF PROGRAM");

  return EXIT_SUCCESS;
}
