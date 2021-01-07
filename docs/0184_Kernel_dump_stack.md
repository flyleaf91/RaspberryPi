# Kernel dump_stack()

利用内核的dump_stack()快速理清tty设备函数调用关系

## diff

```diff
diff --git a/kernel-4.9/drivers/tty/serial/8250/8250_dma.c b/kernel-4.9/drivers/tty/serial/8250/8250_dma.c
index fdbddbc6375..b5e5556fcc3 100644
--- a/kernel-4.9/drivers/tty/serial/8250/8250_dma.c
+++ b/kernel-4.9/drivers/tty/serial/8250/8250_dma.c
@@ -71,13 +71,29 @@ int serial8250_tx_dma(struct uart_8250_port *p)
        struct circ_buf                 *xmit = &p->port.state->xmit;
        struct dma_async_tx_descriptor  *desc;
        int ret;

        if (uart_tx_stopped(&p->port) || dma->tx_running ||
            uart_circ_empty(xmit))
                return 0;

+       dump_stack();
+
        dma->tx_size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

        desc = dmaengine_prep_slave_single(dma->txchan,
                                           dma->tx_addr + xmit->tail,
                                           dma->tx_size, DMA_MEM_TO_DEV,

```

## 输出log

```
[ 5952.713043] -(1)[2247:Binder:563_2]Call trace:
[ 5952.713058] -(1)[2247:Binder:563_2][<ffffff9cb928a7e8>] dump_backtrace+0x0/0x288
[ 5952.713066] -(1)[2247:Binder:563_2][<ffffff9cb928a7e0>] show_stack+0x14/0x1c
[ 5952.713074] -(1)[2247:Binder:563_2][<ffffff9cb95eaef0>] dump_stack+0xcc/0x104
[ 5952.713083] -(1)[2247:Binder:563_2][<ffffff9cb9672b70>] serial8250_tx_dma+0x94/0x2a8
[ 5952.713090] -(1)[2247:Binder:563_2][<ffffff9cb96712c8>] serial8250_start_tx+0x110/0x1b8
[ 5952.713099] -(1)[2247:Binder:563_2][<ffffff9cb966a950>] __uart_start+0x58/0x64
[ 5952.713106] -(1)[2247:Binder:563_2][<ffffff9cb966accc>] uart_write+0x1cc/0x234
[ 5952.713113] -(1)[2247:Binder:563_2][<ffffff9cb965fd3c>] n_tty_write+0x11c/0x3c8
[ 5952.713122] -(1)[2247:Binder:563_2][<ffffff9cb965b628>] tty_write+0x1e4/0x27c
[ 5952.713130] -(1)[2247:Binder:563_2][<ffffff9cb9416040>] __vfs_write+0x44/0x124
[ 5952.713136] -(1)[2247:Binder:563_2][<ffffff9cb9416320>] vfs_write+0xc8/0x184
[ 5952.713142] -(1)[2247:Binder:563_2][<ffffff9cb9416514>] SyS_write+0x6c/0xcc
[ 5952.713149] -(1)[2247:Binder:563_2][<ffffff9cb92835c0>] el0_svc_naked+0x34/0x38
[ 5952.713155] -(1)[2247:Binder:563_2]==serial8250_tx_dma,head:933 tail:908 tx_size:25
```

## 查找内核函数

* cd kernel-4.9/drivers/tty/serial
* `ack " uart_write\("`
  ```
  serial_core.c
  566:static int uart_write(struct tty_struct *tty,
  ```
* uart_write
  ```C
  static int uart_write(struct tty_struct *tty,
                                          const unsigned char *buf, int count)
  {
          struct uart_state *state = tty->driver_data;
          struct uart_port *port;
          struct circ_buf *circ;
          unsigned long flags;
          int c, ret = 0;
  
          /*
           * This means you called this function _after_ the port was
           * closed.  No cookie for you.
           */
          if (!state) {
                  WARN_ON(1);
                  return -EL3HLT;
          }
  
          port = uart_port_lock(state, flags);
          circ = &state->xmit;
          if (!circ->buf) {
                  uart_port_unlock(port, flags);
                  return 0;
          }
  
          while (port) {
                  c = CIRC_SPACE_TO_END(circ->head, circ->tail, UART_XMIT_SIZE);
                  if (count < c)
                          c = count;
                  if (c <= 0)
                          break;
                  memcpy(circ->buf + circ->head, buf, c);
                  circ->head = (circ->head + c) & (UART_XMIT_SIZE - 1);
                  buf += c;
                  count -= c;
                  ret += c;
          }
  
          __uart_start(tty);
          uart_port_unlock(port, flags);
          return ret;
  }
  ```
* `struct uart_port`中有`struct uart_state`，所以修改上面的state从port中获取；
