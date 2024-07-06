#ifndef __MOVE_H__
#define __MOVE_H__

typedef struct
{
    /* data */
    short speedx;
    short speedw;
    short speed_all;
}speed_t;

void move_set(void);
void move_init(void);


#endif
