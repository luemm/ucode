import * as cubus from 'ubus';

let ubus = cubus.connect();

let main_obj = {
	get_arg: {
		args: {
			argin: "input",
		},
		call: function(req) {
			let input = req.args.argin;
			return {input:input};
		}
	},
	get_pid: {
		call: function(req) {
			let pid = getpid();
			return {pid:pid};
		}
	},
};

gdata.ubus = ubus;
gdata.obj = ubus.publish("ubus_obj", main_obj);
