#pragma once

namespace veda {
	struct Contexts {
		static	VEDAcontext	current	(void);
		static	VEDAcontext	pop	(void);
		static	void		push	(VEDAcontext ctx);
		static	void		set	(VEDAcontext ctx);
		static void 		clear_current(void);
		static void 		remove(VEDAcontext ctx);
		static uint32_t 	get_ctx_ins(VEDAcontext ctx);
	};
}
