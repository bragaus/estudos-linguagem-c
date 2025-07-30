

long write_syscall(long fd, const void *buf, unsigned long count) {

    return __builtin_syscall(1, fd, buf, count);
}



void exit_syscall(int status) { __builtin_syscall(60, status);
}






void _start() {
    char msg[] = "Hello World!";




    

    write_syscall(1, msg, sizeof(msg) - 1);
    exit_syscall(0); 
}
