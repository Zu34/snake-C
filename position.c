#include "position.h"
#define MAX_LEN 1000 
#define MAX_OBSTACLES 1000

static Position snake1[MAX_LEN];
static int head1, tail1;

static Position snake2[MAX_LEN];
static int head2, tail2;

static Position apple;
static Position obstacles[MAX_OBSTACLES];
static int num_obstacles;
