/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sad-aude <sad-aude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:35:55 by sad-aude          #+#    #+#             */
/*   Updated: 2020/07/30 14:15:47 by sad-aude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_longprec_for_hexa(char *str, int hexa, char *temp, t_spec *spec)
{
	int	i;

	i = 0;
	if (spec->prec < spec->len)
	{
		if (spec->is_sharp)
		{
			if (!(str = ft_strjoin(temp, str, 3)))
				return (NULL);
		}
		else
			ft_strdel(&temp);
		if (spec->is_majhexa)
			ft_strcapitalize(str);
		return (str);
	}
	if (spec->is_sharp && hexa != 0)
		i = 2;
	while (spec->diff++ < (spec->prec - spec->len))
		temp[i++] = '0';
	if (!(str = ft_strjoin(temp, str, 3)))
		return (NULL);
	if (spec->is_majhexa)
		ft_strcapitalize(str);
	return (str);
}

char	*apply_prec_for_hexa(char *str, int hexa, t_spec *spec)
{
	char	*temp;

	if (str[0] == '0' && spec->prec == 0)
	{
		ft_strdel(&str);
		if (!(str = ft_stringnew(0)))
			return (NULL);
		return (str);
	}
	if (spec->is_sharp && hexa != 0)
	{
		if (!(temp = ft_stringnew(2 + spec->prec)))
			return (NULL);
		temp[0] = '0';
		temp[1] = 'x';
	}
	else
	{
		if (!(temp = ft_stringnew(spec->prec)))
			return (NULL);
	}
	spec->len = ft_strlen(str);
	str = apply_longprec_for_hexa(str, hexa, temp, spec);
	return (str);
}

char	*apply_width_for_hexa(char *str, int hexa, t_spec *spec)
{
	if (spec->is_sharp && hexa != 0)
	{
		if (spec->is_majhexa)
			spec->count += write(1, "0X", 2);
		else
			spec->count += write(1, "0x", 2);
		while (spec->diff++ < spec->width - spec->len - 2)
			spec->count += write(1, "0", 1);
	}
	else
		while (spec->diff++ < spec->width - spec->len)
			spec->count += write(1, "0", 1);
	return (str);
}

char	*apply_longwidth_for_hexa(char *str, int hexa, t_spec *spec)
{
	int indic;

	indic = 0;
	if (spec->is_sharp && hexa != 0 && !spec->is_minus && !spec->is_prec)
	{
		spec->width -= 2;
		while (indic++ < spec->width - spec->len)
			spec->count += write(1, " ", 1);
		if (spec->is_majhexa)
			spec->count += write(1, "0X", 2);
		else
			spec->count += write(1, "0x", 2);
	}
	else
	{
		if (spec->is_zero && spec->is_star && spec->prec < 0)
			while (indic++ < spec->width - spec->len)
				spec->count += write(1, "0", 1);
		else
			while (indic++ < spec->width - spec->len)
				spec->count += write(1, " ", 1);
	}
	return (str);
}

char	*check_width_for_hexa(char *str, int hexa, t_spec *spec)
{
	spec->len = ft_strlen(str);
	if (spec->is_minus)
	{
		if (spec->is_sharp && hexa != 0 && !spec->is_prec)
		{
			spec->width -= 2;
			if (spec->is_majhexa)
				spec->count += write(1, "0X", 2);
			else
				spec->count += write(1, "0x", 2);
		}
		spec->count += write(1, str, ft_strlen(str));
	}
	if (spec->is_zero && !spec->is_prec && !spec->is_minus)
		str = apply_width_for_hexa(str, hexa, spec);
	else
		str = apply_longwidth_for_hexa(str, hexa, spec);
	if (!spec->is_minus)
		spec->count += write(1, str, ft_strlen(str));
	return (str);
}
