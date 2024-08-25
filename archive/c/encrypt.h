void encrypt(char *msg);

void encrypt(char *msg){
    while(*msg){
        *msg ^= 31;
        msg++;
    }
}
