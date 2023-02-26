#include	"libft.h"
#include	"minishell.h"
#include	<stdlib.h>
#include	<readline/readline.h>
#include	<readline/history.h>

/*does a split on the string that contain the actual
 * command but before that, it is added in the history*/
char	**ft_cmdparsing(char *cmd)
{
	char **cmd2;

	if (!cmd)
		return (0);
	else
		add_history(cmd);
	cmd2 = ft_split(cmd, ' ');
	if (!cmd2)
		return (0);
	free (cmd);
	return (cmd2);
}

/*Takes the args from the splited command and copy them into their own array*/
char	**ft_parsingargs(char **args, int nbr)
{
	char	**args2;
	int		i;
	int		j;

	i = 0;
	j = 1;
	args2 = malloc(nbr * sizeof(char *) + 1);
	if (!args)
		return (0);
	while (i < nbr)
	{
		args2[i] = args[j];
		i++;
		j++;
	}
	return (args2);
}

/*create a t_command struct and store inside the name of the command
 * and the args that were given by the user, then it return the struct*/
t_command	ft_addargs(char **cmd)
{
	t_command	command;
	int			i;

	command.name = cmd[0];
	i = 0;
	while (cmd[i])
		i++;
	command.args = ft_parsingargs(cmd, i);
	return (command);
}
