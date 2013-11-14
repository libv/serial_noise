/*
 * Copyright (c) 2013 Luc Verhaegen <libv@skynet.be>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 * Really trivial program to make constant noise on many available serial
 * busses, so that UART pins may be found. Copyright is ascertained to at
 * least attempt to mitigate some of the stupidity of android forums, and
 * to perhaps see some changes get back to linux-sunxi.org from time to time.
 *
 * For usage information, please refer to http://linux-sunxi.org/UART
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SERIAL_COUNT 8

int
main(int argc, char *argv[])
{
	char filename[64];
	FILE *fds[SERIAL_COUNT] = {NULL, };
	int i, ret, found;

	if (argc != 1) {
		printf("\n");
		printf("Copyright (c) 2013 Luc Verhaegen <libv@skynet.be>\n");
		printf("\n");
		printf("This program is free software; you can redistribute it "
		       "and/or modify it\n");
		printf("under the terms of the GNU General Public License as "
		       "published by the\n");
		printf("Free Software Foundation; either version 2 of the "
		       "License, or (at your\n");
		printf("option) any later version.\n");
		printf("\n");
		printf("This program is distributed in the hope that it will be"
		       " useful, but\n");
		printf("WITHOUT ANY WARRANTY; without even the implied warranty"
		       " of\n");
		printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. "
		       "See the GNU\n");
		printf("General Public License for more details.\n");
		printf("\n");
		printf("You should have received a copy of the GNU General "
		       "Public License along\n");
		printf("with this program; if not, write to the Free Software "
		       "Foundation, Inc.,\n");
		printf("59 Temple Place, Suite 330, Boston, MA 02111-1307 "
		       "USA\n");
		printf("\n");
		printf("For more information, refer to "
		       "http://linux-sunxi.org/UART\n");
		printf("\n");
		return 0;
	}

	for (i = 0; i < SERIAL_COUNT; i++) {
		ret = snprintf(filename, sizeof(filename), "/dev/ttyS%d", i);
		if (ret <= 0) {
			printf("error writing filename!\n");
			continue;
		}

		fds[i] = fopen(filename, "w");
		if (!fds[i]) {
			printf("Error: failed to open %s: %s\n", filename,
			       strerror(errno));
			continue;
		}

	}

	printf("Flooding serial consoles with text...\n");

	while (1) {
		for (i = 0, found = 0; i < SERIAL_COUNT; i++) {
			if (!fds[i])
				continue;

			found = 1;

			ret = fprintf(fds[i], "UART%d\n", i);
			if (ret > 0)
				continue;

			printf("Error: failed to write to ttyS%d: %s\n",
			       i, strerror(errno));
			fclose(fds[i]);
			fds[i] = NULL;
		}

		if (!found) {
 			printf("Error: No serial consoles found. Exiting.\n");
			return -1;
		}

		usleep(20000);
	}

	return 0;
}
