#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void print_error() {
    printf("Read error occured\n");
    exit(1);
}

int main()
{
    int word_count = 0;
    int last_char_was_word = 0;
    char buf[8192];

    while (1) {
        int res = fread(buf, 1, 8192, stdin);

        if (res == 0)
            break;
        else if (res < 0)
            print_error();

        int curr_index = 0;
        while (curr_index != res) {
            char c = buf[curr_index];

            if (c >= 9 && c <= 13 || c == 32) {
                if (last_char_was_word)
                    ++word_count;
                last_char_was_word = 0;
            } else {
                last_char_was_word = 1;
            }

            ++curr_index;
        }
    }

    if (last_char_was_word)
        ++word_count;

    printf("%d\n", word_count);
    return 0;
}