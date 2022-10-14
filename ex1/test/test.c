#include "../ioctl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVPATH	"/dev/ioctl_test"
enum {
	RETURN_SUCCESS_VAL = 0,
	RETURN_FAIL_VAL = 1,
	RETURN_MAX_VAL,
};

int ioctl_set_val(int fd,  struct ioctl_arg *arg_set)
{
	int ret = -RETURN_FAIL_VAL;

	ret = ioctl(fd, IOCTL_VALSET, arg_set);
	if (ret < 0) {
		fprintf(stderr, "%s failed: %d\n", __func__, ret);
	}

	return ret;
}

int ioctl_get_val(int fd,  struct ioctl_arg *arg_get)
{
	int ret = -RETURN_FAIL_VAL;

	ret = ioctl(fd, IOCTL_VALGET, arg_get);
	if (ret < 0) {
		fprintf(stderr, "%s failed: %d\n", __func__, ret);
	} else {
		printf("%s success! arg_get.val = %d\n", __func__, arg_get->val);
	}

	return ret;
}

int ioctl_set_num_val(int fd, int* arg_set)
{
	int ret = -RETURN_FAIL_VAL;

	ret = ioctl(fd, IOCTL_VALSET_NUM, *arg_set);
	if (ret < 0) {
		fprintf(stderr, "%s failed: %d\n", __func__, ret);
	}

	return ret;
}

int ioctl_get_num_val(int fd, int* arg_get)
{
	int ret = -RETURN_FAIL_VAL;

	ret = ioctl(fd, IOCTL_VALGET_NUM, arg_get);
	if (ret < 0) {
		fprintf(stderr, "%s failed: %d\n", __func__, ret);
	} else {
		printf("%s success! arg_get.val = %d\n", __func__, *arg_get);
	}

	return ret;
}

int main(int argc, char** argv)
{
	int fd;
	int ret = -RETURN_FAIL_VAL;
	struct ioctl_arg ioctl_arg_set, ioctl_arg_get;
	int arg0, arg1, arg_get;

	/* Argument check */
	if (argc != 3) {
		fprintf(stderr, "Wrong argument count!\n");
		goto arg_notice;
	}

	arg0 = (int)(argv[1][0] - '0');
	arg1 = (int)(argv[2][0] - '0');
	if (arg0 < 0 || arg0 > 9 ||
		arg1 < 0 || arg0 > 9) {
		fprintf(stderr, "Wrong argument value! should between 0 - 9\n");
		fprintf(stderr, "Should between 0 - 9! arg0 = %c, arg1 = %c\n", argv[1][0], argv[2][0]);
		goto arg_notice;
	}

	/* Set argument */
	printf("arg0 = %d, arg1 = %d\n", arg0, arg1);
	ioctl_arg_set.val = arg0;

	/* Open dev */
	fd = open(DEVPATH, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "Cannot open device: %s\n", DEVPATH);
		goto out;
	}

	/* ioctl */
	ret = ioctl_set_val(fd, &ioctl_arg_set);
	if (ret) {
		fprintf(stderr, "ioctl_set_val return failed\n");
		goto close;
	}

	ret = ioctl_get_val(fd, &ioctl_arg_get);
	if (ret) {
		fprintf(stderr, "ioctl_get_val return failed\n");
		goto close;
	}

	ret = ioctl_set_num_val(fd, &arg1);
	if (ret) {
		fprintf(stderr, "ioctl_set_num_val return failed\n");
		goto close;
	}

	ret = ioctl_get_num_val(fd, &arg_get);
	if (ret) {
		fprintf(stderr, "ioctl_get_num_val return failed\n");
		goto close;
	}



	ret = RETURN_SUCCESS_VAL;	
	goto close;


arg_notice:
		fprintf(stderr, "plz use as ./test [0-9] [0-9]\n");
		goto out;
close:
		close(fd);
out:
	return ret;
}
