# ucode
basic ucode samples
## uci configuration
get the _ipaddr_ field in uci configuration :
```sh
root@OpenWrt:~# ucode uci_ipaddr.uc lan
{ "UCI": { "IP": "192.168.1.1" } }
```
## ubus call
get a field of the system board description
```sh
root@OpenWrt:~# ucode ubus_system_board.uc model
QEMU Standard PC (i440FX + PIIX, 1996)
```
### embedded c
call a c function to display a delayed string
```sh
root@OpenWrt:~# ./dprint 100 "test delayed print with embedded c in ucode"
test delayed print with embed
```
the function is available in the cinuc.so library made from the cinuc.c source file
dprint is the bytecode generated with the dprint.uc source file
