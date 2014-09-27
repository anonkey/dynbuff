/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/27 15:31:41 by tseguier          #+#    #+#             */
/*   Updated: 2014/09/27 16:28:55 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct		s_dynstr
{
	t_ldcd			bufflist;
	unsigned long	size;
	unsigned long	inc;
	long long		offset;
}					t_sdynstr;

typedef t_sdynstr	*t_dynstr;

t_dynstr	ft_dynstrnew(unsigned long inc)
{
	t_dynstr	str;

	if (!(str = (t_dynstr)ft_memalloc(sizeof(t_sdynstr))))
		return (NULL);
	if (!(str->bufflist = ft_ldcdnew()))
	{
		ft_memdel((void **)&str);
		return (NULL);
	}
	str->inc = inc;
	return (str);
}

void	ft_dynstrdel(t_dynstr *dstr_p)
{
	char	*str;

	while (ft_ldcdsize((*dstr_p)->bufflist))
	{
		str = ft_ldcdpop_back((*dstr_p)->bufflist);
		ft_strdel(&str);
	}
	ft_memdel((void **)dstr_p);
}

int		main(void)
{
	t_dynstr	dstr;

	dstr = ft_dynstrnew(64);
	ft_dynstrdel(&dstr);
	return (0);
}