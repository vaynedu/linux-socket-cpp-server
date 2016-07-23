#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

int  value_receive_exit;
int  value_send_exit;

void *ProcessReceive(void *arg)
{
      string receiveMessage;
      ClientSocket *clientSocket = static_cast<ClientSocket*>(arg);
      while(!value_receive_exit){
           clientSocket->Receive(receiveMessage);
           if(receiveMessage == "exit"){
                cout <<  "server exit" <<endl;
                value_send_exit = 1;
                break;
           }else if(receiveMessage == ""){
                continue;
           }
           cout << "Response from server: "<<receiveMessage << endl;
           sleep(5);
      }
      pthread_exit(NULL);
      return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t   thread;
    int retval;
    string  sendMessage;

    cout << "Running client......"<<endl;
    try
    {
        ClientSocket clientSocket("127.0.0.1",8080);

        retval = pthread_create(&thread,NULL,ProcessReceive,static_cast<void *>(&clientSocket));
        if(retval != 0){
            throw SocketException("pthread_create failed\n");
        }
        while(!value_send_exit){
            //cout << "client say:   ";
            //cin >> sendMessage;
            sendMessage = "cao yan qing da bei dan\n";
            clientSocket.Send(sendMessage);
            if(sendMessage == "exit" || sendMessage == ""){
                cout << "client exit"<<endl;
                value_receive_exit = 1;
                break;
            }
            sendMessage.clear();
            sleep(5);
        }
        cout << "end" <<endl;
    }
    catch(SocketException& ex)
    {
        cout << "Exception was caught:" << ex.Description() << endl;
    }
    return 0;
}
