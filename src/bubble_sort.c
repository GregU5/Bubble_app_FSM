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
 * return 0 bubble sort init success
 */
int32_t
bs_init(struct Bubble_sort *my_sort, int32_t *data, uint32_t size)
{
  int32_t retval = -1;
  if ( my_sort->is_init == 1) {
    return retval = 1;
  }

  if ( (my_sort != NULL) && (size != 0)) {
    my_sort->size = size;
    my_sort->tab = data;
    my_sort->is_sorted = 0;

    my_sort->bs_counter.idx = 0;
    my_sort->bs_counter.no_free_elements = 128;
    my_sort->bs_counter.i = 0; //for BIG_FOR licznik przejść
    my_sort->bs_counter.j = 1; //for LITTLE_FOR licznik elementów
    my_sort->bs_counter.swap_count = 0;

    //my_sort->bs_counter.last_idx = 0;

    my_sort->is_init = 1;
    my_sort->bs_counter.state = BIG_FOR;

    retval = 0;
  }

  return retval;
}

/*
 * return 1 is bubble struct is inited
 * return -1 is not inited
 */
int32_t
bs_is_init(struct Bubble_sort *my_sort)
{
  int32_t retval;
  if (my_sort->is_init > 0) {
    retval = 1;
  }else {
    retval = -1;
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
  uint32_t number_of_last_element = my_sort->bs_counter.idx;

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
    }
  }

  my_sort->bs_counter.state = b_state;
  my_sort->bs_counter.i = i;
  my_sort->bs_counter.j = j;
  return retval;
}

/*
 * return -1 not init
 * return  number of elements
 */
int32_t
bs_insert(struct Bubble_sort *my_sort, int32_t new_var)
{
  int32_t retval;

  if(bs_is_init(my_sort) < 0) {
    return retval = -1;
  }
  if(my_sort->bs_counter.no_free_elements == 0) {
    return retval = 0;
  }

  uint32_t idx = my_sort->bs_counter.idx;
  my_sort->tab[idx] = new_var;

  my_sort->bs_counter.no_free_elements--;
  idx++;
  my_sort->bs_counter.idx = idx;

  return retval = idx;
}

/*
 * return free elements
 * return -1 if struct not init
 */
uint32_t
bs_get_free(struct Bubble_sort *my_sort)
{
  uint32_t retval;

  retval = bs_is_init(my_sort);
  if (retval > 0) {
    retval = my_sort->bs_counter.no_free_elements;
  }
  return retval;
}
/* return size of the array */
uint32_t
bs_get_array_size(struct Bubble_sort *my_sort)
{
  uint32_t retval;

  retval = bs_is_init(my_sort);
  if (retval > 0) {
    retval = my_sort->size;
  }
  return retval;
}

/*
 *function return number of last idx from array
 */
uint32_t
bs_get_lst_idx(struct Bubble_sort *my_sort)
{
  uint32_t retval = 0;

  retval = bs_is_init(my_sort);
  if (retval > 0) {
    retval = my_sort->bs_counter.idx;
  }
  return retval;
}

/* fuction to update counter of free elements
 * return 0 updated done
 * return -1 fail
 *
 *  */
uint32_t
bs_update_free(struct Bubble_sort *my_sort, uint32_t update_var)
{
  uint32_t retval = 0;
  retval = bs_is_init(my_sort);
  if(retval > 0) {
      my_sort->bs_counter.no_free_elements = update_var;
  }
  return retval;
}

/*
 * function to update last index of array from bubble sort
 * return 0 update done
 * return -1 fail
 */
int32_t
bs_update_lst_idx(struct Bubble_sort *my_sort, uint32_t update_var)
{
  int32_t retval = 0;
  retval = bs_is_init(my_sort);
  if(retval > 0) {
      my_sort->bs_counter.idx = update_var;
  }
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

void
bs_show_array(struct Bubble_sort *my_sort)
{
  if (my_sort->bs_counter.idx == 0) {
    printf("TABLICA JEST PUSTA!\n");
  }
  for(int i = 0; i < my_sort->bs_counter.idx; i++) {
      printf("tablica[%d] = %d\n", i, my_sort->tab[i]);
  }
  printf("Number of last element: %d\n", my_sort->bs_counter.idx);
  printf("Number of elements to insert: %d\n", my_sort->bs_counter.no_free_elements);
}
