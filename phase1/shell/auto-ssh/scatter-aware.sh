#!/bin/bash

###
# Note: Before running this script, please ensure you have installed 'expect' on each system 
###
# check expect command
if ! type "expect" > /dev/null; then
    echo "please intall expect on each matchine in this cluster"
    echo "run: sudo apt-get install expect"
    exit 1
fi

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


if [ $( id -u ) -ne 0 ]; then
    echo "Permission denied."
    exit 1
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

# copy remote script
for (( i=0; i<$length; i++ ))
do
    ssh_auto_keygen ${users[$i]} ${hosts[$i]} ${passwds[$i]}
    expect << EOF
    spawn scp ssh-id-cp.sh ${users[$i]}@${hosts[$i]}:$HOME
    expect {
        "*assword" { send "${passwds[$i]}\r";}
    }
    expect eof;
EOF
done

# copy ssh identify 
for (( i=0; i<$length; i++ ))
do
    for (( j=0; j<$length; j++))
    do
        if [ $i -eq $j ]; then
            continue
        fi
        expect << EOF
        spawn ssh ${users[$i]}@${hosts[$i]} "bash $HOME/ssh-id-cp.sh ${hosts[$j]} ${passwds[$j]}"      
        expect {
            "*yes/no"  { send "yes\r"; exp_continue }
            "*assword" { send "${passwds[$i]}\r"    }
        }
        expect eof;
EOF
    done
done

# Clean
for (( i=0; i<$length; i++))
do
    expect << EOF
    spawn ssh ${users[$i]}@${hosts[$i]} "rm -f $HOME/ssh-id-cp.sh"
    expect {
        "*yes/no"  { send "yes\r"; exp_continue }
        "*assword" { send "${passwds[$i]}\r"    }
    }
    expect eof;
EOF
done

echo "done"

