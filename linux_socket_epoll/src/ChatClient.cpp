#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

int main(int argc,char *argv[])
{
    cout << "Running client......"<<endl;
    try
    {
        ClientSocket clientSocket("127.0.0.1",8080);
        while(1){
             clientSocket.Send("Hello,my name is du shuai");
             string message;
             clientSocket.Receive(message);
             cout << "Response from server: "<< message << endl;
             sleep(5);
           }
    }
    catch(SocketException& ex)
    {
        cout << "Exception was caught:" << ex.Description() << endl;
    }
    return 0;
}
