#include <stdio.h>

#include <ucode/compiler.h>
#include <ucode/lib.h>
#include <ucode/vm.h>
#include <libubus.h>

static uc_parse_config_t config = {
	.strict_declarations = false,
	.lstrip_blocks = true,
	.trim_blocks = true,
	.raw_mode = true
};

uc_value_t *uc_getpid(uc_vm_t *vm, size_t nargs)
{
	return ucv_int64_new(getpid());
}

static int ucode_run(uc_vm_t *vm, const char *script)
{
	uc_source_t *source;
	uc_program_t *prog;
	uc_value_t *ops;
	char *err;
	int ret;

	source = uc_source_new_file(script);
	if (!source) {
		fprintf(stderr, "error opening ucode\n");
		return -1;
	}

	prog = uc_compile(vm->config, source, &err);
	uc_source_put(source);
	if (!prog) {
		fprintf(stderr, "error conpiling ucode: %s\n", err);
		return -1;
	}

	ret = uc_vm_execute(vm, prog, &ops);
	uc_program_put(prog);
	if (ret) {
		fprintf(stderr, "error executing ucode: %i\n", ret);
		return -1;
	}

	return 0;
}

int main()
{
	uc_vm_t vm = { 0 };

	uloop_init();

	uc_search_path_init(&config.module_search_path);
	uc_vm_init(&vm, &config);
	uc_stdlib_load(uc_vm_scope_get(&vm));

	ucv_object_add(uc_vm_scope_get(&vm), "gdata", ucv_get(ucv_object_new(&vm)));
	uc_function_register(uc_vm_scope_get(&vm), "getpid", uc_getpid);

	if (ucode_run(&vm,"ubus_obj.uc"))
		goto free_vm;
	ucv_gc(&vm);

	uloop_run();

	uloop_done();

free_vm:
	uc_search_path_free(&vm.config->module_search_path);
	uc_vm_free(&vm);
}
