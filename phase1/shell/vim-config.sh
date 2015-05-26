#!/bin/bash
VIM_CONFIG="/etc/vim/vimrc"
if [ $UID -ne 0 ];
then
    echo "Please run with super user"
    exit 1
fi
if ! type "vim" > /dev/null ;
then
    apt-get install vim
fi
if [ -f "$VIM_CONFIG" ];
then
    echo "set tabstop=4"    >> $VIM_CONFIG
    echo "set shiftwidth=4" >> $VIM_CONFIG
    echo "set cindent"      >> $VIM_CONFIG
    echo "set expandtab"     >> $VIM_CONFIG
else
    echo "Can't found $VIM_CONFIG"
fi
echo "Config VIM finished."
