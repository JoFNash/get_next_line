/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsybassi <hsybassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:22:07 by hsybassi          #+#    #+#             */
/*   Updated: 2022/01/03 23:37:16 by hsybassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

// все strjoin надо проверить на NULL!

char	*get_next_line(int fd)
{
	char		*result_string;
	static char *remains;
	char 		buff[BUFFER_SIZE + 1];
	char		*temp;
	int			read_symbols;

	//printf("TUT! remains: |%s|\n", remains);
	result_string = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	read_symbols = 1;
	while (read_symbols > 0)
	{
		read_symbols = read(fd, buff, BUFFER_SIZE);
		if (read_symbols < 0)
			return (NULL);
		buff[read_symbols] = '\0';
		if (!remains)
			remains = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(remains, buff);
			free(remains);
			remains = temp;
		}
		if (ft_strchr(remains, '\n')) // если наткнулись на '\n'
		{
			break;
		}
	}
	result_string = get_result(remains);
	remains = get_remains(&remains);
	if(result_string== NULL)
	{
		free(remains);
		remains = NULL;
	}
	return (result_string);
}
