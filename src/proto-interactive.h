#ifndef PROTO_INTERACTIVE_H
#define PROTO_INTERACTIVE_H
#include <stdio.h>

/*这个 TCP API 的 wrapper 是为了让 parser 不直接调用用户态TCP协议栈接口
取代了原来的自定义 socket
这样的话可以使得 parser 将数据收发的需求传递给下层协议
这允许了 SSL 中间层的存在*/

struct InteractiveData {
  const void *m_payload;
  unsigned m_length;
  unsigned tcp_ctrl;
  unsigned is_payload_dynamic : 1;
  unsigned is_closing : 1;
};

enum {
  TCPTRAN_DYNAMIC = 0x0001,
};

/* Called to 'transmit' TCP packet payload. */
void tcp_transmit(struct InteractiveData *more, const void *data, size_t length,
                  unsigned flags);

/* Called to close the connection */
void tcp_close(struct InteractiveData *more);

/* Called to allocate a TCP buffer. */
unsigned char *tcp_transmit_alloc(struct InteractiveData *more, size_t length);

void append_interactive_data(struct InteractiveData *more1,
                             struct InteractiveData *more2);
void free_interactive_data(struct InteractiveData *more);

int interactive_data_selftest();

#endif
