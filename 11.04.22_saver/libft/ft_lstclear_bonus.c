/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:21:49 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:22:06 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;
	t_list	*temp;

	elem = *lst;
	while (elem)
	{
		temp = elem;
		(*del)(elem->content);
		elem = temp->next;
		free(temp);
	}
	*lst = NULL;
}
