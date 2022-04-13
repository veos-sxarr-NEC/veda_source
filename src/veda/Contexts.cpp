#include "veda.hpp"

namespace veda {
//------------------------------------------------------------------------------
thread_local std::list<VEDAcontext> t_stack;

//------------------------------------------------------------------------------
VEDAcontext Contexts::current(void) {
	if(t_stack.empty())
		throw VEDA_ERROR_UNKNOWN_CONTEXT;
	if(t_stack.back()->is_handle_valid() == false)
	{
		throw VEDA_ERROR_CONTEXT_IS_DESTROYED;
	}
	return t_stack.back();
}

//------------------------------------------------------------------------------

VEDAcontext Contexts::pop(void) {
	auto ctx = current();
	t_stack.pop_back();
	ctx->dec_ref_count(1);
	return ctx;
}

//------------------------------------------------------------------------------

void Contexts::push(VEDAcontext ctx) {
	t_stack.emplace_back(ctx);
	ctx->inc_ref_count();
}


//------------------------------------------------------------------------------

void Contexts::remove(VEDAcontext ctx) {
	t_stack.remove(ctx);
}

//------------------------------------------------------------------------------

void Contexts::clear_current(void) {
	t_stack.clear();
}

//------------------------------------------------------------------------------
uint32_t Contexts::get_ctx_ins(VEDAcontext ctx) {
	uint32_t count = 0;
	for (auto it=t_stack.begin(); it != t_stack.end(); ++it)
	{
		if(*it == ctx)
			count++;
	}
	return count;
}

//------------------------------------------------------------------------------

void Contexts::set(VEDAcontext ctx) {
	if(ctx) {
		if(t_stack.empty())	t_stack.emplace_back(ctx);
		else			t_stack.back() = ctx;
		ctx->inc_ref_count();
	} else {
		if(!t_stack.empty()) {
			t_stack.back()->dec_ref_count(1);
			t_stack.pop_back();
		}
	}
}

//------------------------------------------------------------------------------
}
