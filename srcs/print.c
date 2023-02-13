/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:53:07 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_instruction(t_instruction *instr)
{
	write(STDOUT_FILENO, instr->line, ft_strlen(instr->line));
	write(STDOUT_FILENO, "\n", 1);
}

void	print_instructions(t_instruction *instr)
{
	while (instr)
	{
		print_instruction(instr);
		instr = instr->next;
	}
}

void	print_bottom_stack(int max_size_nbr[2])
{
	write(STDOUT_FILENO, "	", 1);
	write_n_char(max_size_nbr[0], '_');
	write(STDOUT_FILENO, " ", 1);
	write_n_char(max_size_nbr[1], '_');
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "	", 1);
	write_n_char(max_size_nbr[0] - 1, ' ');
	write(STDOUT_FILENO, "a ", 2);
	write_n_char(max_size_nbr[1] - 1, ' ');
	write(STDOUT_FILENO, "b", 1);
	write(STDOUT_FILENO, "\n", 1);
}

void	print_numbers_stacks(int max_size, int max_size_nbr[2],
	t_stack *stack_a, t_stack *stack_b)
{
	int	i;

	i = -1;
	while (++i < max_size)
	{
		write(STDOUT_FILENO, "	", 1);
		if ((int)(stack_a->size - max_size + i) >= 0)
			write_n_char(max_size_nbr[0]
				- size_nbr(stack_a->array[stack_a->size - max_size + i]), ' ');
		if ((int)(stack_a->size - max_size + i) >= 0)
			ft_putnbr(stack_a->array[stack_a->size - max_size + i]);
		else
			write_n_char(max_size_nbr[0], ' ');
		write(STDOUT_FILENO, " ", 1);
		if ((int)(stack_b->size - max_size + i) >= 0)
			write_n_char(max_size_nbr[1]
				- size_nbr(stack_b->array[stack_b->size - max_size + i]), ' ');
		if ((int)(stack_b->size - max_size + i) >= 0)
			ft_putnbr(stack_b->array[stack_b->size - max_size + i]);
		else
			write_n_char(max_size_nbr[1], ' ');
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int	max_size_nbr[2];
	int	max_size;

	max_size = stack_a->size;
	if (stack_b->size > stack_a->size)
		max_size = stack_b->size;
	write(STDOUT_FILENO, "stacks\n", 7);
	max_size_nbr[0] = get_max_size_nbr_stack(stack_a);
	max_size_nbr[1] = get_max_size_nbr_stack(stack_b);
	print_numbers_stacks(max_size, max_size_nbr, stack_a, stack_b);
	print_bottom_stack(max_size_nbr);
}
