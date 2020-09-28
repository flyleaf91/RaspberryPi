# printf Hex Format

进行二进制数据查看的时候常用的16 byte对齐输出参考

## 打印输出示例

```C
pal_log_err("oem_avb_key =\n");
for (i = 0; i < AVB_PUBK_SZ; i++) {
        pal_log_err("0x%02x ", g_avb_key[i]);

        if (((i + 1) % 16) == 0)
                pal_log_err("\n");
}
```
