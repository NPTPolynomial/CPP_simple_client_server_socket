//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for inet_addr

#include <string>
#include <iostream>

// IPv4 AF_INET sockets:
/*struct sockaddr_in {
    short sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short sin_port;     // e.g. htons(3490)
    struct in_addr sin_addr;     // see struct in_addr, below
    char sin_zero[8];  // zero this if you want to
};
 
struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

*/

using namespace std;

int main( int argc, char *argv[]){

    //create a client socket
    int socket_desc;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1){
        cout<<"Could not create socket"<<endl;
    }
    

    //prepare all the addresses for the server we are connecting to 
    struct sockaddr_in server;

    //server.sin_addr.s_addr = inet_addr("216.58.209.3");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) <0){
        cout<<"connection error"<<endl;
        return 1;
    }else{
        cout<<"connected"<<endl;

    }
    
    
    //send test data
    const char *message;
    message = "GET / HTTP/1.1\r\n\r\n";
    
    if (send(socket_desc, message, strlen(message), 0) < 0){
        cout<<"Message failed to send."<<endl;
    }else{
        cout<<"Message sent."<<endl;
    }
    



    //receive data if there is any

    char server_reply[2000];
    if (recv(socket_desc, server_reply, 2000, 0) < 0){
        cout << "Recv failed"<<endl;

    }else{
        cout << "Server reply: ";
        cout << server_reply << endl;
    }


    //close connection

    close(socket_desc);

    return 0;
}

