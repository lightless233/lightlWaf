#include "php_lightWAF.h"
#include "ext/standard/info.h"
#include "zend_execute.h"

#include <string.h>
#include <sys/stat.h>

static zend_function_entry lightWAF_functions[] = {
	
	{NULL, NULL, NULL}
};

/* LIGHT_DO_FCALL */
static int LIGHT_DO_FCALL(ZEND_OPCODE_HANDLER_ARGS)
{
	char *filePath;
	struct stat st;
	int nRev_st = 0;

	php_printf("[Debug] ZEND_DO_FCALL\n<br />");

	filePath = zend_get_executed_filename(TSRMLS_C);
	php_printf("[Debug] filePath: %s\n<br />", filePath);

	if (strstr(filePath, "/upload/"))
	{
		/* 非法调用，拦截 */	
		php_printf("[Warning] Execute command via system() etc.\n<br />");
		return ZEND_USER_OPCODE_RETURN;
	}
	else	/* Not Found */
	{
		/* 合法调用，放行 */
		return ZEND_USER_OPCODE_DISPATCH;
	}
}

/* LIGHT_DO_FCALL_BY_NAME */
static int LIGHT_DO_FCALL_BY_NAME(ZEND_OPCODE_HANDLER_ARGS)
{
	char *filePath = zend_get_executed_filename(TSRMLS_C);
	
	php_printf("[Debug] ZEND_DO_FCALL_BY_NAME\n<br />");
	
	php_printf("[Debug] filePath: %s\n<br />", filePath);

	if (strstr(filePath, "/upload/"))
	{
		/* 非法调用，拦截 */
		php_printf("[Warning] Execute command via variable.\n<br />");
		return ZEND_USER_OPCODE_RETURN;
	}
	else /* Not Found */
	{
		/* 合法调用，放行 */
		return ZEND_USER_OPCODE_DISPATCH;
	}
}

/* LIGHT_INCLUDE_OR_EVAL */
static int LIGHT_INCLUDE_OR_EVAL(ZEND_OPCODE_HANDLER_ARGS)
{
	char *filePath = zend_get_executed_filename(TSRMLS_C);
	
	php_printf("[Debug] ZEND_INCLUDE_OR_EVAL\n<br />");
	
	php_printf("[Debug] filePath: %s\n<br />", filePath);

	if ( strstr(filePath, "/upload/") )
	{
		/* 非法调用，拦截 */
		php_printf("[Warning] Execute command via include or eval.\n<br />");
		return ZEND_USER_OPCODE_RETURN;
	}
	else /* Not Found */
	{
		/* 合法调用，放行 */
		return ZEND_USER_OPCODE_DISPATCH;
	}
}

ZEND_MINIT_FUNCTION(lightWAF)
{
	/*
	 * hook掉ZEND_DO_FCALL
	 * 处理system函数等
	 */
	zend_set_user_opcode_handler(ZEND_DO_FCALL, LIGHT_DO_FCALL);

	/*
	 * hook掉ZEND_DO_FCALL_BY_NAME
	 * 处理$func='system';$func();等类型
	 */
	zend_set_user_opcode_handler(ZEND_DO_FCALL_BY_NAME, LIGHT_DO_FCALL_BY_NAME);

	/*
	 * hook掉ZEND_INCLUDE_OR_EVAL
	 * 处理eval, require等
	 */
	zend_set_user_opcode_handler(ZEND_INCLUDE_OR_EVAL, LIGHT_INCLUDE_OR_EVAL);

	return SUCCESS;
}

ZEND_MSHUTDOWN_FUNCTION(lightWAF)
{
	return SUCCESS;
}

ZEND_RINIT_FUNCTION(lightWAF)
{
	return SUCCESS;
}

ZEND_RSHUTDOWN_FUNCTION(lightWAF)
{
	return SUCCESS;
}

ZEND_MINFO_FUNCTION(lightWAF)
{
}

zend_module_entry lightWAF_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_LIGHTWAF_EXTNAME,
	lightWAF_functions,
	ZEND_MINIT(lightWAF),
	ZEND_MSHUTDOWN(lightWAF),
	ZEND_RINIT(lightWAF),
	ZEND_RSHUTDOWN(lightWAF),
	ZEND_MINFO(lightWAF),
	PHP_LIGHTWAF_EXTVER,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LIGHTWAF
	ZEND_GET_MODULE(lightWAF)
#endif
