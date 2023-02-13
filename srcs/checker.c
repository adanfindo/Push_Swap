/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:56:46 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_stack_ordered_2(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->size - 1)
	{
		if (stack->array[i] >= stack->array[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	stack_contains(t_stack *stack, int num)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->array[i++] == num)
			return (1);
	}
	return (0);
}

int	init_instructions(t_program *prg)
{
	int	ret;

	prg->instr = NULL;
	ret = get_instruction(&prg->instr);
	while (ret > 0)
		ret = get_instruction(&prg->instr);
	if (ret < 0)
	{
		free_instructions(prg->instr);
		free(prg->stack_a.array);
		free(prg->stack_b.array);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program	prg;

	if (--argc < 1)
		return (0);
	prg.debug = 0;
	if (init_stacks(argc, &argv[1], &prg.stack_a, &prg.stack_b))
		return (1);
	if (init_instructions(&prg))
		return (1);
	execute_instructions(prg.instr, &prg.stack_a, &prg.stack_b, prg.debug);
	if (is_stack_ordered_2(&prg.stack_a) || prg.stack_b.size)
		write(STDOUT_FILENO, "KO\n", 3);
	else
		write(STDOUT_FILENO, "OK\n", 3);
	free_prg(&prg);
	return (0);
}
