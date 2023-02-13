/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:02:42 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	execute_instructions(t_instruction *instr,
			t_stack *stack_a, t_stack *stack_b, int debug)
{
	while (instr)
	{
		if (!ft_strcmp(instr->line, "sa") || !ft_strcmp(instr->line, "ss"))
			swap_stack(stack_a);
		if (!ft_strcmp(instr->line, "sb") || !ft_strcmp(instr->line, "ss"))
			swap_stack(stack_b);
		if (!ft_strcmp(instr->line, "pa"))
			push_stack(stack_a, stack_b);
		if (!ft_strcmp(instr->line, "pb"))
			push_stack(stack_b, stack_a);
		if (!ft_strcmp(instr->line, "ra") || !ft_strcmp(instr->line, "rr"))
			rotate_stack(stack_a);
		if (!ft_strcmp(instr->line, "rb") || !ft_strcmp(instr->line, "rr"))
			rotate_stack(stack_b);
		if (!ft_strcmp(instr->line, "rra") || !ft_strcmp(instr->line, "rrr"))
			reverse_rotate_stack(stack_a);
		if (!ft_strcmp(instr->line, "rrb") || !ft_strcmp(instr->line, "rrr"))
			reverse_rotate_stack(stack_b);
		if (debug)
			print_instructions(instr);
		instr = instr->next;
	}
}

int	add_instruction_2(t_instruction **instructions, char *line)
{
	t_instruction	*tmp;
	t_instruction	*new;

	new = malloc(sizeof(t_instruction));
	if (!new)
		return (1);
	new->line = ft_strdup(line);
	new->next = NULL;
	tmp = *instructions;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*instructions = new;
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	while (n--)
	{
		tmp = (char *)s;
		*tmp = 0;
		s++;
	}
}

int	get_instruction(t_instruction **instructions)
{
	int		ret;
	char	line[4];

	ft_bzero(line, 4);
	ret = read(STDIN_FILENO, line, 3);
	if (line[0] == '\n' || line[1] == '\n')
		return (0);
	if (line[2] != 10 && (read(0, line + 3, 1) < 0 || line[3] != 10))
		return (-1);
	if (line[2] != '\n')
		line[3] = '\0';
	else
		line[2] = '\0';
	if (ft_strcmp(line, "sa") && ft_strcmp(line, "sb")
		&& ft_strcmp(line, "ss") && ft_strcmp(line, "pa")
		&& ft_strcmp(line, "pb") && ft_strcmp(line, "ra")
		&& ft_strcmp(line, "rb") && ft_strcmp(line, "rr")
		&& ft_strcmp(line, "rra") && ft_strcmp(line, "rrb")
		&& ft_strcmp(line, "rrr"))
		return (-1);
	if (ret <= 0 || add_instruction_2(instructions, line))
		return (-1);
	return (1);
}
