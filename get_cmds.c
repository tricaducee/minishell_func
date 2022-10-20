#include "get_cmds.h"
#include <stdio.h>//----------------------------------------------
size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strslen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char			*ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	ret	= malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char			*ret;
	unsigned int	i;
	unsigned int	f_len;

	if (!s)
		return (0);
	f_len = ft_strlen(s);
	if (start >= f_len)
		return (ft_strdup(""));
	if (len > f_len - start)
		len = f_len - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*split_cmd(char *cmdline, unsigned int *i, char c)
{
	unsigned int	j;

	j = 0;
	while (cmdline[*i + j] && (cmdline[*i + j] == c))
		++j;
	*i += j;
	return (ft_substr(cmdline, *i - j, j));
}

char	**ft_strsjoin(char *s, char **ss)
{
	char			**ret;
	unsigned int	i;

	ret	= malloc((ft_strslen(ss) + 2) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (ss && ss[i])
	{
		ret[i] = ss[i];
		++i;
	}
	ret[i] = s;
	ret[++i] = 0;
	return (ret);
}

char	*split_cmd_sp(char *cmdline, unsigned int *i)
{
	unsigned int	j;

	j = 0;
	while (cmdline[*i + j] && cmdline[*i + j]
			!= ' ' && cmdline[*i + j] != '<' && cmdline[*i + j]
			!= '>' && cmdline[*i + j] != '|' && cmdline[*i + j] != '&')
		++j;
	*i += j;
	return (ft_substr(cmdline, *i - j, j));
}


void	print_tab(char **s)
{
	while (*s)
		printf("%s\n", *(s++));
}

void	free_tab(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}


t_cmdli	*get_cmds(char *cmdline)
{
	unsigned int	i;
	t_cmdli			*cmds_list;
	char			**cmds_tab;
	char			**tmp;

	i = 0;
	cmds_list = NULL;
	cmds_tab = NULL;
	while (cmdline[i])
	{
		while (cmdline[i] == ' ') //all white space
			++i;
		tmp = cmds_tab;
		if (cmdline[i] == '<')
			cmds_tab = ft_strsjoin(split_cmd(cmdline, &i, '<'), cmds_tab);
		else if (cmdline[i] == '>')
			cmds_tab = ft_strsjoin(split_cmd(cmdline, &i, '>'), cmds_tab);
		else if (cmdline[i] == '|')
			cmds_tab = ft_strsjoin(split_cmd(cmdline, &i, '|'), cmds_tab);
		else if (cmdline[i] == '&')
			cmds_tab = ft_strsjoin(split_cmd(cmdline, &i, '&'), cmds_tab);
		else
			cmds_tab = ft_strsjoin(split_cmd_sp(cmdline, &i), cmds_tab);
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	print_tab(cmds_tab);
	free_tab(cmds_tab);
	return (cmds_list);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	get_cmds(av[1]);
	return (0);
}
