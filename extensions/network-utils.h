// The author disclaims copyright to this source code.
#ifndef __NETWORK_H
#define __NETWORK_H

#ifdef __NETWORK

#include <errno.h>
#include <colorforth.h>

// #define PERROR(msg) ERR(msg); ERR(": "); ERR(strerror(errno));

#define FAILURE 0

cell client_start(cell host, cell port);
void server_start (struct state *s);
cell server_close(cell fd);
cell server_nonblocking (cell server_fd);
cell server_accept (cell server_fd);
cell socket_recv(cell socket);
cell socket_send (cell msg, cell socket);
cell socket_send_line (cell msg, cell socket);

void init_network(struct state *s);

#endif /* __NETWORK */

#endif /* _NETWORK_H */
