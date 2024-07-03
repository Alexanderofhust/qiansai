#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct
{
    /* data */
    int droptime;
    char existing;
    char dropping;
    char dropped;
    char mode;
}shuye_t;

/*void mydetectQRcode1(void);
void move_cal(const vector<Point>& xpoints5);
void xspeedcal(int xdistance);
void wspeedcal(int xcenterX);*/
int navi_cal(void);
void shuye_config(void);
int drop_detect(int argc, char **argv);
void data_send(void);
#endif
