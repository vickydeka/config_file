import imp


import os
ingress_tbl_name="ipv4"
egress_tbl_name="send_frame"
def read_data():
    global info,src_mac_info
    info={}
    src_mac_info={}
    with open("dstip.txt") as file:
        data=file.readline().split(',')
        info[data[0]]=data[1]+','+data[2].strip()
    with open("srcmac.txt") as file:
        data=file.readline().split(',')
        src_mac_info[data[0]]=data[1].strip()
    print(info)
    print(src_mac_info)
def write_forwarding_rules():
    if os.path.exists(f"{file_name}.txt"):
        os.remove(f"{file_name}.txt")
    wrt=open(f"{file_name}.txt","w")
    print(f"Generating rules for table {ingress_tbl_name}")
    for x,(y,z) in enumerate(info.items()):
        z=z.split(',')
        str_cmd=f"table_add {ingress_tbl_name} ipv4_forward {y} => {z[0]} {z[1]}"
        print(str_cmd)
        wrt.write(str_cmd+"\n")
    print(f"Generating rules for table {egress_tbl_name}")
    for x,(y,z) in enumerate(src_mac_info.items()):
        str_cmd=f"table_add {egress_tbl_name} rewrite_mac {y} => {z}"
        print(str_cmd)
        wrt.write(str_cmd+"\n")
    #os.system(f"simple_switch_CLI < {file_name}.txt")
file_name=input("Enter filename (.txt) :")
read_data()
write_forwarding_rules()