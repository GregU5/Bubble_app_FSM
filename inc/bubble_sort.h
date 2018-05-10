/*
 * bubble_sort.h
 *
 *  Created on: Apr 29, 2018
 *      Author: greg
 */

#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct bubble_counters {
  uint32_t no_free_elements;
  uint32_t idx;
  uint32_t last_idx;
  uint32_t swap_count;			// count of swap in array
  uint32_t i,j;				// loop counters
  int32_t state;
};

struct Bubble_sort {
   uint32_t size;			//size of array
   int32_t *tab;			// pointer to array to sort
   uint32_t is_sorted;			// check if array were sorted, is_sorted = 0 <- not sorted, is_sorted = 1 <- sorted
   uint32_t is_init;			// 1 - init, 0 - not inited
   struct bubble_counters bs_counter;	//
};

int32_t bs_init (struct Bubble_sort *my_sort, int32_t *data, uint32_t size);
int32_t bs_is_init(struct Bubble_sort *my_sort);
int32_t sm_bubble_sort (struct Bubble_sort *my_sort);

int32_t bs_insert(struct Bubble_sort *my_sort, int32_t new_var);

uint32_t bs_get_free(struct Bubble_sort *my_sort);
uint32_t bs_get_array_size(struct Bubble_sort *my_sort);
uint32_t bs_get_lst_idx(struct Bubble_sort *my_sort);

void bs_show_array (struct Bubble_sort *my_sort);

#endif /* BUBBLE_SORT_H_ */
