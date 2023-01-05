#include <string.h>
#include "data.hpp"

void ft_bzero(void *s, size_t n)
{
	size_t i;
	unsigned char *l;

	l = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*(l + i) = 0;
		i++;
	}
}

std::string toUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void create_output(t_data *data, std::string msg)
{
    //for (size_t j = 0; j < msg.length(); j++)
        //data->output[j] = msg[j];
	msg += "\r\n";
	ft_strcpy(data->output, msg.c_str());
	std::cout << "output = " << data->output << std::endl;
}

char * ft_strcpy(char *dest, const char * src)
{
	char *ptr = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return ptr;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	signe;

	signe = 1;
	i = 0;
	number = 0;
	while (*str > 0 && *str <= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + i) >= 48 && *(str + i) <= 57)
		number = number * 10 + *(str + i++) - '0';
	return (number * signe);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != 0)
	{
		str++;
		count++;
	}
	return (count);
}

void get_host_name(t_data *data)
{
	char server_name_char[1024];

	gethostname(server_name_char, 1024);
	data->server_name = server_name_char;
	size_t pos = data->server_name.find_first_of('.', 0);
	data->server_name.erase(pos, data->server_name.length());
}