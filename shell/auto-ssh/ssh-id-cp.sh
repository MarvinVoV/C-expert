#!/bin/bash

# param: host, passwd

function ssh_id_auto_copy(){
    expect << EOF
        spawn ssh-copy-id -i $HOME/.ssh/id_rsa.pub $1
        expect {
            "*yes/no"  { send "yes\r"; exp_continue }
            "*assword" { send "$2\r"                }
        }
        expect eof
EOF
}

ssh_id_auto_copy $1 $2


