#include "../rpc.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    reportable_t parent;

    char *str;
} my_struct_t;

void *parse_parameters(void *data)
{
    const char *buf = (const char *)(data);

    my_struct_t *d = (my_struct_t *)(malloc(sizeof(my_struct_t)));

    if (d)
    {
        d->str = strdup(buf);
    }

    return (void *)data;
}

void *do_work(void *data)
{

    char *input_str = (char *)data;
    int len = strlen(input_str);

    
    char *output_str = (char *)malloc(len + 1);     // Crear un buffer para la cadena invertida

   
    for (int i = 0; i < len; i++) {       // Invertir la cadena
        output_str[i] = input_str[len - i - 1];
    }
    output_str[len] = '\0';

    
    return output_str;   // Devolver la cadena invertida
}

reportable_t *report(void *data)
{
    my_struct_t *d = (my_struct_t *)(data);

    d->parent.data = strdup(d->str);
    d->parent.len = strlen(d->str);

    return (reportable_t *)(data);
}

void clean_up(void *params, void *result, reportable_t *report)
{
    if (result != NULL) {     // Liberar el buffer de la cadena invertida si existe
        free(result);
    }

    if (params != NULL) {         // Liberar el buffer de los parámetros si existe
        free(params);
    }

    if (report != NULL && report->data != NULL) {      // Liberar el buffer del informe si existe
        free(report->data);
        report->data = NULL;
    }
}
