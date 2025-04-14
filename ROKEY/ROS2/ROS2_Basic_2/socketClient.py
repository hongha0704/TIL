import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip_address = input("ip adress를 입력하시오: ")

client_socket.connect((ip_address, 8080))
print('서버에 연결되었습니다.')

client_socket.sendall(b'Hello, Server!')
data = client_socket.recv(1024)
print(f'서버로부터 받은 데이터: {data.decode()}')

client_socket.close()

