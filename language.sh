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

if [ $# -eq 0 ];then 
	echo 'Usage: /root/mkusers userfile'
exit 1
fi
if [ ! -f $1 ];then
	echo  "Input file not found"
exit 1
fi
while read line 
do
useradd -s  /bin/false  $line
done < $1 
