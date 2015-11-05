//server implementation.

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //to write

#include <pthread.h> //for multi-threaded connections

using namespace std;

int main (){

    //create socket for server
    int socket_desc;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1){
        cout << "Failed to create socket";
    }


    //incoming connection setup
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );


    //bind the socket to server
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0 ){
        cout << "Binding failed"<<endl;
    }else{
        cout << "Binding success."<<endl;
    }


    //listen in for connections
    listen(socket_desc, 3);


    //accept incoming connections
    int new_socket;
    int c; //will be size of sockaddr_in for length of socket.
    struct sockaddr_in client;
    const char *message; //will be used to send message back to client

    cout << "Waiting for incoming connections..."<<endl;
    c = sizeof(struct sockaddr_in);
    
    //accet new connections in a loop.
    while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
        cout << "Connection accepted"<<endl;

        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        cout << "CLIENT IP: "<<client_ip<<endl;
        cout << "CLIENT PORT: "<<client_port<<endl;
        

        //send message back to client
        message = "Hello client :) \n";
        send(new_socket, message, strlen(message), 0);
    }

    if(new_socket < 0){
        cout << "Incoming Connection failed to accepted"<<endl;

    }else{
             
    }
    
   

    close(socket_desc);
    return 0;


}
