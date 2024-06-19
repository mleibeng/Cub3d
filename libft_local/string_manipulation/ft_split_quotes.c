/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:34:02 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/29 14:18:38 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_wordcount(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	*word_dupe(char *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

int	handle_quoted_substring(char *str, int *i, int *word_index, char **array)
{
	char	quote;
	int		start_index;

	quote = str[(*i)++];
	start_index = *i;
	while (str[*i] != '\0' && str[*i] != quote)
	{
		++(*i);
	}
	while (start_index < *i && (str[start_index] == ' '
			|| str[start_index] == '\t'))
	{
		++start_index;
	}
	while (*i > start_index && (str[*i - 1] == ' ' || str[*i - 1] == '\t'))
	{
		--(*i);
	}
	array[(*word_index)++] = word_dupe(&str[start_index], *i - start_index);
	if (str[*i] != '\0')
	{
		++(*i);
	}
	return (*i);
}

char	**ft_split_quotes(char *str)
{
	int		i;
	int		word_index;
	char	**array;
	int		start_index;

	i = 0;
	word_index = 0;
	array = malloc(sizeof(char *) * (ft_wordcount(str) + 1));
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			++i;
		if (ft_isquote(str[i]))
			i = handle_quoted_substring(str, &i, &word_index, array);
		else
		{
			start_index = i;
			while (str[i] != '\0' && !ft_isquote(str[i]) && str[i] != ' '
				&& str[i] != '\t' && str[i] != '\n')
				++i;
			array[word_index++] = word_dupe(&str[start_index], i - start_index);
		}
	}
	array[word_index] = 0;
	return (array);
}
