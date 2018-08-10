/*
 * Converts IPADDRESS to CIDR, or returns CIDR if already a valid one
 * Copyright (C) 2018 z0noxz, <chris@noxz.tech>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ip2cidr.h"

const char *usage = "usage: ip2cidr <IP>";

/* HAKMEM bit counter (item 169) */
int
bit_count(unsigned int u) {
    unsigned int u_count;

    u_count = u - ((u >> 1) & 0333333333333) - ((u >> 2) & 011111111111);
    return ((u_count + (u_count >> 3)) & 030707070707) % 63;
}

int
main(int argc, char **argv) {
    int ip, cidr,
        n1, n2, n3, n4, input_size;
    int buffer_size = 80;
    char buffer[buffer_size];
    char *input;

    /* validate input from STDIN */
    if (!isatty(fileno(stdin)) && fgets(buffer, buffer_size, stdin) != NULL) {
        input_size = strlen(buffer);
        input = malloc(input_size);
        input[0] = '\0';
        strcat(input, buffer);

    /* validate input from CLI */
    } else if (argc == 2) {
        input_size = strlen(argv[1]);
        input = malloc(input_size);
        input[0] = '\0';
        strcat(input, argv[1]);

    /* no valid input, so show usage */
    } else {
        fprintf(stderr, "%s\n", usage);
        return 1;
    }

    /* validate ip address */
    if (
        sscanf(input, "%d.%d.%d.%d", &n1, &n2, &n3, &n4) == 4 &&
        n1 >= 0 && n1 <= 255 &&
        n2 >= 0 && n2 <= 255 &&
        n3 >= 0 && n3 <= 255 &&
        n4 >= 0 && n4 <= 255
    ) {
        ip      = n1 * 0x1000000u + n2 * 0x10000u + n3 * 0x100u + n4;
        cidr    = bit_count(ip);

        /* check if ip is a valid subnet mask (all ones are in succession) */
        if (cidr < 1 || cidr > 32 || ip != (0xffffffffu >> (32-cidr) << (32-cidr))) {
            fprintf(stderr, "error: not a subnet mask\n");
            return 1;
        }
    } else if (sscanf(input, "%d", &cidr) == 1 && cidr >= 1 && cidr <= 32) {
    } else {
        fprintf(stderr, "error: not a correctly formed ip address\n");
        return 1;
    }

    /* finally print the CIDR */
    printf("%d\n", cidr);
    return 0;
}
