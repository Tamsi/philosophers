/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:58:26 by tbesson           #+#    #+#             */
/*   Updated: 2021/12/03 11:26:41 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char const *str, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[i] && c == str[i])
		i++;
	while (str[i] && c != str[i])
	{
		i++;
		len++;
	}
	return (len);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		while (c == str[i] && str[i])
			i++;
		if (c != str[i] && str[i])
		{
			count++;
			while (c != str[i] && str[i])
				i++;
		}
	}
	return (count);
}

static char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < count_words(s, c))
	{
		j = 0;
		tab[i] = malloc((ft_word_len(&s[k], c) + 1) * sizeof(char));
		if (!tab[i])
			return (ft_free_tab(tab));
		while (c == s[k] && s[k])
			k++;
		while (c != s[k] && s[k])
			tab[i][j++] = s[k++];
		tab[i++][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
