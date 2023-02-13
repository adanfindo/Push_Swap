/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:03:02 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pick_solution_2(t_program *prg, t_state *states, t_state *solution)
{
	if (!solution)
		solution = states;
	if (solution->instructions)
	{
		execute_instructions(solution->instructions, &prg->stack_a,
			&prg->stack_b, prg->debug);
		prg->instr = copy_instructions(solution->instructions);
		if (!prg->instr)
		{
			free_states(states);
			return (1);
		}
	}
	return (0);
}

t_state	*add_states_2(t_state **states, t_state *new)
{
	t_state	*tmp;

	tmp = *states;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*states = new;
	return (new);
}

t_state	*new_empty_state_b(t_state *state, t_stack *stack_b, size_t max_size)
{
	if (stack_b)
		state->stack_b = copy_stack(stack_b);
	else
	{
		state->stack_b = new_empty_stack(max_size);
		if (!state->stack_b)
		{
			free_stack(state->stack_a);
			free(state);
			return (NULL);
		}
	}
	state->instructions = NULL;
	state->last_instr = NULL;
	state->next = NULL;
	return (state);
}
