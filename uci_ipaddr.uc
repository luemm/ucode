'use strict';

import { cursor } from 'uci';

function get_ipaddr(itf) {
	let ctx = cursor();
	let lanip = ctx.get('network',itf,'ipaddr');

	if (lanip==null)
		lanip='undefined';

	return lanip;
}

let itf = ARGV[0];
let lip = get_ipaddr(itf);
print( {UCI: { IP : lip} });
