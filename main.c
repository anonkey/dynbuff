/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/27 15:31:41 by tseguier          #+#    #+#             */
/*   Updated: 2014/09/27 18:33:09 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
typedef struct			s_dynstr
{
	t_ldcd				bufflist;
	unsigned long long	size;
	unsigned long		inc;
	unsigned long	offset;
}						t_sdynstr;

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

	while (ft_ldcdsize((*dstr_p)->bufflist) > 0)
	{
		str = ft_ldcdpop_back((*dstr_p)->bufflist);
		ft_strdel(&str);
	}
	ft_memdel((void **)dstr_p);
}

int		ft_dynstr_extend(t_dynstr dstr, unsigned long size)
{
	void	*buffer;

	if (!(buffer = ft_strnew(size + dstr->inc)))
		return (-1);
	if (-1 == ft_ldcdpush_back(dstr->bufflist, buffer, size + dstr->inc))
		return (-1);
	dstr->offset = 0;
	return (0);
}

int		ft_dynstradd(t_dynstr dstr, char *str)
{
	unsigned long	size;
	unsigned long	freebytes;

	size = ft_strlen(str);
	if (!(ft_ldcdsize(dstr->bufflist)) || dstr->bufflist->tail->content_size - dstr->offset < size)
	{
		if (dstr->bufflist->tail)
		{
			freebytes = dstr->bufflist->tail->content_size - dstr->offset;
			ft_strncpy((char *)(dstr->bufflist->tail->content + dstr->offset), str, freebytes);
			size -= freebytes;
			str += freebytes;
			dstr->size += freebytes;
		}
		if (-1 == ft_dynstr_extend(dstr, size))
			return (-1);
	}
	ft_strcpy((char *)(dstr->bufflist->tail->content + dstr->offset), str);
	dstr->offset += size;
	dstr->size += size;
	return (0);
}

int		ft_dynstrput(t_dynstr dstr)
{
	t_ldcd_cell		iter;

	iter = dstr->bufflist->head;
	while (iter)
	{
		//return (- 1 de write
		ft_putchar('\n');
		write(1, (char *)iter->content, iter->content_size);
		iter = iter->next;
	}
	return (dstr->size);
}

char		*ft_dynstrflush(t_dynstr dstr)
{
	char			*res;
	t_ldcd_cell		iter;
	unsigned long	size;

	size = 0;
	if (!(res = ft_strnew(dstr->size)))
		return (NULL);
	iter = dstr->bufflist->head;
	while (iter && iter->next)
	{
		ft_strncpy(res + size, (char *)iter->content, iter->content_size);
		size += iter->content_size;
		iter = iter->next;
	}
	ft_strncpy(res + size, (char *)iter->content, dstr->offset);
	res[size + dstr->offset] = '\0';
	ft_ldcddel(&(dstr->bufflist), &ft_memdel);
	return (res);
}

int		main(void)
{
	t_dynstr	dstr;
	int			i;
	char		*tmp;

	dstr = ft_dynstrnew(64);
	i = 0;
	while (i < 300000)
	{
		tmp = ft_itoa(rand());
		ft_dynstradd(dstr, tmp);
		ft_dynstradd(dstr, "||--||");
		free(tmp);
		++i;
	}
	ft_dynstrput(dstr);
	tmp = ft_dynstrflush(dstr);
	ft_putendl(tmp);
	ft_dynstrdel(&dstr);
	return (0);
}