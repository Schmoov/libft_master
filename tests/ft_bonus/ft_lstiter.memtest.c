#include <criterion/criterion.h>
#include <stdlib.h>
#include <ctype.h>
#include "libft.h"

void change_sign(void *val)
{
	*(int *)val = -*(int *)val;
}

void make_zero(void *val)
{
	*(int *)val = 0;
}

void scream(void *val)
{
	char	*s = *(char **)val->content;
	int	i = 0;
	while (s[i])
	{
		s[i] = toupper(s[i]);
		i++;
	}
}

void bob(void *val)
{
	char	*s = *(char **)val->content;
	int	i = 0;
	while (s[i])
	{
		if (i%2)
			s[i] = toupper(s[i]);
		else
			s[i] = tolower(s[i]);
		i++;
	}
}

void	idendity(void *osef)
{
	(void)	osef;
}

void	free_str(void *node)
{
	free((char *)((t_list *)node->content));
}

Test(lstiter, ints)
{
	int	a = 42;
	t_list	*node_a = ft_lstnew((void *)&a);
	int	b = 0;
	t_list	*node_b = ft_lstnew((void *)&b);
	int	c = -3583;
	t_list	*node_c = ft_lstnew((void *)&c);
	t_list	*lst = NULL;

	ft_lstadd_front(&lst, node_a);
	ft_lstadd_front(&lst, node_b);
	ft_lstadd_front(&lst, node_c);

	ft_lstiter(lst, change_sign);
	cr_expect_eq(*(int *)lst->content, 3583);
	cr_expect_eq(*(int *)lst->next->content, 0);
	cr_expect_eq(*(int *)lst->next->next->content, -42);

	ft_lstiter(lst, make_zero);
	cr_expect_eq(*(int *)lst->content, 0);
	cr_expect_eq(*(int *)lst->next->content, 0);
	cr_expect_eq(*(int *)lst->next->next->content, 0);

	ft_lstclear(&lst, identity);
}

Test(lstiter, strings)
{
	char	*str1 = strdup("Mammouth ecrase les prix");
	char	*str2 = strdup("Mamie ecrase les prouts");
	char	*str3 = strdup("Que d'humour !");
	t_list	*node_str1 = ft_lstnew((void *)&str1);
	t_list	*node_str2 = ft_lstnew((void *)&str2);
	t_list	*node_str3 = ft_lstnew((void *)&str3);
	t_list	*lst = NULL;

	ft_lstadd_front(&lst, node_str1);
	ft_lstadd_front(&lst, node_str2);
	ft_lstadd_front(&lst, node_str3);

	ft_lstiter(lst, scream);
	cr_expext_str_eq(*(char **)lst->content, "QUE D'HUMOUR !");
	cr_expext_str_eq(*(char **)lst->next->content, "MAMIE ECRASE LES PROUTS");
	cr_expext_str_eq(*(char **)lst->next->next->content, "MAMMOUTH ECRASE LES PRIX");

	ft_lstiter(lst, bob);
	cr_expext_str_eq(*(char **)lst->content, "qUe d'hUmOuR !");
	cr_expext_str_eq(*(char **)lst->next->content, "mAmIe eCrAsE LeS PrOuTs");
	cr_expext_str_eq(*(char **)lst->next->next->content, "mAmMoUtH EcRaSe lEs pRiX");


	ft_lstclear(&lst, free_str);
}
