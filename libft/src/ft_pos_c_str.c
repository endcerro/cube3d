int ft_pos_c_str(char *str, char c)
{
	int i = -1;
	while(str[++i])
		if(str[i] == c)
			return i;
	return -1;
}

// int ft_pos_cs_str(char *str, char *str, int *pos)
// {
// 	int i = -1;
// 	while(str[++i])
// 		if(str[i] == c)
// 			return c;
// 	return 0;
// }