// The author disclaims copyright to this source code.

#ifdef __NETWORK

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_SERVER_START            (opcode_t) 0x3F90A4AA           // server-start
#define OP_CLIENT_START            (opcode_t) 0x54C4D466           // client-start
#define OP_SERVER_STOP             (opcode_t) 0x73F7E84A           // server-stop
#define OP_SERVER_NONBLOCKING      (opcode_t) 0x3A7FBA86           // server-nonblocking
#define OP_SERVER_ACCEPT           (opcode_t) 0xA66BDA62           // server-accept

#define OP_SOCKET_SEND             (opcode_t) 0xB830ECB2           // socket-send
#define OP_SOCKET_SEND_CHAR        (opcode_t) 0x49DA8E15           // socket-send-char
#define OP_SOCKET_RECV             (opcode_t) 0x9897D554           // socket-recv

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("server-start"),         OP_SERVER_START);
define_primitive(s, ENTRY_NAME("client-start"),         OP_CLIENT_START);
define_primitive(s, ENTRY_NAME("server-stop"),          OP_SERVER_STOP);
define_primitive(s, ENTRY_NAME("server-nonblocking"),   OP_SERVER_NONBLOCKING);
define_primitive(s, ENTRY_NAME("server-accept"),        OP_SERVER_ACCEPT);

define_primitive(s, ENTRY_NAME("socket-send"),          OP_SOCKET_SEND);
define_primitive(s, ENTRY_NAME("socket-send-char"),     OP_SOCKET_SEND_CHAR);
define_primitive(s, ENTRY_NAME("socket-recv"),          OP_SOCKET_RECV);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_SERVER_START: {
  POP1();
  cell port = p1;

  cell server_fd;
  struct sockaddr_in address;
  int opt = 1;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    PERROR("socket failed");
    return;
  }

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    PERROR("socket failed");
    return;
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt))) {
    PERROR("setsockopt");
    return;
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons( port );

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
    PERROR("bind failed");
    return;
  }

  if (listen(server_fd, 3) < 0) {
    PERROR("listen");
    return;
  }

  cf_printf(s, "Server started on port: %d\n", port);

  PUSH1(server_fd);

  break;
}

case OP_CLIENT_START: {
  POP2();
  cell port = p1;
  char * host = CFSTRING2C(p2);

  cf_printf(s, "client: %s  %d\n", host, port);

  int sock = 0;
  struct sockaddr_in serv_addr;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    PERROR("Socket creation error");
    return;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
    PERROR("Invalid address/ Address not supported");
    return;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    PERROR("Connection Failed");
    return;
  }

  cf_printf(s, "Client connected on %s on port %d\n", host, port);

  PUSH1(sock);

  break;
}

case OP_SERVER_STOP: {
  POP1();
  cell fd = p1;

  if (close(fd)) {
    PERROR("socket close");
    return;
  }

  cf_printf(s, "FD closed. Server stopped\n");

  PUSH1(-1);

  break;
}

case OP_SERVER_NONBLOCKING: {
  POP1();
  cell fd = p1;

  int status = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

  if (status == -1){
    PERROR("calling fcntl");
    return;
  }

  cf_printf(s, "FD made nonblocking\n");

  PUSH1(fd);

  break;
}

case OP_SERVER_ACCEPT: {
  POP1();
  cell server_fd = p1;

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  cell new_socket;

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
    PERROR("accept");
    return;
  }

  cf_printf(s, "Connection accepted\n");

  PUSH1(new_socket);

  break;
}

case OP_SOCKET_SEND: {
  POP2();
  cell socket = p1;
  char *msg = CFSTRING2C(p2);

  if (send(socket, msg, strlen(msg), 0) < 0) {
    PERROR("send failed");
    return;
  }

  PUSH1(-1);

  break;
}

case OP_SOCKET_SEND_CHAR: {
  POP2();
  cell socket = p1;
  char c = p2;

  if (send(socket, &c, 1, 0) < 0) {
    PERROR("send failed");
    return;
  }

  PUSH1(-1);

  break;
}

case OP_SOCKET_RECV: {
  POP3();
  cell socket = p1;
  cell len = p2;
  char *buffer = (char *)p3;

  const ssize_t reslen = recv(socket, buffer, len, 0);

  if (reslen < 0) {
    if (errno == EAGAIN) {
      PUSH1(0);
      return;
    }
    PERROR("recv failed");
    return;
  }

  PUSH1(-1);

  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define PERROR(msg) cf_printf(s, "ERROR: %s: %s\n", msg, strerror(errno)); PUSH1(0)

#endif /* __SECTION_FUNCTION */

#endif /* __NETWORK */
