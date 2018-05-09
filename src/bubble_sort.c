/*
 * bubble_sort.c
 *
 *  Created on: Apr 29, 2018
 *      Author: greg
 */

#include "bubble_sort.h"

static void swap_elements(int32_t *tab1, int32_t *tab2);


enum {
    INIT,
    BIG_FOR,
    LITTLE_FOR,
    END_SORT
};

/* return 1 bubble sort struct already inited ( no need to init )
 * return 0 bubble sort init
 */
int32_t
bubble_sort_init(struct Bubble_sort *my_sort, int32_t *data, uint32_t size)
{
  int32_t retval = -1;
  if ( my_sort->is_init == 1) {
    return retval = 1;
  }

//  int test = sizeof(struct Bubble_sort);

  if ( (my_sort != NULL) && (size != 0)) {
    my_sort->size = size;
    my_sort->tab = data;
    my_sort->is_sorted = 0;

    my_sort->bs_counter.no_last_element = 0;
    my_sort->bs_counter.no_elements_to_insert = 128;
    my_sort->bs_counter.i = 0; //for BIG_FOR licznik przejść
    my_sort->bs_counter.j = 1; //for LITTLE_FOR licznik elementów
    my_sort->bs_counter.swap_count = 0;

    my_sort->is_init = 1;
    my_sort->bs_counter.state = BIG_FOR;

    retval = 0;
  }

  return retval;
}

/*
 * return -1 bubble sort struct not inited
 * return 1 sorted, still empty space to be insert
 * return 2 no elements to sort
 *
 */
int32_t sm_bubble_sort(struct Bubble_sort *my_sort) {

  int32_t retval = 0;
  uint32_t number_of_last_element = my_sort->bs_counter.no_last_element;

  if (my_sort->is_init != 1) {
      return retval = -1;
  }

  if (my_sort->is_sorted != 0) {

    if ( (number_of_last_element == my_sort->size) ) {
      return retval = 2;
    }
    my_sort->is_sorted = 0;
  }

  uint32_t b_state = my_sort->bs_counter.state;
  uint32_t i = my_sort->bs_counter.i;
  uint32_t j = my_sort->bs_counter.j;

  switch(b_state) {
    case BIG_FOR: {
      my_sort->bs_counter.swap_count = 0;
      b_state = (i > number_of_last_element) ? END_SORT : LITTLE_FOR;
    }
    break;
    case LITTLE_FOR: {
      if (my_sort->tab[j-1] > my_sort->tab[j]) {
	swap_elements(&my_sort->tab[j-1], &my_sort->tab[j]);
	my_sort->bs_counter.swap_count++;
      }

      j++;
      if (j > number_of_last_element - 1) {
	j = 1;
	i++;
	if (my_sort->bs_counter.swap_count == 0) {
	    b_state = END_SORT;
	}
	my_sort->bs_counter.swap_count = 0;
      }
     }
     break;
    case END_SORT: {
      my_sort->is_sorted = 1;
      printf("\nEnd of bubble sorting\n");
      b_state = BIG_FOR;
      i = 0;
      j = 1;
      retval = 1;

//      if (number_of_last_element == my_sort->size) {
//	  retval = 2;
//      }

    }
  }

  my_sort->bs_counter.state = b_state; //zapisanie aktualnego stanu do struktury maszyny
  my_sort->bs_counter.i = i;
  my_sort->bs_counter.j = j;
  return retval;
}

/*
 * funkcja dodajaca n wylosowanych liczby do tablicy
 * argument my_sort, przekazanie wskaznika na strukture
 * argument no_elements -> ilość liczb do dodania
 * argument rand_max -> losuj liczbę od 1 do rand_max
 */
int32_t
bs_rand_num(struct Bubble_sort *my_sort, uint32_t no_elements, uint32_t rand_max)
{
  int32_t retval = 0;

  if (my_sort->is_init == 0) {
    return retval = -1;
  }
  if (no_elements > my_sort->size) {
    return retval = -1; //bledne parametry funkcji
  }
  if (no_elements > my_sort->bs_counter.no_elements_to_insert) {
    printf("\nremoved elements : %d\n", no_elements - my_sort->bs_counter.no_elements_to_insert);
    no_elements = no_elements - (no_elements - my_sort->bs_counter.no_elements_to_insert);

  }

  uint32_t last_index = my_sort->bs_counter.no_last_element;

  int i;
  for(i = 0; i < no_elements; i++ ) {
    my_sort->tab[last_index] = (rand() % rand_max) + 1;
    last_index++;
  }

  my_sort->bs_counter.no_last_element = last_index;
  my_sort->bs_counter.no_elements_to_insert-= no_elements;
  if(!no_elements) {
      printf("Tablica jest pelna. Nie można dodac liczb!\n");
  }

  return retval = no_elements;
}

int32_t
bs_add_num(struct Bubble_sort *my_sort, int32_t new_var)
{
  int32_t retval = 0;
  if (my_sort->is_init != 1) {
      return retval - 1;
  }

  uint32_t no_last_element = my_sort->bs_counter.no_last_element;
  if (no_last_element > my_sort->size) {
    printf("\nBrak miejsca!\n");
    return retval = -1;
  }
  uint32_t array_index = no_last_element;

  my_sort->tab[array_index] =  new_var;
  my_sort->bs_counter.no_last_element = ++no_last_element;

  my_sort->bs_counter.no_elements_to_insert = my_sort->size - no_last_element;

  return retval;
}

void
swap_elements(int32_t *tab1, int32_t *tab2)
{
  int32_t tmp;
  tmp = *tab1;
  *tab1 = *tab2;
  *tab2 = tmp;
}

