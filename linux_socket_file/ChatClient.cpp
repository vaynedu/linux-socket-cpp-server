#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"
#include <pthread.h>


using namespace std;

int value_receive_exit;
int value_send_exit;

void *ProcessReceive(void *arg)
{
    string  receiveMessage;
    ClientSocket *clientSocket = static_cast<ClientSocket *>(arg);
    while(!value_receive_exit){
        clientSocket->Receive(receiveMessage);
        if(receiveMessage == ""){
               continue;
        }
        cout << "Response from server: "<< receiveMessage << endl;
        if(receiveMessage == "server has received your file"){
              value_send_exit = 1;
              break;
        }
        //cout << "Response from server: "<< receiveMessage << endl;
        sleep(2);
    }
    pthread_exit(NULL);
    return NULL;
}



int main(int argc,char *argv[])
{
    pthread_t thread;
    int retval;
    string sendMessage;

    cout << "Running client......"<<endl;
    try
    {
        ClientSocket clientSocket("127.0.0.1",8080);

        retval = pthread_create(&thread,NULL,ProcessReceive,static_cast<void *>(&clientSocket));
        if(retval != 0){
            throw SocketException("pthread_create failed\n");
        }

        //clientSocket.Send("Hello,my name is du shuai,I will send you file");
        clientSocket.SendFile("passwd");
        //clientSocket.Send("file translate complete");
        while(!value_send_exit){
           sleep(5);
        }
        value_receive_exit = 1;
        pthread_join(thread,NULL);


    }
    catch(SocketException& ex)
    {
        cout << "Exception was caught:" << ex.Description() << endl;
    }
    return 0;
}
