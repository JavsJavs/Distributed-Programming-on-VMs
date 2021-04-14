int initServer(int port)
{
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
       printf("Error creating socket\n");
    }
   struct sockaddr_in serv_addr;
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port);

   int option = 1;
   setsockopt(sock_fd,SOL_SOCKET,
              (SO_REUSEPORT | SO_REUSEADDR),
              &option,sizeof(option));

   if (bind(sock_fd,(struct sockaddr *) &serv_addr,
         sizeof(serv_addr)) < 0)
         printf("ERROR on binding");
   listen(sock_fd,5);
   return sock_fd;
}

int waitForConnections(int sock_fd){
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsock_fd = accept(sock_fd,
                            (struct sockaddr *) &cli_addr,
                            &clilen);
    return newsock_fd;

}

void closeConnection(int socket_fd){
    close(socket_fd);
}
