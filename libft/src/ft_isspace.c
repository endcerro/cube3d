#include "../libft.h"

int ft_isspace(char *in)
{
	if (*in == ' ' || *in == '	' || *in == '\n'|| *in == '\t' || *in == '\v' || *in == '\f' || *in == '\r')
		return(1);
	return(0);
}