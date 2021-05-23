// The author disclaims copyright to this source code.
#include <colorforth.h>

#ifdef __NETWORK

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <network-utils.h>

char server_pad[1024] = {0};

cell client_start(cell host, cell port) {
// 	int sock = 0;
// 	struct sockaddr_in serv_addr;
// 	char host_str[1024] = {0};
//
// 	ForthStringToC( host_str, (char *) host, sizeof(host_str));
//
// 	EMIT_CR;
//
// 	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// 		PERROR("Socket creation error");
// 		return FAILURE;
// 	}
//
// 	memset(&serv_addr, '0', sizeof(serv_addr));
//
// 	serv_addr.sin_family = AF_INET;
// 	serv_addr.sin_port = htons(port);
//
// 	// Convert IPv4 and IPv6 addresses from text to binary form
// 	if(inet_pton(AF_INET, host_str, &serv_addr.sin_addr) <= 0) {
// 		PERROR("Invalid address/ Address not supported");
// 		return FAILURE;
// 	}
//
// 	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// 		PERROR("Connection Failed");
// 		return FAILURE;
// 	}
//
// 	MSG("Client connected on ");
// 	MSG("host");
// 	MSG_NUM_D(": ", port);

//	return sock;
  return 0;
}

void
server_start(struct state *s)
{
  unsigned int port = pop(s->stack);
  char *host = (char *)pop(s->stack) + sizeof(cell);

  printf("Server start: %u %s %p!!!!\n", port, host, host);
//	cell server_fd;
//	struct sockaddr_in address;
//	int opt = 1;
//
//	EMIT_CR;
//
//	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//		PERROR("socket failed");
//		return FAILURE;
//	}
//
//	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//		PERROR("socket failed");
//		return FAILURE;
//	}
//
//	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//				   &opt, sizeof(opt))) {
//		PERROR("setsockopt");
//		return FAILURE;
//	}
//	address.sin_family = AF_INET;
//	address.sin_addr.s_addr = INADDR_ANY;
//	address.sin_port = htons( port );
//
//	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
//		PERROR("bind failed");
//		return FAILURE;
//	}
//
//	if (listen(server_fd, 3) < 0) {
//		PERROR("listen");
//		return FAILURE;
//	}
//
//	MSG_NUM_D("Server started on port: ", port);

  // return server_fd;
}

cell server_close(cell fd) {
// 	EMIT_CR;
//
// 	if (close(fd)) {
// 		PERROR("socket close");
// 		return FAILURE;
// 	}
//
// 	MSG("FD closed");

	return 0;
}

cell server_nonblocking(cell fd) {
//	int status = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
//
//	EMIT_CR;
//
//	if (status == -1){
//		PERROR("calling fcntl");
//		return FAILURE;
//	}
//
//	MSG("FD made nonblocking");

	return fd;
}

cell server_accept(cell server_fd) {
// 	struct sockaddr_in address;
// 	int addrlen = sizeof(address);
// 	cell new_socket;
//
// 	EMIT_CR;
//
// 	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
// 		PERROR("accept");
// 		return FAILURE;
// 	}
//
// 	MSG("Connection accepted");

//	return new_socket;
  return 0;
}

cell socket_recv(cell socket) {
// 	char buffer[1024] = {0};
//
// 	if (recv(socket, buffer, sizeof(buffer), 0) < 0) {
// 		if (errno == EAGAIN) {
// 			return 0;
// 		}
// 		PERROR("recv failed");
// 		return -1;
// 	}
//
// 	CStringToForth(server_pad, buffer, sizeof(buffer));
// 	return (cell) server_pad;

  return 0;
}

cell socket_send (cell msg, cell socket) {
// 	char buffer[1024] = {0};
//
// 	ForthStringToC( buffer, (char *) msg, sizeof(buffer));
//
// 	if (send(socket, buffer, strlen(buffer), 0) < 0) {
// 		PERROR("send failed");
// 		return 0;
// 	}
	return -1;
}

cell socket_send_line (cell msg, cell socket) {
// 	char buffer[1024] = {0};
//
// 	ForthStringToC( buffer, (char *) msg, sizeof(buffer));
//
// 	buffer[strlen(buffer)] = '\n';
//
// 	if (send(socket, buffer, strlen(buffer), 0) < 0) {
// 		PERROR("send_line failed");
// 		return 0;
// 	}
	return -1;
}

void
init_network(struct state *state)
{
  define_primitive_extension(state, "server-start", OP_SERVER_START, server_start);
}

#else

void
init_network(struct state *s)
{
}

#endif /* __NETWORK */
