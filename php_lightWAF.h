#ifndef PHP_LIGHTWAF_H
	#define PHP_LIGHTWAF_H 1
	
	#define PHP_LIGHTWAF_EXTNAME	"lightWAF"
	#define PHP_LIGHTWAF_EXTVER		"1.0"
	
	#ifdef HAVE_CONFIG_H
	#include "config.h"
	#endif
	
	#include "php.h"
	
	extern zend_module_entry lightWAF_module_entry;
	#define phpext_lightWAF_ptr &lightWAF_module_entry
	
#endif
