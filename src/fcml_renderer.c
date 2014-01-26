/*
 * fcml_rend.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include <fcml_renderer.h>
#include "fcml_dialect_int.h"
#include "fcml_trace.h"

fcml_ceh_error fcml_fn_render( fcml_st_dialect *dialect, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags ) {
	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)dialect;
	if( dialect_context_int->instruction_renderer ) {
		fcml_fnp_render_instruction renderer = (fcml_fnp_render_instruction)dialect_context_int->instruction_renderer;
		return renderer( dialect, output_stream, result, render_flags );
	} else {
		/* Dialect not initialized correctly.*/
		FCML_TRACE_MSG("Rendering not supported by current dialect.");
		return FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
	}
}