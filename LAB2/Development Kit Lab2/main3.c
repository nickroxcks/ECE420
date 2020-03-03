//one read lock and one write lock on entire array
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "common.h"
#include "timer.h"

int array_size;
int server_port;
char *server_ipadress;
char **server_array;
double array_of_times[COM_NUM_REQUEST];  //to store time for each request
int index_time = 0;

pthread_t threads_id[COM_NUM_REQUEST];
pthread_mutex_t array_lock;
pthread_mutex_t time_lock;
pthread_rwlock_t read_write_lock;

void* client_side(void *descriptor){
    int client_fd = (int) (long) descriptor;  //This cast is to remove warnings
    char buffer[COM_BUFF_SIZE];
    char buffer_out[COM_BUFF_SIZE];
    double start;
    double end;
    ClientRequest request;

    read(client_fd,buffer,COM_BUFF_SIZE);

    GET_TIME(start);
    
    ParseMsg(buffer,&request);

    if(request.is_read){
        pthread_rwlock_rdlock(&read_write_lock);
        getContent(buffer_out,request.pos,server_array);
        pthread_rwlock_unlock(&read_write_lock);
    }

    else{
        pthread_rwlock_wrlock(&read_write_lock);
        setContent(request.msg,request.pos,server_array);
        pthread_rwlock_unlock(&read_write_lock);
    }

    GET_TIME(end);

    if(request.is_read){
        write(client_fd,buffer_out,COM_BUFF_SIZE);
    }
    else{
        write(client_fd,request.msg,COM_BUFF_SIZE);
    }

    close(client_fd);

    pthread_mutex_lock(&time_lock);
    array_of_times[index_time] = end - start;
    index_time++;
    index_time %= COM_NUM_REQUEST;  //saftey net just in case
    pthread_mutex_unlock(&time_lock);

    pthread_exit(0);

}

void start_server(){
    
    struct sockaddr_in sock_var;
    int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
    int clientFileDescriptor;
    int i;
    //pthread_t t[COM_NUM_REQUEST];

    sock_var.sin_addr.s_addr=inet_addr(server_ipadress);
    sock_var.sin_port=server_port;
    sock_var.sin_family=AF_INET;
    
    int options;
    if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &options, sizeof(options)) < 0){
        perror("Socket Bind Failed\n");
        exit(0);
    }


    if (bind(serverFileDescriptor, (struct sockaddr*) &sock_var, sizeof(sock_var)) < 0){
        perror("Bind Failed\n");
        exit(0);
    }

    if (listen(serverFileDescriptor, COM_NUM_REQUEST) < 0){
        perror("Bind listen Failed\n");
        exit(0);
    }

    printf("socket has been created\n");

    while(1)        //loop infinity
    {
        for(i=0;i<COM_NUM_REQUEST;i++)      //can support many clients at a time
        {
            clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);
            //printf("Connected to client %d\n",clientFileDescriptor);
            pthread_create(&threads_id[i],NULL,client_side,(void *)(long)clientFileDescriptor);
        }

        //wait to finish
        for(i = 0;i<COM_NUM_REQUEST;i++){
            pthread_join(threads_id[i],NULL);
        }

        //write to file output
        saveTimes(array_of_times,COM_NUM_REQUEST);
    }
    close(serverFileDescriptor);
}

int main(int argc, char* argv[])
{
    if(argc != 4){
        printf("please enter in the format <array_size> <ip> <port>\n");
        return 0;
    }
    //initializations
    array_size = atoi(argv[1]);
    server_ipadress = argv[2];
    server_port = atoi(argv[3]);
    pthread_rwlock_init(&read_write_lock,NULL);
    pthread_mutex_init(&time_lock, NULL);

    server_array= malloc(array_size * sizeof(char *));

    printf("alocated memory\n");
    int i;
    for (i = 0; i < array_size; i++){
        server_array[i] = malloc(COM_BUFF_SIZE * sizeof(char));
    }
    printf("Does it break");
    for (i = 0; i < array_size; i++){
        sprintf(server_array[i], "String %d: the initial value", i);
    }
    printf("anout to start\n");
    start_server();

    return 0;
}
