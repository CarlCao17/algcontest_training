#include<cstdio>
#include<cstring>

char code[8][1 << 8];

int readchar() {
    for(;;) {
        int ch = getchar();
        if(ch != '\n' && ch != '\r') return ch; // 返回 EOF 或者非换行符
    }
}

int readcodes() {
    memset(code, 0, sizeof(code));
    int ch = readchar();
    if(ch == EOF) return 0;
    code[1][0] = ch;
    for(int i = 2; i < 8; i++) {
        for(int j = 0; j < (1<<i)-1; j++) {
            int ch = getchar();
            if(ch == EOF) return 0;
            if(ch == '\r' || ch == '\n') return 1;
            code[i][j] = (char)ch;
        }
    }
    return 1;
}

int readint(int n) {
    int res = 0;
    for(int i = 0; i < n; i++) {
        res = res * 2 + readchar() - '0';
    }
    return res;
}

int main() {
    while(readcodes()) {
        for(;;) {
            int len = readint(3);
            if(len == 0) break;
            for(;;) {
                int num = readint(len);
                if(num == ((1<<len)-1)) break;
                putchar(code[len][num]);
            }
        }
        putchar('\n');
    }
    return 0;
}