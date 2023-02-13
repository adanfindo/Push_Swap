/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:14:35 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	count_instructions(t_instruction *ins)
{
	size_t	nb;

	nb = 0;
	while (ins)
	{
		nb++;
		ins = ins->next;
	}
	return (nb);
}

int	pick_solution(t_program *prg, t_state *states)
{
	t_state	*solution;
	t_state	*tmp_state;

	solution = NULL;
	tmp_state = states->next;
	while (tmp_state)
	{
		if (!solution || count_instructions(tmp_state->instructions)
			< count_instructions(solution->instructions))
			solution = tmp_state;
		tmp_state = tmp_state->next;
	}
	return (pick_solution_2(prg, states, solution));
}

int	realign_and_fill_a(t_program *prg)
{
	t_instruction	*tmp;

	if (prg->stack_b.size > 1 && align_stack_b(prg))
		return (1);
	while (prg->stack_b.size)
	{
		if (prg->stack_b.array[0] > prg->stack_a.array[prg->stack_a.size - 1]
			|| (prg->stack_b.array[0] < prg->stack_a.array[0]
				&& prg->stack_a.array[0]
				< prg->stack_a.array[prg->stack_a.size - 1]))
			tmp = add_instruction(&prg->instr, "pa");
		else
			tmp = add_instruction(&prg->instr, "rra");
		if (!tmp)
			return (1);
		execute_instructions(tmp, &prg->stack_a, &prg->stack_b, prg->debug);
	}
	if (align_stack_a(prg))
		return (1);
	return (0);
}

int	resolve(t_program *prg)
{
	t_state	*states;

	states = new_empty_state(&prg->stack_a, &prg->stack_b,
			prg->stack_a.max_size);
	if (!states)
		return (1);
	if (prg->stack_a.size > 5
		&& (create_states_resolution(&states) || large_resolve(states)))
		return (1);
	if (pick_solution(prg, states))
		return (1);
	free_states(states);
	if (bruteforce_order_a(prg))
		return (1);
	if (realign_and_fill_a(prg))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program	pg;

	if (--argc < 1)
		return (0);
	pg.debug = 0;
	if (init_stacks(argc, &argv[1], &pg.stack_a, &pg.stack_b))
		return (1);
	pg.instr = NULL;
	if (pg.stack_a.size && is_stack_ordered(&pg.stack_a, ASC) && resolve(&pg))
	{
		free_instructions(pg.instr);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	print_instructions(pg.instr);
	free_prg(&pg);
	return (0);
}
