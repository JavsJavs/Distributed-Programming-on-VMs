#include "utils.h"

int main(int argc, char** argv)
{
 int server_fd=initServer(60000);
 int client_fd=waitForConnections(server_fd);

 closeConnection(server_fd);
 closeConnection(client_fd);
return 0;
}
