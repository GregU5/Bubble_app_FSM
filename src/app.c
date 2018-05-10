/*
 * app.c
 *
 *  Created on: May 5, 2018
 *      Author: greg
 */
#include "app.h"

struct app g_app_values;
struct Bubble_sort my_bubbles;

static void show_array(struct Bubble_sort *my_sort);

int32_t
app_init(void)
{
  int32_t retval = 0;
  printf("Program do sortowania bablekowego.\n");
  g_app_values.state = STATE_INIT;
  g_app_values.last_state = 0;

  return retval;
}

int32_t
app(void)
{
  int32_t retval = 0;

  switch(g_app_values.state) {
    case STATE_INIT: {
      int32_t is_init = bubble_sort_init(&my_bubbles, array_to_sort, SIZE);
      if(is_init < 0) {
	g_app_values.state = -1;
	printf("\n BUBBLE STRUCT INIT ERROR\n");
      }else {
	g_app_values.state = SHOW_MENU;
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
	g_app_values.last_state = SHOW_MENU;
	g_app_values.state = CHOSE_FUNC;
    }
    break;
    case CHOSE_FUNC: {
      g_app_values.state = chose_func(&my_bubbles);
      g_app_values.last_state = CHOSE_FUNC;
    }
    break;
    case SORT: {
      if( sm_bubble_sort(&my_bubbles) == 0){
	g_app_values.state = SORT;
      }else {
	g_app_values.state = SHOW_MENU;
	g_app_values.last_state = SORT;
      }
    }
    break;
    case ADD_ONE_NUMBER: {

      printf("Podaj dowolną cyfrę od 1 do 1000:\n");
      int32_t num = 0;
      scanf("%d", &num);
      if (num > 0 && num <= 1000) {
	bs_add_num(&my_bubbles, num);
	printf("Dodano %d do ostatniego elementu tablicy.\n", num);
	g_app_values.state = SHOW_MENU;
      }else {
	  g_app_values.state = ADD_NUM_ERROR;
      }
      g_app_values.last_state = ADD_ONE_NUMBER;
    }
    break;
    case ADD_NUM_ERROR: {
      printf("Wprowadzono liczbe spoza zakresu lub nieodpowiedni znak.\n");
      g_app_values.state = SHOW_MENU;
      g_app_values.last_state = ADD_NUM_ERROR;

    }
    break;
    case ADD_TEN_NUMBERS: {
      printf("Dodano %d losowych liczb\n", bs_rand_num(&my_bubbles, 10, 999));
      g_app_values.state = SHOW_MENU;
      g_app_values.last_state = ADD_TEN_NUMBERS;
    }
    break;
    case DISPLAY_ARRAY: {
      show_array(&my_bubbles);
      g_app_values.state = SHOW_MENU;
      g_app_values.last_state = DISPLAY_ARRAY;
    }
    break;
    case CANCEL_BTN: {
      //if(g_app_values.last_state == )
      if(g_app_values.last_state == CHOSE_FUNC) {
	  g_app_values.state = END;
      }
      g_app_values.last_state = CANCEL_BTN;
    }
    break;
    case END:
      retval = -1;

    break;
  }

  return retval;
}

int32_t
chose_func(struct Bubble_sort *my_sort)
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

static void
show_array(struct Bubble_sort *my_sort)
{
  if (my_sort->bs_counter.no_last_element == 0) {
    printf("TABLICA JEST PUSTA!\n");
  }
  for(int i = 0; i < my_sort->bs_counter.no_last_element; i++) {
      printf("tablica[%d] = %d\n", i, my_sort->tab[i]);
  }
  printf("Number of last element: %d\n", my_sort->bs_counter.no_last_element);
  printf("Number of elements to insert: %d\n", my_sort->bs_counter.no_elements_to_insert);

}
