#define CLEAR 1
#define RANDOM 2
#define MOUSE 3
#define KEYBOARD 4
#define RUN 5
#define SAVE 6
#define EXIT 7

int get_input_method(void);
void print_menu(WINDOW *menu_win, int hl);
