#include <iostream>
#include <string>
#include "EpollServerSocket.h"
#include "SocketException.h"

using namespace std;

int main(int argc,char *argv[])
{
    cout<<"Running server......"<<endl;
    try
    {
        EpollServerSocket server(8080);
        while(true){
          //  Socket newSocket;
          //   server.Accept(newSocket);
            server.Run();
          /*
            try
            {
                string message;
                server.Receive(newSocket,message);
                cout<<"Receive message: "<<message<<endl;
                message = "Here is server";
                server.Send(newSocket,message);
            }
            catch(SocketException&){}
           */
        }
    }
    catch(SocketException& ex)
    {
        cout << "Exception was caught:" << ex.Description() << "\nExiting.\n"<<endl;
    }
    return 0;
}
