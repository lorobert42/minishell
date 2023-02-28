#include	"minishell.h"
#include	"libft.h"
#include	<readline/readline.h>
#include	<readline/history.h>

/*first part of longer series of function that redirect the input to
 * the right func*/
int	ft_findcmdp1(t_command *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->name, "echo", 4))
		ft_echo(cmd->args, 1);
	else if (!ft_strncmp(cmd->name, "pwd", 3))
		ft_pwd(env, 1);
	else if (!ft_strncmp(cmd->name, "env", 4))
		ft_env(env, 1);
	else if (!ft_strncmp(cmd->name, "cd", 2))
		ft_cd(cmd->args[0], &env);
	else if (!ft_strncmp(cmd->name, "getenv", 2))
		ft_unset(&env, cmd->args[0]);
	return (1);
}

/*A func that i'll need to rework that return the name of actual folder*/
char	*ft_getworkfoldername(void)
{
	int		len;
	int 	strt;
	char	pwd[PATH_MAX];
	char	*res;
	int		i;

	getcwd(pwd, PATH_MAX);
	res = 0;
	len = ft_strlen(pwd);
	i = len;
	while (len >= 0)
	{
		if (pwd[len] == '/')
		{
			strt = len + 1;
			res = ft_substr(pwd, strt, i - len);
			return (res);
		}
		len--;
	}
	return (0);
}

/* prototype for the main loop, it's kinda rough, but it'll look pretty :D */
void	ft_mainloop(t_env *env)
{
	t_readline	rl;
	t_command	cmd;

	while (1)
	{
		rl.uname = ft_strjoin(getenv("USER"), "@minishell ");
		rl.pwd = ft_strjoin(ft_getworkfoldername(), " % ");
		rl.display = ft_strjoin(rl.uname, rl.pwd);
		rl.pwd = ft_calloc(ft_strlen(rl.pwd), sizeof(char));
		rl.uname = ft_calloc(ft_strlen(rl.uname), sizeof(char));
		rl.cmd1d = readline(rl.display);
		rl.display = ft_calloc(ft_strlen(rl.display), sizeof(char));
		rl.cmd2d = ft_cmdparsing(rl.cmd1d);
		cmd = ft_addargs(rl.cmd2d);
		ft_findcmdp1(&cmd, env);
	}
}