/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:11:28 by tbesson           #+#    #+#             */
/*   Updated: 2021/12/02 20:37:05 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		len;
	int		i;

	if (!s1)
		return (0);
	while (*s1 && ft_ischarset(*s1, set))
		s1++;
	len = ft_strlen(s1) - 1;
	while (len >= 0 && ft_ischarset(s1[len], set))
		len--;
	trim = malloc((len + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (s1[i] && i <= len)
	{
		trim[i] = s1[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
