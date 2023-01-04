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