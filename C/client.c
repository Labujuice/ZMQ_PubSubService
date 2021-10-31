
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

// 子執行緒函數
void *PubThread(void *data)
{
    char *str = (char *)data; // 取得輸入資料

    void *context_pub = zmq_ctx_new();
    void *publisher = zmq_socket(context_pub, ZMQ_PUB);
    int rc = zmq_connect(publisher, "tcp://localhost:5556");
    assert(rc == 0);

    printf("PubThread initial complete!\n");

    uint32_t cnt = 0;
    while (1)
    {
        char buffer[6535];
        int len = sprintf(buffer, "PubThread: %d\n", cnt);
        zmq_send(publisher, buffer, len, 0);
        printf("%s, %s\n", str, buffer); // 每秒輸出文字
        sleep(1);
        cnt++;
    }
    pthread_exit(NULL); // 離開子執行緒
}

void *SubThread(void *data)
{
    char *str = (char *)data; // 取得輸入資料

    void *context_sub = zmq_ctx_new();
    void *subscriber = zmq_socket(context_sub, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "tcp://localhost:5555");
    assert(rc == 0);

    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

    printf("SubThread initial complete!\n");

    while (1)
    {
        char buffer[6535];
        rc = zmq_recv(subscriber, buffer, 65535, 0);

        printf("%s Received %d bytes, %s \n", str, rc, buffer);
    }
    pthread_exit(NULL); // 離開子執行緒
}

// 主程式
int main()
{
    pthread_t t_Sub, t_Pub;                         // 宣告 pthread 變數
    pthread_create(&t_Pub, NULL, PubThread, "PUB"); // 建立子執行緒
    pthread_create(&t_Sub, NULL, SubThread, "SUB"); // 建立子執行緒

    pthread_join(t_Pub, NULL); // 等待子執行緒執行完成
    pthread_join(t_Sub, NULL); // 等待子執行緒執行完成
    return 0;
}