#include "main.h"

#include <iostream>
#include <string>
#include <curl/curl.h>

extern shuye_t shuyestate;
//�˴�����һ�����⣬��Ҫshuyestate�еı���ֵ��ʾ��������д��file
void data_send(void)
{
    std::string node_id = "NODE-001";
    std::string data = "{\"droptime\":,\"humidity\":50.2,\"timestamp\":\"2023-04-01T12:00:00Z\"}";
    
    send_data_to_cloud(node_id, data);
    
  
}

//��װlibcurl: ��Ubuntu��Debian�ϣ�����ʹ���������װlibcurl��������
//sudo apt-get install libcurl4-openssl-dev
// �ص����������ڴ���libcurlд������ݣ�����򵥴�ӡ����
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// �������ݵ��ƶ˵ĺ���
void send_data_to_cloud(const std::string& node_id, const std::string& json_data) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // ����URL
        std::string url = "https://api.example.com/upload_node_data";
        
        // ����POST����
        std::string post_fields = "{\"node_id\":\"" + node_id + "\", \"data\":" + json_data + "}";
        
        // ��ʼ��curl����
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // ���ûص�����
        
        // ����һ��std::string��������Ӧ����
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        // ִ������
        res = curl_easy_perform(curl);
        
        // �����
        if(res == CURLE_OK) {
            std::cout << "���ݷ��ͳɹ�����������Ӧ��" << response << std::endl;
        } else {
            std::cerr << "���ݷ���ʧ�ܣ�������룺" << res << std::endl;
        }
        
        // ����
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

��δ������ȳ�ʼ��libcurl������Ȼ������Ŀ��URL��POST���ݣ���������һ���ص������������������Ӧ��
���ִ�����󲢼�����������ʵ���������URL�����ݽṹ���ǵ��ڱ���ʱ����libcurl�⣬
����ʹ��g++����ʱ���-lcurl��־��
*/
