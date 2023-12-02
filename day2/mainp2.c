#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 32KiB should be enough for parsing the whole file.
#define MAX_FILE_SIZE (32*1024)

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    FILE* fp = fopen("input.txt", "rb");
    if (fp == NULL)
        return 1;

    char buf[MAX_FILE_SIZE] = {};
    int n = fread(buf, sizeof*buf, sizeof buf, fp);

    if (n < 1)
        return 1;

    int sum = 0;
    int current_id = 0;
    int current_val = 0;
    int red = 1, green = 1, blue = 1;
    for (int i = 0; i < n; ++i) {
        if (buf[i] == 'G' && strncmp(&buf[i], "Game", 4) == 0) {
            i += 4;
            if (buf[i] == ' ')
                i += 1;

            if (buf[i + 1] == ':')
                current_id = buf[i++] - '0';
            else if (buf[i + 2] == ':') {
                current_id = (int)(buf[i] - '0') * 10 + (int)(buf[i+1] - '0');
                i += 2;
            } else if (buf[i + 3] == ':') {
                current_id = (int)(buf[i] - '0') * 100 + (int)(buf[i+1] - '0') * 10 + (int)(buf[i+2] - '0');
                i += 3;
            } else {
                int orig_idx = i;
                while (isdigit((unsigned char)buf[i++]))
                    continue;

                buf[i++] = 0;
                current_id = atoi(&buf[orig_idx]);
            }
        } else if (isdigit((unsigned char)buf[i])) {
            int value = buf[i++] - '0';
            
            if (isdigit((unsigned char)buf[i])) {
                value = value * 10 + (int)(buf[i++] - '0');
            }

            current_val = value;
        } else if (buf[i] == 'r' && strncmp(&buf[i], "red", 3) == 0) {
            red = max(current_val, red);
        } else if (buf[i] == 'g' && strncmp(&buf[i], "green", 5) == 0) {
            green = max(current_val, green);
        } else if (buf[i] == 'b' && strncmp(&buf[i], "blue", 4) == 0) {
            blue = max(current_val, blue);
        } else if (buf[i] == '\n' || buf[i] == 0) {
            sum += red * green * blue;

            red = 1;
            green = 1;
            blue = 1;
        }
    }

    printf("%d\n", sum);
}
