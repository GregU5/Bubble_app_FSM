/*
 * app.h
 *
 *  Created on: May 5, 2018
 *      Author: greg
 */

#ifndef APP_H_
#define APP_H_

#include "bubble_sort.h"
#include <unistd.h>

#define SIZE 128
int32_t array_to_sort[SIZE];

enum {
  STATE_INIT = 1,
  SHOW_MENU,
  CHOSE_FUNC,
  SORT,
  ADD_ONE_NUMBER,
  ADD_TEN_NUMBERS,
  DISPLAY_ARRAY,
  ADD_NUM_ERROR,
  CANCEL_BTN,
  END
};

struct app {
  int32_t state;
  int32_t last_state;
};

int32_t app_init(void);
int32_t app(void);
int32_t chose_func(struct Bubble_sort *my_sort);



#endif /* APP_H_ */
