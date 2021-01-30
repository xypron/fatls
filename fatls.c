// SPDX-License-Identifier: GPL-2.0+
/*
 *  List FAT directory
 *
 *  Copyright (c) 2021 Heinrich Schuchardt
 */

#include <fcntl.h>
#include <linux/msdos_fs.h>
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	struct __fat_dirent entry[2];
	int fd;
	int ret;
	uint32_t id;
	int files = 0;
	int dirs = 0;
	unsigned long long bytes = 0;

	setlocale(LC_ALL, "");

	if (argc != 2) {
		printf("Usage: %s DIRECTORY\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*
	 * Open file descriptor for the directory.
	 */
	fd = open(argv[1], O_RDONLY | O_DIRECTORY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	ret = fchdir(fd);
	if (ret == -1) {
		perror("fchdir");
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, FAT_IOCTL_GET_VOLUME_ID, &id);
	if (ret == -1) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}
	printf("\nVolume ID %04x-%04x\n", id >> 16, id & 0xFFFF);

	printf("Directory %s\n\n", argv[1]);

	for (;;) {
		struct stat pstat;
		char buf[40];
		struct tm *tm;

		/*
		 * Read next directory entry.
		 */
		ret = ioctl(fd, VFAT_IOCTL_READDIR_BOTH, entry);

		/*
		 * If an error occurs, the return value is -1.
		 * If the end of the directory list has been reached,
		 * the return value is 0.
		 * For backward compatibility the end of the directory
		 * list is also signaled by d_reclen == 0.
		 */
		if (ret < 1)
			break;

		if (*entry[1].d_name)
			ret = stat(entry[1].d_name, &pstat);
		else
			ret = stat(entry[0].d_name, &pstat);
		if (ret == -1) {
			printf("%-35s ", "stat() failed");
			goto nostat;
		}

		tm = gmtime(&pstat.st_ctim.tv_sec);

		ret = strftime(buf, sizeof(buf), "%F %T", tm);
		if (!ret) {
			printf("%-35s ", "strftime() failed");
			goto nostat;
		}

		printf("%s ", buf);
		if (S_ISDIR(pstat.st_mode)) {
			printf("%-15s ", "<DIR>");
			++dirs;
		} else {
			printf("%'15llu ", (unsigned long long)pstat.st_size);
			++files;
			bytes += pstat.st_size;
		}

nostat:
		/*
		 * Write both the short name and the long name.
		 */
		printf("%-12s %s\n", entry[0].d_name, entry[1].d_name);
	}

	if (ret == -1) {
		perror("VFAT_IOCTL_READDIR_BOTH");
		exit(EXIT_FAILURE);
	}

	/*
	 * Close the file descriptor.
	 */
	close(fd);

	printf("%13d Files %'15llu bytes\n", files, bytes);
	printf("%13d Directories\n", dirs);

	exit(EXIT_SUCCESS);
}
