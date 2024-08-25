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
		"again"         { send "\r"   ;              }
	}
	expect eof;
EOF
}

function scp_auto_copy(){

    scp $1 $2@$3:$4
}

if [ $( id -u ) -ne 0 ]; then
    echo "Permission denied."
    exit 1
fi

if ! type "expect" > /dev/null; then
    apt-get install expect;
fi

flag="y";
i=0;
while [ $flag != "n" ]
do
    read -p "Enter host:" hosts[$i]
    read -p "Enter ${hosts[$i]}'s user:" users[$i]
    read -p "Enter ${hosts[$i]}'s passwd:" passwds[$i]
    let i++
    read -p "Continue(y/n)" flag
    while [ $flag != "n" ] && [ $flag != "y" ]
    do
        read -p "Continue(y/n)" flag
    done
done

length=$i;

for (( i=0; i<$length; i++ ))
do
    ssh_auto_keygen ${users[$i]} ${hosts[$i]} ${passwds[$i]}
done

for (( i=0; i<$length; i++ ))
do
    for (( j=0; j<$length; j++))
    do
        if [ $i -eq $j ]; then
            continue
        fi
        ssh_auto_copy_rsa ${users[$i]} ${hosts[$i]} ${passwds[$i]} ${hosts[$j]} ${passwds[$j]}
    done
done

echo "done"

