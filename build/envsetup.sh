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

function set_stuff_for_environment()
{
    #settitle
    #set_java_home
    #setpaths
    #set_sequence_number

    #export ANDROID_BUILD_TOP=$(gettop)
    # With this environment variable new GCC can apply colors to warnings/errors
    export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'
    export ASAN_OPTIONS=detect_leaks=0
}


# Clear this variable.  It will be built up again when the vendorsetup.sh
# files are included at the end of this file.
unset LUNCH_MENU_CHOICES
function add_lunch_combo()
{
    local new_combo=$1
    local c
    for c in ${LUNCH_MENU_CHOICES[@]} ; do
        if [ "$new_combo" = "$c" ] ; then
            return
        fi
    done
    LUNCH_MENU_CHOICES=(${LUNCH_MENU_CHOICES[@]} $new_combo)
}


function print_lunch_menu()
{
    local uname=$(uname)
    echo
    echo "You're building on" $uname
    echo
    echo "Lunch menu... pick a combo:"

    local i=1
    local choice
    for choice in ${LUNCH_MENU_CHOICES[@]}
    do
        echo "     $i. $choice"
        i=$(($i+1))
    done

    echo
}


function lunch()
{
    local answer

    if [ "$1" ] ; then
        answer=$1
    else
        print_lunch_menu
        echo -n "Which would you like? [Auto] "
        read answer
    fi

    local selection=

    if [ -z "$answer" ]
    then
        selection=Auto
    elif (echo -n $answer | grep -q -e "^[0-9][0-9]*$")
    then
        if [ $answer -le ${#LUNCH_MENU_CHOICES[@]} ]
        then
            selection=${LUNCH_MENU_CHOICES[$(($answer-1))]}
        fi
    elif (echo -n $answer | grep -q -e "^[^\-][^\-]*-[^\-][^\-]*$")
    then
        selection=$answer
    fi

    if [ -z "$selection" ]
    then
        echo
        echo "Invalid lunch combo: $answer"
        return 1
    fi

    export TARGET_BUILD_APPS=

    local variant=$(echo -n $selection | sed -e "s/^[^\-]*-//")
    #check_variant $variant
    #if [ $? -ne 0 ]
    #then
    #    echo
    #    echo "** Invalid variant: '$variant'"
    #    echo "** Must be one of ${VARIANT_CHOICES[@]}"
    #    variant=
    #fi

    local product=$(echo -n $selection | sed -e "s/-.*$//")
    #TARGET_PRODUCT=$product \
    #TARGET_BUILD_VARIANT=$variant \
    #build_build_var_cache
    #if [ $? -ne 0 ]
    #then
    #    echo
    #    echo "** Don't have a product spec for: '$product'"
    #    echo "** Do you have the right repo manifest?"
    #    product=
    #fi

    #if [ -z "$product" -o -z "$variant" ]
    #then
    #    echo
    #    return 1
    #fi

    #export TARGET_PRODUCT=$product
    #export TARGET_BUILD_VARIANT=$variant
    #export TARGET_BUILD_TYPE=release

    echo

    set_stuff_for_environment
    #printconfig
    #destroy_build_var_cache

    build_host_file $selection
    if [ "$LUNCH_BUILD_HOST" ]
    then
        echo "include $LUNCH_BUILD_HOST" > Makefile
        echo "include build/core/main.mk" >> Makefile
    fi
}

unset LUNCH_BUILD_HOST
function build_host_file()
{
    local host

    if [ "$1" ] ; then
        host=$1
    else
        host=Auto
    fi

    if [ $host = Auto ] 
    then
        host=$(uname -o)
    fi

    if [ $host = Cygwin ]
    then
        LUNCH_BUILD_HOST=build/target/cygwin.mk
    else
        echo unknown build host machine ...
    fi
}

add_lunch_combo Auto
add_lunch_combo Cygwin
