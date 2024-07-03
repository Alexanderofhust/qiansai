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
    ������Ӳ������ƽ̨���ͽڵ�����
    :param node_id: �ڵ�ID
    :param data: Ҫ���͵����ݣ��ֵ��ʽ��
    """
    # ����Ӳ������ƽ̨��API URL�������ʵ������滻
    api_url = "https://api.example.com/upload_node_data"
    
    # ׼��Ҫ���͵����ݣ�������JSON��ʽΪ��
    payload = {
        "node_id": node_id,
        "data": data
    }
    
    # ��������ͷ���������͵���JSON��ʽ������
    headers = {
        'Content-Type': 'application/json'
    }
    
    try:
        # ����POST����
        response = requests.post(api_url, data=json.dumps(payload), headers=headers)
        
        # �����Ӧ״̬��
        if response.status_code == 200:
            print("���ݷ��ͳɹ�")
            print("��������Ӧ:", response.text)
        else:
            print(f"���ݷ���ʧ�ܣ�������룺{response.status_code}")
            print("��������:", response.text)
    except requests.exceptions.RequestException as e:
        print("�����������:", e)

# ʾ������
node_id = "NODE-001"
data = {
    "temperature": 25.6,
    "humidity": 50.2,
    "timestamp": "2023-04-01T12:00:00Z"
}

# ���ú�����������
send_data_to_cloud(node_id, data)

##��ʾ����ʹ��requests�����������ݣ���ȷ�������Ѱ�װ�˿⣨���δ��װ������ͨ��pip install requests���װ����

#���ʾ���ٶ�����Ӳ������ƽ̨�ṩ��һ��API�ӿ����ڽ������ݣ�����URL����������ݸ�ʽ��Ҫ����ʵ�����������

#��ע�⣬���������Ϊʾ����ʵ��Ӧ��ʱ��Ҫ��������Ӳ������ƽ̨�ľ���API�ĵ�����URL��������������ݸ�ʽ�����⣬���ǵ���ȫ�ԣ�
# ���ƽ̨֧��HTTPS���������ض��������֤���ƣ���API��Կ��OAuth�ȣ�������Ҫ����������ȷ�����Ӧ����֤��Ϣ��
# ##