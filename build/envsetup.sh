#BUILD_SYSTEM=build/core
#export CLEAR_VARS=${BUILD_SYSTEM}/clear_vars.mk
#export BUILD_SHARED_LIBRARY=${BUILD_SYSTEM}/rule_shared_library.mk

#function findmakefile()
#{
#    TOPFILE=build/core/envsetup.mk
#    local HERE=$PWD
#    T=
#    while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
#        T=`PWD= /bin/pwd`
#        if [ -f "$T/Android.mk" -o -f "$T/Android.bp" ]; then
#            echo $T/Android.mk
#            \cd $HERE
#            return
#        fi
#        \cd ..
#    done
#\cd $HERE
#}

#M=$(findmakefile)
#echo ${M}

echo "include build/target/cygwin.mk" > Makefile
echo "include build/core/main.mk" >> Makefile

