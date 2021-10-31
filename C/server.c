#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int rc = 0;

int main(void)
{
    void *context_pub = zmq_ctx_new();
    void *publisher = zmq_socket(context_pub, ZMQ_PUB);
    rc = zmq_bind(publisher, "tcp://*:5555");
    assert(rc == 0);

    void *context_sub = zmq_ctx_new();
    void *subscriber = zmq_socket(context_sub, ZMQ_SUB);
    rc = zmq_bind(subscriber, "tcp://*:5556");
    assert(rc == 0);

    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

    printf("Server initial complete!\n");
    while (1)
    {
        char buffer[6535];
        rc = zmq_recv(subscriber, buffer, 65535, 0);
        
        printf("Received %d \n",rc);
        printf("Received %s \n",buffer);

        zmq_send(publisher, buffer, rc, 0);
    }
    return 0;
}
