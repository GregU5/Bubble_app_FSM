/*
 * app.c
 *
 *  Created on: May 5, 2018
 *      Author: greg
 */
#include "app.h"

struct app g_app;
struct Bubble_sort my_bubbles;

static int32_t app_rand_nums (struct Bubble_sort *my_sort, uint32_t no_elements, uint32_t rand_max);
static int32_t app_add_num(struct Bubble_sort *my_sort);
static int32_t get_num(void);

int32_t
app_init(void)
{
  int32_t retval = 0;
  printf("Program do sortowania bablekowego.\n");
  g_app.state = STATE_INIT;
  g_app.last_state = 0;

  return retval;
}

int32_t
app_chose_func(struct Bubble_sort *my_sort)
{
  int32_t retval = 0;
  static uint8_t click = 0;

  char cmd = 0;
  scanf(" %c", &cmd);
  getchar();

  switch(cmd) {
    case 'r': {
      retval = ADD_TEN_NUMBERS;
      click = 0;
    }
    break;
    case 's': {
      retval = SORT;
      click = 0;
    }
    break;
    case 'a': {
      retval = ADD_ONE_NUMBER;
      click = 0;
    }
    break;
    case 'd': {
      retval = DISPLAY_ARRAY;
      click = 0;
    }
    break;
    case 'n': {
      retval = CANCEL_BTN;
      click = 0;
    }
    break;

    default: {
      retval = CHOSE_FUNC;
      printf("%c - nie rozpoznaje\n", cmd);
      click++;
      if (click > 2) {
	system("clear");
	click = 0;
	retval = SHOW_MENU;
      }
    }
    break;
  }

  return retval;
}

int32_t
app(void)
{
  int32_t retval = 0;

  switch(g_app.state) {
    case STATE_INIT: {
      int32_t is_init = bs_init(&my_bubbles, array_to_sort, SIZE);
      if(is_init < 0) {
	g_app.state = -1;
	printf("\n BUBBLE STRUCT INIT ERROR\n");
      }else {
	g_app.state = SHOW_MENU;
      }
    }
    break;
    case SHOW_MENU: {
      printf("\nMenu wyboru:\n"
	  "r - Dodaj 10 liczb losowych\n"
	  "a - Podaj jedna liczbe i dodaj do tablicy\n"
	  "s - Sortuj tablice\n"
	  "n - Neguj/Cofnij\n"
	  "d - Wyswietl tablice\n"
	  );

      printf("Naciśnienie 'n' zakończy działanie programu.\n");
      g_app.last_state = SHOW_MENU;
      g_app.state = CHOSE_FUNC;
    }
    break;
    case CHOSE_FUNC: {
      g_app.state = app_chose_func(&my_bubbles);
      g_app.last_state = CHOSE_FUNC;
    }
    break;
    case SORT: {
      if (sm_bubble_sort(&my_bubbles) == 0){
	g_app.state = SORT;
      }else {
	g_app.state = SHOW_MENU;
	g_app.last_state = SORT;
      }
    }
    break;
    case ADD_ONE_NUMBER: {
      int32_t check;
      check = app_add_num(&my_bubbles);
      if (check < 0) {
       g_app.state = ADD_NUM_ERROR;
      }else {
	if (check == 0) {
	  printf("Brak miejsca w tablicy!\n");
	}
	g_app.state = SHOW_MENU;
      }
      g_app.last_state = ADD_ONE_NUMBER;
    }
    break;
    case ADD_NUM_ERROR: {
      printf("Wprowadzono liczbe spoza zakresu lub nieodpowiedni znak.\n");
      g_app.state = SHOW_MENU;
      g_app.last_state = ADD_NUM_ERROR;
    }
    break;
    case ADD_TEN_NUMBERS: {
      int32_t check = app_rand_nums(&my_bubbles, 10, 999);
      printf("Dodano %d losowych liczb\n", check);
      if(check == 0) {
	  printf("Tablica jest pelna! Brak wolnych miejsc\n");
      }
      g_app.state = SHOW_MENU;
      g_app.last_state = ADD_TEN_NUMBERS;
    }
    break;
    case DISPLAY_ARRAY: {
      bs_show_array(&my_bubbles);
      g_app.state = SHOW_MENU;
      g_app.last_state = DISPLAY_ARRAY;
    }
    break;
    case CANCEL_BTN: {
      if(g_app.last_state == CHOSE_FUNC) {
	  g_app.state = END;
      }
      g_app.last_state = CANCEL_BTN;
    }
    break;
    case END:
      retval = -1;

    break;
  }

  return retval;
}

/*
 * function to add numbers to array to sort
 * *my_sort - struct of bubble_sort to sort
 *  no_elements - number of elements to be added to array
 *  rand_max - the upper limit of random number
 *
 *  return number of elements putted into array
 *  return -1 struct of bubble sort not inited or bad size of array
 *  return -2 no place to put new numbers
 */
int32_t
app_rand_nums(struct Bubble_sort *my_sort, uint32_t no_elements, uint32_t rand_max)
{
  int32_t retval = 0;

  uint32_t size;
  size = bs_get_array_size(my_sort);
  if ((no_elements > size) || (size  < 0)) {
    retval = -1; // number of elements are greater tan size of array or bubble struct is not inited
  }
  uint32_t free_elements;
  free_elements = bs_get_free(my_sort);

  if (no_elements > free_elements) {
    no_elements = no_elements - (no_elements - free_elements);
  }

  for(int i = 0; i < no_elements; i++) {
    int32_t tmp = (rand() % rand_max) + 1;
    bs_insert(my_sort,tmp);
  }

  return retval = no_elements;
}

/*
 * function add number by user to array
 * return value of inserted element
 * return -1 bad array size or bubble struct not inited
 * return -2 no place for new numbers
 */
int32_t
app_add_num(struct Bubble_sort *my_sort)
{
  int32_t retval = 0;
  int32_t num = get_num();

  if(num <= 0) {
    return retval = num;
  }

  return retval = bs_insert(my_sort, num);
}
/*
 * return number give by user from 1 to 1000
 * return -1 if number was out of the brackets
 */
int32_t
get_num(void)
{
  int32_t retval = 0;
  printf("Podaj dowolną cyfrę od 1 do 1000:\n");
  scanf("%d", &retval);

  if(retval > 0 && retval <= 1000) {
    return retval;
  }

  return retval = -2;
}

