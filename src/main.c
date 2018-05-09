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


//BUBBLE_SORT_CREATE_STATIC_INSTANCE(my);



/*
 * case : 's' - sortowanie
 * case : 'r' - dodaj 10 elementow
 * case : 'd' - wyswietl tablice
 * case : 'a' - dodaj 1 element
 * case : 'n' - neguj, cofnij
 * case : 't' - akcecptuj, dalej
 *
 */
void show(void);

struct Bubble_sort bubbles;

int main(void)
{
  app_init();

  while(1) {
      if( 0 > app() ) {
	break;
      }
  }

  show();

  printf("\nEND OF PROGRAM");

  return EXIT_SUCCESS;
}

void show(void)
{
  printf("Number_of_elements left: %d\n", bubbles.bs_counter.no_elements_to_insert);
  printf("Number of last element: %d\n\n", bubbles.bs_counter.no_last_element);
}
