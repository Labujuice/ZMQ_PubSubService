#
# this is an example for PubSub Cient scenario 
#

import zmq
import time
import threading

def pub_job():
    pub_context = zmq.Context()

    #  Socket to talk to server
    print("PUB: Connecting to the pubsub server…")
    pub_socket = pub_context.socket(zmq.PUB)
    pub_socket.connect("tcp://localhost:5556")

    a=0
    while True:
        pub_socket.send(b"A:%d"%a)
        a += 1
        time.sleep(1)


def sub_job():
    sub_context = zmq.Context()

    #  Socket to talk to server
    print("SUB: Connecting to the pubsub server…")
    sub_socket = sub_context.socket(zmq.SUB)
    sub_socket.connect("tcp://localhost:5555")
    sub_socket.setsockopt(zmq.SUBSCRIBE,b'') 

    while True:
        response = sub_socket.recv();
        print("received: %s" % response);


publishThread = threading.Thread(target=pub_job)
subscribeThread = threading.Thread(target=sub_job)

publishThread.start()
subscribeThread.start()
