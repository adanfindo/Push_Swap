/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:13:40 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	execute_instructions(t_instruction *instr, t_stack *stack_a,
t_stack *stack_b, int debug)
{
	while (instr)
	{
		if (debug)
			print_instruction(instr);
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
			print_stacks(stack_a, stack_b);
		instr = instr->next;
	}
}

t_instruction	*copy_and_concat_instructions(t_instruction **instr,
t_instruction *new)
{
	t_instruction	*ptr;
	t_instruction	*tmp_instr;

	tmp_instr = *instr;
	if (tmp_instr)
	{
		while (tmp_instr->next)
			tmp_instr = tmp_instr->next;
		tmp_instr->next = copy_instructions(new);
		if (!tmp_instr->next)
			return (NULL);
		ptr = tmp_instr->next;
		((t_instruction *)tmp_instr->next)->prev = tmp_instr;
	}
	else
	{
		*instr = copy_instructions(new);
		ptr = *instr;
	}
	return (ptr);
}

t_instruction	*copy_instructions(t_instruction *instructions)
{
	t_instruction	*new;

	new = NULL;
	while (instructions)
	{
		if (!(add_instruction(&new, instructions->line)))
		{
			free_instructions(new);
			return (NULL);
		}
		instructions = instructions->next;
	}
	return (new);
}

t_instruction	*add_n_instructions(t_instruction **instructions, char *line,
size_t n)
{
	t_instruction	*start;

	start = NULL;
	if (n > 0)
	{
		start = add_instruction(instructions, line);
		if (!start)
			return (NULL);
		n--;
		while (n > 0)
		{
			if (!(add_instruction(instructions, line)))
			{
				free_instructions(start);
				return (NULL);
			}
			n--;
		}
	}
	return (start);
}

t_instruction	*add_instruction(t_instruction **instructions, char *line)
{
	t_instruction	*tmp;
	t_instruction	*new;

	new = malloc(sizeof(t_instruction));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	if (!new->line)
	{
		free(new);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	tmp = *instructions;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		new->prev = tmp;
		tmp->next = new;
	}
	else
		*instructions = new;
	return (new);
}
