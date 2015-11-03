PHP_ARG_ENABLE(lightWAF,
	[Whether to enable the "lightWAF" extension],
	[	enable-lightWAF		Enable "lightWAF" extension support])

if test $PHP_LIGHTWAF != "no"; then
	PHP_SUBST(LIGHTWAF_SHARED_LIBADD)
	PHP_NEW_EXTENSION(lightWAF, lightWAF.c, $ext_shared)
fi
