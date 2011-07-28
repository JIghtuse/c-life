#define ASCII       "\033(0" /* adding ASCII symbols mode */
#define NON_ASCII   "\033(B" /* usual mode */
#define HLINE       "q" /* horizontal line ASCII-code */
#define VLINE       "x" /* vertical line ASCII-code */
#define LU_CORNER   "l" /* left-up corner symbol */
#define RU_CORNER   "k" /* right-up corner symbol */
#define LD_CORNER   "m" /* left-down corner symbol */
#define RD_CORNER   "j" /* right-down corner symbol */

extern int bc_box(int, int, int, int);
