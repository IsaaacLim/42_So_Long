#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd;
	int 	ret;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("line: %s\n", line);
			free(line);
		}
		if (ret == 0)
			printf("EOF\n");
		if (ret == -1)
			printf("Error\n");
		close(fd);
	}
	else
		printf("Input argument\n");
}