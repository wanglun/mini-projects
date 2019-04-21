// refer: https://blog.crazyark.me/posts/epoll/
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_EVENTS 10
#define LISTEN_PORT 1234
#define BUF_LEN 512
#define MAX_CONN 100

struct epoll_event ev, events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;
struct sockaddr_in server;

#define log(...) printf(__VA_ARGS__)

void response_to_conn(int conn_sock) {
  char buf[BUF_LEN + 1];

  int read_len = 0;
  while ((read_len = read(conn_sock, buf, BUF_LEN)) > 0) {
    buf[read_len] = '\0';

    int cursor = 0;
    while (cursor < read_len) {
      // writing to a pipe or socket whose reading end is closed
      // will lead to a SIGPIPE
      int len = write(conn_sock, buf + cursor, read_len - cursor);
      if (len < 0) {
        perror("write");
        return;
      }
      cursor += len;
    }

    // there are no data so we do not have to do another read
    if (read_len < BUF_LEN) {
      break;
    }
  }

  // must make sure that the next read will block this non-blocking
  // socket, then we think the event is fully consumed.
  if (read_len < 0 && errno == EAGAIN) {
    return;
  }
  // end of file
  if (read_len == 0) {
    return;
  }
}

/* Code to set up listening socket, 'listen_sock' */
void listen_and_bind() {
  if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  int option = 1;
  setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(LISTEN_PORT);
  if (bind(listen_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  listen(listen_sock, MAX_CONN);
}

void create_epoll() {
  epollfd = epoll_create1(0);
  if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  ev.events = EPOLLIN;
  ev.data.fd = listen_sock;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
    perror("epoll_ctl: listen_sock");
    exit(EXIT_FAILURE);
  }
}

void set_fd_nonblocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    perror("getfl");
    return;
  }
  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
    perror("setfl");
    return;
  }
}

void epoll_loop() {
  for (;;) {
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    log("get %d events from epoll_wait!\n", nfds);

    for (int n = 0; n < nfds; ++n) {
      if (events[n].data.fd == listen_sock) {
        struct sockaddr_in local;
        socklen_t addrlen;
        conn_sock = accept(listen_sock, (struct sockaddr*)&local, &addrlen);
        if (conn_sock == -1) {
          perror("accept");
          exit(EXIT_FAILURE);
        }

        log("accept a new connection!\n");

        // set non-blocking
        set_fd_nonblocking(conn_sock);

        ev.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
        ev.data.fd = conn_sock;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
          perror("epoll_ctl: conn_sock");
          exit(EXIT_FAILURE);
        }
      } else {
        if (events[n].events & (EPOLLRDHUP | EPOLLERR)) {
          log("detect a closed/broken connection!\n");
          // must EPOLL_CTL_DEL before close
          // https://idea.popcount.org/2017-03-20-epoll-is-fundamentally-broken-22/
          epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, NULL);
          close(events[n].data.fd);
        } else
          response_to_conn(events[n].data.fd);
      }
    }
  }
}

int main(int argc, char** argv) {
  log("listenning on port 1234!\n");
  listen_and_bind();

  log("creating epoll!\n");
  create_epoll();

  log("starting loop on epoll!\n");
  epoll_loop();

  return 0;
}
