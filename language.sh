#!/bin/bash
#language config file  edit by ycl
#command   obj
ucfg get config language > /tmp/language.conf
ENABLE=`ucfg get config language ENABLE | sed 's/ENABLE=//g'`

#!/bin/bash
#language config file lte_sim_pin.cgi.c_language_flag edit by ycl
#command obj
ucfg get config languagepin > /tmp/languagepin.conf
ENABLE=`ucfg get config languagepin ENABLE | sed 's/ENABLE=//g'`

#/bin/bash
case  $1  in
bar)
	echo 'foo'
;;
foo)
	echo 'bar'
;;
*)
	echo '/root/script foo|bar'
;;
esac
