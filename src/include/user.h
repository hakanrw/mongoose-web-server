#include <stdint.h>
#include <time.h>

struct user {
	uint32_t id;
	char* name;
	time_t reg_date;	
};

typedef struct user user_t; 
