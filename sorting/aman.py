import socket
 
HOST = '127.0.0.1'
PORT = 8000

socket_instance = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_instance.bind(HOST, PORT)
socket_instance.listen(1)

print(f"listining on port {PORT}")
while True:
    connecton,adress = socket_instance.accept()
    
    data = connection.recv(1024) 
    print(data.decode('utf-8'))
    



















