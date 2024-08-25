#!/bin/bash

# params: user, host, passwd
function ssh_auto_keygen(){
    expect << EOF 
	spawn ssh $1@$2 "ssh-keygen -t rsa"
	expect {
			"yes/no"		{ send "yes\r"; exp_continue }
			"*assword"      { send "$3\r" ; exp_continue }
			"save the key"  { send "\r"   ; exp_continue }
			"Overwrite"     { send "y\r"  ; exp_continue }
			"no passphrase" { send "\r"   ; exp_continue }
			"again"         { send "\r"   ; exp_continue }
	}
	expect eof;
EOF
}

ssh_auto_keygen root 192.168.220.128 root
