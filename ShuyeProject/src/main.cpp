#include <stdio.h>
#include<opencv2/opencv.hpp>
#include "main.h"


using namespace std;
using namespace cv;

int my_error=0;
shuye_t shuye_state;
int argc=5;
char *argc;

int main()
{
    shuye_config();
    while (1)
    {
        /* code */
        drop_detect();
        navi_cal();
        data_send();//需要配置参数
        write_shuye_to_file(shuye_state, "shuye_data.json");
    return 0;
        if(my_error==1)return 0;
    }
    
    return 0;
}

void shuye_config(void)
{
    *argc=[];
    system("color F0");
	 VideoCapture cap(1); // 摄像头索引通常是0或1，根据实际情况调整

    if(!cap.isOpened()) {
        cerr << "Error opening camera." << endl;
        return -1;
    }
}

void write_shuye_to_file(shuye_t s, const char* filename) {
    json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "droptime", json_object_new_int(s.droptime));
    json_object_object_add(jobj, "existing", json_object_new_double(s.existing));
    json_object_object_add(jobj, "dropping", json_object_new_double(s.dropping));
    json_object_object_add(jobj, "dropped", json_object_new_double(s.dropped));
    json_object_object_add(jobj, "mode", json_object_new_double(s.mode));

    FILE *fp = fopen(filename, "w");
    if (fp) {
        fprintf(fp, "%s", json_object_to_json_string(jobj));
        fclose(fp);
    }
    json_object_put(jobj);
}




