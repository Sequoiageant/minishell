
#include "libft.h"
#include "mshell.h"

void    print_pipe_bufs(t_list *pipe_list)
{
    t_list *cmd_list;
    t_cmd *cmd;

    cmd_list = (t_list*)pipe_list->content;
    while (cmd_list)
    {
        cmd = (t_cmd*)cmd_list->content;
        printf("buf: [%s]\n", cmd->buf);               
        cmd_list = cmd_list->next;
    }
}

void    print_pipe_redirs(t_list *pipe_list)
{
    t_list *cmd_list;
    t_cmd *cmd;

    cmd_list = (t_list*)pipe_list->content;
    while (cmd_list)
    {
        cmd = (t_cmd*)cmd_list->content;
        if (cmd->input_file)
            printf("redir: input_file");
        if (cmd->output_file)
            printf("redir: output_file");
        if (cmd->output_file_append)
            printf("redir: output_file append");
        printf("file: [%s]\n", cmd->file);        
        cmd_list = cmd_list->next;
    }
}

void    print_pipe_argvs(t_list *pipe_list)
{
    t_list  *cmd_list;
    t_cmd   *cmd;
    int     i;

    cmd_list = (t_list*)pipe_list->content;
    while (cmd_list)
    {
        cmd = (t_cmd*)cmd_list->content;
        i = 0;
        while (cmd->argv[i])
        {
            printf("argv[%d]: [%s]\n", i, cmd->argv[i]);
            i++;
        }
        cmd_list = cmd_list->next;
    }
}

void print_commands(t_list *pipe_list)
{
    while (pipe_list)
    {
        printf("PIPE >> \n");
        // print_pipe_bufs(pipe_list);
        // print_pipe_redirs(pipe_list);
        print_pipe_argvs(pipe_list);
        pipe_list = pipe_list->next;
    }
}