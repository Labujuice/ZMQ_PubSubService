import sys
import time
import zmq

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('python3 zmq_PubSubServer [PubPort] [SubPort]')
        sys.exit()
    print('Input ports:')
    print("Server Publish port = " + sys.argv[1])
    print("Server Subscribe port = " + sys.argv[2])


context_PUB = zmq.Context()
socket_pub = context_PUB.socket(zmq.PUB)
socket_pub.bind("tcp://*:" + sys.argv[1])

context_SUB = zmq.Context()
socket_sub = context_SUB.socket(zmq.SUB)
socket_sub.bind("tcp://*:" + sys.argv[2])
socket_sub.setsockopt(zmq.SUBSCRIBE, b'')

print('====================================')
print('Server starts!')
print("Client Publish port = " + sys.argv[2])
print("Client Subscribe port = " + sys.argv[1])
while True:
    response = socket_sub.recv()
    socket_pub.send(response)
