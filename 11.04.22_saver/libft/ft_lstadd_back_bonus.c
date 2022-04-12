/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:39:46 by dluba             #+#    #+#             */
/*   Updated: 2021/10/18 20:39:46 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_0;

	lst_0 = *lst;
	if (!lst || !new)
		return ;
	if (lst_0)
	{
		lst_0 = ft_lstlast(lst_0);
		lst_0->next = new;
		return ;
	}
	*lst = new;
}
