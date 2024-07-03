import requests
import json



def read_shuye_from_file(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data

data = read_shuye_from_file('shuye_data.json')
#print(data)

def send_data_to_cloud(node_id, data):
    """
    向智云硬件服务平台发送节点数据
    :param node_id: 节点ID
    :param data: 要发送的数据（字典格式）
    """
    # 智云硬件服务平台的API URL，请根据实际情况替换
    api_url = "https://api.example.com/upload_node_data"
    
    # 准备要发送的数据，这里以JSON格式为例
    payload = {
        "node_id": node_id,
        "data": data
    }
    
    # 设置请求头，表明发送的是JSON格式的数据
    headers = {
        'Content-Type': 'application/json'
    }
    
    try:
        # 发送POST请求
        response = requests.post(api_url, data=json.dumps(payload), headers=headers)
        
        # 检查响应状态码
        if response.status_code == 200:
            print("数据发送成功")
            print("服务器响应:", response.text)
        else:
            print(f"数据发送失败，错误代码：{response.status_code}")
            print("错误详情:", response.text)
    except requests.exceptions.RequestException as e:
        print("网络请求错误:", e)

# 示例数据
node_id = "NODE-001"
data = {
    "temperature": 25.6,
    "humidity": 50.2,
    "timestamp": "2023-04-01T12:00:00Z"
}

# 调用函数发送数据
send_data_to_cloud(node_id, data)

##此示例将使用requests库来发送数据，请确保事先已安装此库（如果未安装，可以通过pip install requests命令安装）。

#这个示例假定智云硬件服务平台提供了一个API接口用于接收数据，具体URL和所需的数据格式需要根据实际情况调整。

#请注意，上述代码仅为示例，实际应用时需要根据智云硬件服务平台的具体API文档调整URL、请求参数及数据格式。此外，考虑到安全性，
# 如果平台支持HTTPS，并且有特定的身份验证机制（如API密钥、OAuth等），还需要在请求中正确添加相应的认证信息。
# ##