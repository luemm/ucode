import * as ubus from 'ubus';

function get_board(field) {
	let bus = ubus.connect();
	let bdstatus = null;

	if (bus) {
			bdstatus = bus.call("system", "board") || {};
			bus.disconnect();
			return bdstatus[field];
	}

	return "undefined";
}

let field=get_board(ARGV[0]);
print(field);
