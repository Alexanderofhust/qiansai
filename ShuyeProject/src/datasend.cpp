#include "main.h"

#include <iostream>
#include <string>
#include <curl/curl.h>

extern shuye_t shuyestate;
//此处遇到一个问题，需要shuyestate中的变量值表示出来才能写入file
void data_send(void)
{
    std::string node_id = "NODE-001";
    std::string data = "{\"droptime\":,\"humidity\":50.2,\"timestamp\":\"2023-04-01T12:00:00Z\"}";
    
    send_data_to_cloud(node_id, data);
    
  
}

//安装libcurl: 在Ubuntu或Debian上，可以使用以下命令安装libcurl开发包：
//sudo apt-get install libcurl4-openssl-dev
// 回调函数，用于处理libcurl写入的数据，这里简单打印出来
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// 发送数据到云端的函数
void send_data_to_cloud(const std::string& node_id, const std::string& json_data) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // 设置URL
        std::string url = "https://api.example.com/upload_node_data";
        
        // 设置POST数据
        std::string post_fields = "{\"node_id\":\"" + node_id + "\", \"data\":" + json_data + "}";
        
        // 初始化curl对象
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // 设置回调函数
        
        // 创建一个std::string来接收响应数据
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        // 执行请求
        res = curl_easy_perform(curl);
        
        // 检查结果
        if(res == CURLE_OK) {
            std::cout << "数据发送成功，服务器响应：" << response << std::endl;
        } else {
            std::cerr << "数据发送失败，错误代码：" << res << std::endl;
        }
        
        // 清理
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
}
/*
int main() {
    std::string node_id = "NODE-001";
    std::string data = "{\"temperature\":25.6,\"humidity\":50.2,\"timestamp\":\"2023-04-01T12:00:00Z\"}";
    
    send_data_to_cloud(node_id, data);
    
    return 0;
}

这段代码首先初始化libcurl环境，然后设置目标URL、POST数据，并定义了一个回调函数来处理服务器响应。
最后，执行请求并检查结果。请根据实际情况调整URL和数据结构。记得在编译时链接libcurl库，
例如使用g++编译时添加-lcurl标志。
*/
