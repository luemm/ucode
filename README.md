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
## ucode and c
### embedded c
call a c function to display a delayed string
```sh
root@OpenWrt:~# ./dprint 100 "test delayed print with embedded c in ucode"
test delayed print with embed
```
the function is available in the cinuc.so library made from the cinuc.c source file  
dprint is the bytecode generated with the dprint.uc source file

### embedded in c
manage the ubus environment in c and create an object with ucode
```sh
root@OpenWrt:~# ./ubus_obj &
root@OpenWrt:~# ubus call ubus_obj get_arg '{"argin":"cheers!"}'
{
	"input": "cheers!"
}
root@OpenWrt:~# ubus call ubus_obj get_pid
{
	"pid": 4147
}
```
_ubus\_obj_ is built with _ubus\_obj.c_  
_ubus\_obj.uc_ is needed at runtime by _ubus\_obj_
