IFNAME="wlan0"
CON_NAME="simple_switch_bmv2"
nmcli con add type wifi ifname $IFNAME con-name $CON_NAME autoconnect yes ssid $CON_NAME
nmcli con modify $CON_NAME 802-11-wireless.mode ap 802-11-wireless.band bg ipv4.method shared
nmcli con modify $CON_NAME wifi-sec.key-mgmt wpa-psk
nmcli con modify $CON_NAME wifi-sec.psk "UbuntuServer"
nmcli con up $CON_NAME
nmcli connection show $CON_NAME
