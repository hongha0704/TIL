import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip_address = '127.0.0.1'

client_socket.connect((ip_address, 8080))
print('서버에 연결되었습니다.')

with open('C:/Users/ASUS/Desktop/Study/ROKEY/ROS2/ROS2_Basic_2/send_file.txt', 'rb') as f:
    print('파일 전송 중...')
    while True:
        data = f.read(1024)
        if not data:
            break
        client_socket.sendall(data)
print('파일 전송 완료.')

client_socket.close()

