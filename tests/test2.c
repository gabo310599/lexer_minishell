#include "../includes/lexer.h"
#include <stdio.h>

void print_lexer(t_lexer *lx)
{
    t_token *tok = lx->head;
    int tcount = 0;

    while (tok)
    {
        printf("token[%d]: ", tcount++);
        switch (tok->type)
        {
            case TOKEN_WORD:      printf("WORD\n"); break;
            case TOKEN_PIPE:      printf("PIPE\n"); break;
            case TOKEN_REDIR_IN:  printf("REDIR_IN\n"); break;
            case TOKEN_REDIR_OUT: printf("REDIR_OUT\n"); break;
            case TOKEN_HEREDOC:   printf("HEREDOC\n"); break;
            case TOKEN_APPEND:    printf("APPEND\n"); break;
            case TOKEN_EOF:       printf("EOF\n"); break;
            default:              printf("UNKNOWN\n"); break;
        }

        t_segment *seg = tok->segments;
        int scount = 0;
        while (seg)
        {
            printf("      segment[%d]: \"%s\" (expand=%d)\n", scount++, seg->str, seg->expand);
            seg = seg->next;
        }

        tok = tok->next;
    }
}

int main(void)
{
    const char *tests[] = {
        "hola",
        "hola mundo",
        "\"hola\"",
        "'hola'",
        "\"hola\"mundo",
        "hola\"mundo\"",
        "'hola'mundo",
        "'hola''mundo'",
        "\"hola\"\"mundo\"",
        "'hola'\"mundo\"",
        "\"\"test",
        "test\"\"",
        "\"a\"\"b\"\"c\"",
        "'a''b''c'",
        "cmd \"arg1\"arg2 'arg3'arg4",
        "echo 'a b' | cat > file.txt",
        "ls -la | grep \"Jan\" > output.txt",
        "<< EOF cat << EOF2",
        "echo '' \"\" ''\"\"",
        NULL
    };

    for (int i = 0; tests[i]; i++)
    {
        printf("================================\n");
        printf("INPUT: %s\n", tests[i]);
        printf("================================\n");
        t_lexer *lx = lexer_tokenize(tests[i]);
        if (lx)
        {
            print_lexer(lx);
            lexer_destroy(lx);
        }
        else
        {
            printf("Lexer returned NULL (error)\n");
        }
        printf("\n");
    }

    return 0;
}
