#include "main.h"
#include "move.h"

extern data_rece_t data_rece;// ��������ݣ�����д����
extern int move_mode;//�Ƿ�����־λ
extern int speed_rece_x;
extern int speed_rece_w;
extern PID_Type_t pid_l,pid_r;//Ҳ�����ڴ˴����ζ���
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
        l_current=LIMIT_MAX_MIN(l_current,MAX_CURRENT,MIN_CURRENT);//����define�궨�壬��ʱδд
        r_current=LIMIT_MAX_MIN( r_current,MAX_CURRENT,MIN_CURRENT);
        motor_send(l_current,r_current);//�����������ͬʱ����
        //��������ڴ˴�������
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
    //�������ݶ���Ҫ�궨��ʹ������ͨpid
}