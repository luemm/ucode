#include <unistd.h>
#include "ucode/module.h"

static uc_resource_type_t *display_type;

void delay_print(char *str,int msec)
{
    useconds_t usec = msec * 1000;
    for (char *p = str; *p; p++) {
        putchar(*p);
        fflush(stdout);
        usleep(usec);
    }
    putchar('\n');
}

static uc_value_t *
uc_display_error(uc_vm_t *vm, size_t nargs)
{
	uc_value_t *errmsg;
 
	errmsg = ucv_string_new("cinuc error");

	return errmsg;
}

static uc_value_t *
uc_display_ctx(uc_vm_t *vm, size_t nargs)
{
	uc_value_t *c = uc_fn_arg(0);
 	int *delay;

	delay = malloc(sizeof(int));	
	*delay = atoi(ucv_string_get(c));

	return(uc_resource_new(display_type, delay));
}

static uc_value_t *
uc_display_print(uc_vm_t *vm, size_t nargs)
{
	int **delay = uc_fn_this("cinuc.display");
	uc_value_t *conf = uc_fn_arg(0);

	delay_print(ucv_string_get(conf),**delay);
 
	return ucv_boolean_new(true);
}

static const uc_function_list_t display_fns[] = {
	{ "dprint",		uc_display_print },
};
 
static const uc_function_list_t global_fns[] = {
	{ "error",		uc_display_error },
	{ "display",		uc_display_ctx },
};
 
 
static void close_display(void *ud) {
	free((int*)ud);
}
 
void uc_module_init(uc_vm_t *vm, uc_value_t *scope)
{
	uc_function_list_register(scope, global_fns);
 
	display_type = uc_type_declare(vm, "cinuc.display", display_fns, close_display);
}
