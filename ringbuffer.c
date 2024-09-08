#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    uint8_t *buffer;
    size_t head;
    size_t tail;
    size_t size;
    size_t capacity;
    char  end_char;
} RingBuffer;

const int BUFFER_SIZE = 10;
char buffer[BUFFER_SIZE] = {0};
RingBuffer rb = {
    .buffer = (uint8_t *)buffer,
    .head = 0,
    .tail = 0,
    .size = 0,
    .capacity = BUFFER_SIZE,
    .end_char = '\n'
};

bool isFull(RingBuffer *rb) {
    return rb->size == rb->capacity;
}


bool isEmpty(RingBuffer *rb) {
    return rb->size == 0;
}


void writeRb(RingBuffer *rb, const char *str, const size_t size) {
    if (size <= 0 || str == NULL || *str == '\0') {
        return;
    }
    if (isFull(rb)) {
        return;
    }
    size_t len = size;
    // 写入数据超过最大容量时，截取
    if (len > rb->capacity) {
        len = rb->capacity;
    }

    while (len > 0 && !isFull(rb) && *str != '\0') {
        rb->buffer[rb->head] = *str;
        rb->head = (rb->head + 1) % rb->capacity;
        rb->size++;
        str++;
        len--;
    }
}


char* readRb(RingBuffer *rb) {
    if (isEmpty(rb)) {
        return NULL;
    }
    
    size_t count = 0; // 实际读取的长度
    size_t maxLen = rb->size; // 最大可能读取的长度

    char *data = malloc(1); // 分配初始空间
    if (data == NULL) {
        return NULL; // 分配失败
    }
    data[0] = '\0'; // 初始化为空字符串 确保字符串正确终止

    while(count < maxLen && rb->size > 0) {
        data = (char *) realloc(data, (count + 2) * sizeof(char)); // 动态调整大小
        if (data == NULL) {
            free(data);
            return NULL; //再次分配失败
        }


        char ch = rb->buffer[rb->tail];
        data[count++] = ch;
        rb->tail = (rb->tail + 1) % rb->capacity; 
        rb->size--;
        if (ch == rb->end_char) {
            break;
        }
    }
    data[count] = '\0'; // 确保字符串正确终止
    return data;
}

void printRb(RingBuffer *rb) {
    printf("\n\t************RingBuffer INFO Start ************: \n"); 
    printf("\thead=%lu, tail=%lu, size=%lu, capacity=%lu\n", rb->head, rb->tail, rb->size, rb->capacity);
    printf("\tBuffer Content: ");
    for (int i = 0; i < rb->capacity; i++) {
        if (rb->buffer[i] == '\0') {
            printf("(\\0)");
        } else if(rb->buffer[i] == rb->end_char) {
            printf("(\\n)");
        }else {
            printf("%c ", rb->buffer[i]);
        }
    }
    printf("\n\t************RingBuffer INFO End ************: \n"); 
}

void printData(char *data, size_t len) {
    if (len == 0 || data == NULL) {
        return;
    }
    printf("\tRead Data Content: ");
    for (int i = 0; i < len; i++) {
        if (data[i] == '\0') {
            printf("(\\0)");
        } else if(data[i] == '\n') {
            printf("(\\n)");
        }else {
            printf("%c ", data[i]);
        }
    }
    printf("\n");
}

void printEscaped(const char *str) {
    while (*str) {
        if (*str == '\0') {
            printf("(\\0)");
            str++;
        }else if(*str=='\n'){
            printf("(\\n)");
        } else {
            printf("%c", *str);
        }
        str++;
    }
    printf("\n");
}

int main() {
    // char *str = "he\n\nll\nord";
    char *str = "hello\nw";
    char *echo = NULL;

    memset(rb.buffer, '0', rb.capacity);

    printf("Write:");
    printEscaped(str);
    writeRb(&rb, str, strlen(str));
    printRb(&rb);

    while(!isEmpty(&rb)) {
        echo = readRb(&rb);
        if (echo == NULL) break;
        printData(echo, strlen(echo));
    }

    printRb(&rb);


    char *str2 = "orld\n\nzf";
    printf("Write:");
    printEscaped(str2);
    writeRb(&rb, str2, strlen(str2));
    printRb(&rb);

    while(!isEmpty(&rb)) {
        echo = readRb(&rb);
        if (echo == NULL) break;
        printData(echo, strlen(echo));
    }


    char *str3 = "or\n1\n232\nz";
    printf("Write:");
    printEscaped(str3);
    writeRb(&rb, str3, strlen(str3));
    printRb(&rb);

    while(!isEmpty(&rb)) {
        echo = readRb(&rb);
        if (echo == NULL) break;
        printData(echo, strlen(echo));
    }

    printRb(&rb);
    free(echo);
    
    return 0;
}

