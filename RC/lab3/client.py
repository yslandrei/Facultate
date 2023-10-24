import socket
import struct

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('172.30.0.4', 53325)
c.connect(server_address)

ch = input("character = ")
string = input("string = ")

len_string = len(string).to_bytes(2, byteorder='big')

c.send(ch.encode())
c.send(len_string)
c.send(string.encode())

len_pos_list = struct.unpack('!H', c.recv(2))[0]

pos_list_bytes = c.recv(2 * len_pos_list)
pos_list = struct.unpack(f'!{len_pos_list}H', pos_list_bytes)

print("Aparitile sunt:", end=" ")
for pos in pos_list:
    print(pos, end=" ")
c.close()
