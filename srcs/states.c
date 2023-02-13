/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:14:51 by afindo            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_state	*new_state_instruction(t_state **states, t_state *old_state,
	char *line)
{
	t_state			*state;
	t_instruction	*instr;

	state = add_state(states, old_state);
	if (!state)
		return (NULL);
	instr = add_instruction(&state->instructions, line);
	if (!instr)
	{
		free_states(state);
		return (NULL);
	}
	state->last_instr = instr;
	execute_instructions(instr, state->stack_a, state->stack_b, 0);
	return (state);
}

void	free_states(t_state *states)
{
	t_state	*tmp;
	t_state	*next;

	tmp = states;
	while (tmp)
	{
		next = tmp->next;
		free_stack(tmp->stack_a);
		free_stack(tmp->stack_b);
		free_instructions(tmp->instructions);
		free(tmp);
		tmp = next;
	}
}

t_state	*add_state(t_state **states, t_state *state_from)
{
	t_state	*new;

	new = malloc(sizeof(t_state));
	if (!new)
		return (NULL);
	new->stack_a = NULL;
	new->stack_b = NULL;
	new->instructions = NULL;
	new->last_instr = NULL;
	new->next = NULL;
	new->stack_a = copy_stack(state_from->stack_a);
	new->stack_b = copy_stack(state_from->stack_b);
	new->instructions = copy_instructions(state_from->instructions);
	if (!new->stack_a || !new->stack_b || (state_from->instructions
			&& !new->instructions))
	{
		free_states(new);
		return (NULL);
	}
	return (add_states_2(states, new));
}

t_state	*new_empty_state(t_stack *stack_a, t_stack *stack_b,
	size_t max_size)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	if (stack_a)
		state->stack_a = copy_stack(stack_a);
	else
	{
		state->stack_a = new_empty_stack(max_size);
		if (!state->stack_a)
		{
			free(state);
			return (NULL);
		}
	}
	return (new_empty_state_b(state, stack_b, max_size));
}
