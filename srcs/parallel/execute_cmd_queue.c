/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_queue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:40 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:04:54 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			execute_cmd_queue(cl_command_queue cmd_queue)
{
	if (clk_flush(cmd_queue) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_finish(cmd_queue) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
