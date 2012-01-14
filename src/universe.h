#define LIFE 1
#define EMPTY 0
#define SYMBOL '#'

#define NBORN 3
#define NMIN 2
#define NMAX 3

typedef unsigned short int *cell;

void clear_universe(cell c);
void keyboard_init(cell c);
void mouse_init(cell c);
void rand_universe(cell c);
void update_universe(cell c, cell newc);
void print_universe(cell c);

void save_universe(cell c);
