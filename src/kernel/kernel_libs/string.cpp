/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include <kernel/kernel_libs/string.h>

void *memset(void *s, int c, size_t n) {
    auto *p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}
int atoi(const char *nptr) {
    int c;
    int neg = 0;
    int val = 0;

    // TODO: Don't fucking do this
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\r' || *nptr == '\f' || *nptr == '\v') {
        nptr++;
    }

    if (*nptr == '-') {
        neg = 1;
        nptr++;
    } else if (*nptr == '+') {
        nptr++;
    }

    while ((c = *nptr++ - '0') >= 0 && c <= 9) {
        val = val * 10 + c;
    }

    return neg ? -val : val;
}

char *itoa(int value, char *str, int base) {
    char *p = str;
    char *p1;
    char *p2;
    unsigned long v;
    int divisor = 10;

    /* If base is 10 and value is negative, put `-' in front. */
    if (base == 10 && value < 0) {
        *p++ = '-';
        v = -value;
    } else {
        v = (unsigned long)value;
    }

    /* Pre-compute the divisor for specified base. */
    if (base == 10) {
        divisor = 10;
    } else if (base == 16) {
        divisor = 16;
    } else if (base == 8) {
        divisor = 8;
    } else if (base == 2) {
        divisor = 2;
    } else {
        return nullptr;
    }

    /* Divide the value by the divisor and convert the result to a character. */
    do {
        int remainder = v % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (v /= divisor);

    /* Terminate the string. */
    *p = 0;

    /* Reverse the string. */
    p1 = str;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return str;
}

char *strcpy(char *s1, const char *s2) {
    char *dst = s1;
    const char *src = s2;
    while (*src)
        *dst++ = *src++;
    *dst = '\0'; // Spec says include null terminator.
    return s1;
}