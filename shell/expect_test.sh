#!/bin/bash
ip=$1
passwd=$2
echo $ip $user $passwd

function ssh_auto_copy(){
	expect -c "
		spawn ssh-copy-id -i /root/.ssh/id_rsa.pub $1
		expect {
			"*yes/no" { send "yes"\r;exp_continue}
			"*assword" { send "$2"\r }
		}
		interact;"
}

ssh_auto_copy $ip $passwd
