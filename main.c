  #include <stdio.h>
#include <stdlib.h>
#include "includes/ssh_client.h"

int main(int argc, char **argv)
{

    ssh_client_t *ssh = ssh_login("localhost", "0xpfu", "root"); // login ssh informations

    // if connnection is enabled 
    printf("Connection enabled\n");

}   
