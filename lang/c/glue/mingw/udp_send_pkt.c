/**
 *
 * MQTT/UDP project
 *
 * https://github.com/dzavalishin/mqtt_udp
 *
 * Copyright (C) 2017-2019 Dmitry Zavalishin, dz@dz.ru
 *
 *
 * Network connection - send UDP packet. To be rewritten per target OS.
 *
**/

//#include "../../config.h"
#include "config.h"

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <fcntl.h>
#include <errno.h>

#include "../../mqtt_udp.h"
#include "udp_io.h"



int mqtt_udp_send_pkt( int fd, char *data, size_t len )
{
    //struct sockaddr_in addr;
    SOCKADDR_IN addr;

    //struct sockaddr_in serverAddr;
    SOCKADDR_IN serverAddr;

    socklen_t addr_size;

    /*Configure settings in address struct*/
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( MQTT_PORT );
    serverAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;

    mqtt_udp_throttle(); // Speed limit

    ssize_t rc = sendto( fd, data, len, 0, (struct sockaddr *)&serverAddr, addr_size);

    return (rc != len) ? EIO : 0;
}


int mqtt_udp_send_pkt_addr( int fd, char *data, size_t len, uint32_t ip_addr )
{
    struct sockaddr_in addr;

    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*Configure settings in address struct*/
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( MQTT_PORT );
    serverAddr.sin_addr.s_addr = ip_addr;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;

    ssize_t rc = sendto( fd, data, len, 0, (struct sockaddr *)&serverAddr, addr_size);

    return (rc != len) ? EIO : 0;
}


