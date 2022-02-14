// This must be a power of 2!
#define BUFFER_SIZE 8
#define MAX_ITEMS (BUFFER_SIZE-1)

extern int my_filter[BUFFER_SIZE];
extern int readIdx;
extern int writeIdx;

int filter_len();
void filter_add(int val);
int filter_get_average();
