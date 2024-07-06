#include "main.h"
#include "move.h"

extern data_rece_t data_rece;// 输入的数据，按你写的来
extern int move_mode;//是否跟随标志位
extern int speed_rece_x;
extern int speed_rece_w;
extern PID_Type_t pid_l,pid_r;//也可以在此处初次定义
extern float real_speed_l,real_speed_r;

speed_t speed_l,speed_r;
float k1,k2,d1,d2;
short l_current,r_current;

void move_set(void)
{
    if(move_mode==0)
    {
        speed_l.speed_all=0;
        speed_r.speed_all=0;
        motor_send(0,0);
    }
    else{
        speed_l.speed_all=speed_rece_x+speed_rece_w;
        speed_r.speed_all=speed_rece_x-speed_rece_w;
        pid_l.setpoint=k1*speed_l.speed_all+d1;
        pid_r.setpoint=k2*speed_r.speed_all+d2;
        l_current=PID_Calc(&pid_l,real_speed_l);
        r_current=PID_Calc(&pid_r,real_speed_r);
        l_current=LIMIT_MAX_MIN(l_current,MAX_CURRENT,MIN_CURRENT);//利用define宏定义，暂时未写
        r_current=LIMIT_MAX_MIN( r_current,MAX_CURRENT,MIN_CURRENT);
        motor_send(l_current,r_current);//两个电机可以同时发送
        //电机代码在此处不呈现
    }
}

void move_init(void)
{
    k1=0;
    k2=0;
    d1=0;
    d2=0;
    pid_l.P=0;
    pid_l.I=0;
    pid_l.d=0;
    pid_l.imax=0;
    pid_r.P=0;
    pid_r.I=0;
    pid_r.d=0;
    pid_r.imax=0;
    //所有数据都需要标定，使用最普通pid
}