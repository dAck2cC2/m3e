function hmm() {
cat <<EOF
Invoke ". build/envsetup.sh" from your shell to add the following functions to your environment:
- lunch:     lunch <product_name>-<build_variant>
- croot:     Changes directory to the top of the tree.
- m:         Makes from the top of the tree.
- mm:        Builds all of the modules in the current directory, but not their dependencies.
- mmm:       Builds all of the modules in the supplied directories, but not their dependencies.
             To limit the modules being built use the syntax: mmm dir/:target1,target2.
- mma:       Builds all of the modules in the current directory, and their dependencies.
- mmma:      Builds all of the modules in the supplied directories, and their dependencies.
- cgrep:     Greps on all local C/C++ files.
- resgrep:   Greps on all local res/*.xml files.
- mgrep:     Greps on all local Makefiles files.
- treegrep:  Greps on all local source files not including Makefiles.
- sgrep:     Greps on all local source files including Makefiles.
- godir:     Go to the directory containing a file.

Environment options:
- SANITIZE_HOST: Set to 'true' to use ASAN for all host modules. Note that
                 ASAN_OPTIONS=detect_leaks=0 will be set by default until the
                 build is leak-check clean.

Look at the source to view more functions. The complete list is:
EOF
    T=$(gettop)
    local A
    A=""
    for i in `cat $T/build/envsetup.sh | sed -n "/^[[:blank:]]*function /s/function \([a-z_]*\).*/\1/p" | sort | uniq`; do
      A="$A $i"
    done
    echo $A
}


function gettop
{
    local TOPFILE=build/core/envsetup.mk
    if [ -n "$TOP" -a -f "$TOP/$TOPFILE" ] ; then
        # The following circumlocution ensures we remove symlinks from TOP.
        (cd $TOP; PWD= /bin/pwd)
    else
        if [ -f $TOPFILE ] ; then
            # The following circumlocution (repeated below as well) ensures
            # that we record the true directory name and not one that is
            # faked up with symlink names.
            PWD= /bin/pwd
        else
            local HERE=$PWD
            T=
            while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
                \cd ..
                T=`PWD= /bin/pwd -P`
            done
            \cd $HERE
            if [ -f "$T/$TOPFILE" ]; then
                echo $T
            fi
        fi
    fi
}

# Return driver for "make", if any (eg. static analyzer)
function getdriver()
{
    local T="$1"
#    test "$WITH_STATIC_ANALYZER" = "0" && unset WITH_STATIC_ANALYZER
#    if [ -n "$WITH_STATIC_ANALYZER" ]; then
#        echo "\
#$T/prebuilts/misc/linux-x86/analyzer/tools/scan-build/scan-build \
#--use-analyzer $T/prebuilts/misc/linux-x86/analyzer/bin/analyzer \
#--status-bugs \
#--top=$T"
#    fi
}

function croot()
{
    T=$(gettop)
    if [ "$T" ]; then
        \cd $(gettop)
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}


function findmakefile()
{
    TOPFILE=build/core/envsetup.mk
    local HERE=$PWD
    T=
    while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
        T=`PWD= /bin/pwd`
        if [ -f "$T/Android.mk" -o -f "$T/Android.bp" ]; then
            echo $T/Android.mk
            \cd $HERE
            return
        fi
        \cd ..
    done
\cd $HERE
}

function m()
{
    local T=$(gettop)
    local DRV=$(getdriver $T)
    if [ "$T" ]; then
        $DRV make -C $T $@
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
        return 1
    fi
}

function mm()
{
    local T=$(gettop)
    local DRV=$(getdriver $T)
    # If we're sitting in the root of the build tree, just do a
    # normal make.
    if [ -f build/core/envsetup.mk -a -f Makefile ]; then
        $DRV make $@
    else
        # Find the closest Android.mk file.
        local M=$(findmakefile)
        local MODULES=
        local GET_INSTALL_PATH=
        local ARGS=
        # Remove the path to top as the makefilepath needs to be relative
        local M=`echo $M|sed 's:'$T'/::'`
        if [ ! "$T" ]; then
            echo "Couldn't locate the top of the tree.  Try setting TOP."
            return 1
        elif [ ! "$M" ]; then
            echo "Couldn't locate a makefile from the current directory."
            return 1
        else
            for ARG in $@; do
                case $ARG in
                  GET-INSTALL-PATH) GET_INSTALL_PATH=$ARG;;
                esac
            done
            if [ -n "$GET_INSTALL_PATH" ]; then
              MODULES=
              ARGS=GET-INSTALL-PATH
            else
              MODULES=all_modules
              ARGS=$@
            fi
            ONE_SHOT_MAKEFILE=$M $DRV make -C $T $MODULES $ARGS
        fi
    fi
}

function mmm()
{
    local T=$(gettop)
    local DRV=$(getdriver $T)
    if [ "$T" ]; then
        local MAKEFILE=
        local MODULES=
        local ARGS=
        local DIR TO_CHOP
        local GET_INSTALL_PATH=
        local DASH_ARGS=$(echo "$@" | awk -v RS=" " -v ORS=" " '/^-.*$/')
        local DIRS=$(echo "$@" | awk -v RS=" " -v ORS=" " '/^[^-].*$/')
        for DIR in $DIRS ; do
            MODULES=`echo $DIR | sed -n -e 's/.*:\(.*$\)/\1/p' | sed 's/,/ /'`
            if [ "$MODULES" = "" ]; then
                MODULES=all_modules
            fi
            DIR=`echo $DIR | sed -e 's/:.*//' -e 's:/$::'`
            if [ -f $DIR/Android.mk ]; then
                local TO_CHOP=`(\cd -P -- $T && pwd -P) | wc -c | tr -d ' '`
                local TO_CHOP=`expr $TO_CHOP + 1`
                local START=`PWD= /bin/pwd`
                local MFILE=`echo $START | cut -c${TO_CHOP}-`
                if [ "$MFILE" = "" ] ; then
                    MFILE=$DIR/Android.mk
                else
                    MFILE=$MFILE/$DIR/Android.mk
                fi
                MAKEFILE="$MAKEFILE $MFILE"
            else
                case $DIR in
                  showcommands | snod | dist | *=*) ARGS="$ARGS $DIR";;
                  GET-INSTALL-PATH) GET_INSTALL_PATH=$DIR;;
                  *) if [ -d $DIR ]; then
                         echo "No Android.mk in $DIR.";
                     else
                         echo "Couldn't locate the directory $DIR";
                     fi
                     return 1;;
                esac
            fi
        done
        if [ -n "$GET_INSTALL_PATH" ]; then
          ARGS=$GET_INSTALL_PATH
          MODULES=
        fi
        ONE_SHOT_MAKEFILE="$MAKEFILE" $DRV make -C $T -f build/core/main.mk $DASH_ARGS $MODULES $ARGS
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
        return 1
    fi
}

function mma()
{
  local T=$(gettop)
  local DRV=$(getdriver $T)
  if [ -f build/core/envsetup.mk -a -f Makefile ]; then
    $DRV make $@
  else
    if [ ! "$T" ]; then
      echo "Couldn't locate the top of the tree.  Try setting TOP."
      return 1
    fi
    local MY_PWD=`PWD= /bin/pwd|sed 's:'$T'/::'`
    local MODULES_IN_PATHS=MODULES-IN-$MY_PWD
    # Convert "/" to "-".
    MODULES_IN_PATHS=${MODULES_IN_PATHS//\//-}
    $DRV make -C $T $@ $MODULES_IN_PATHS
  fi
}

function mmma()
{
  local T=$(gettop)
  local DRV=$(getdriver $T)
  if [ "$T" ]; then
    local DASH_ARGS=$(echo "$@" | awk -v RS=" " -v ORS=" " '/^-.*$/')
    local DIRS=$(echo "$@" | awk -v RS=" " -v ORS=" " '/^[^-].*$/')
    local MY_PWD=`PWD= /bin/pwd`
    if [ "$MY_PWD" = "$T" ]; then
      MY_PWD=
    else
      MY_PWD=`echo $MY_PWD|sed 's:'$T'/::'`
    fi
    local DIR=
    local MODULES_IN_PATHS=
    local ARGS=
    for DIR in $DIRS ; do
      if [ -d $DIR ]; then
        # Remove the leading ./ and trailing / if any exists.
        DIR=${DIR#./}
        DIR=${DIR%/}
        if [ "$MY_PWD" != "" ]; then
          DIR=$MY_PWD/$DIR
        fi
        MODULES_IN_PATHS="$MODULES_IN_PATHS MODULES-IN-$DIR"
      else
        case $DIR in
          showcommands | snod | dist | *=*) ARGS="$ARGS $DIR";;
          *) echo "Couldn't find directory $DIR"; return 1;;
        esac
      fi
    done
    # Convert "/" to "-".
    MODULES_IN_PATHS=${MODULES_IN_PATHS//\//-}
    $DRV make -C $T $DASH_ARGS $ARGS $MODULES_IN_PATHS
  else
    echo "Couldn't locate the top of the tree.  Try setting TOP."
    return 1
  fi
}

function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep --color -n "$@" {} +
}

function resgrep()
{
    for dir in `find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -name res -type d`; do
        find $dir -type f -name '*\.xml' -exec grep --color -n "$@" {} +
    done
}

case `uname -s` in
    Darwin)
        function mgrep()
        {
            find -E . -name .repo -prune -o -name .git -prune -o -path ./out -prune -o -type f -iregex '.*/(Makefile|Makefile\..*|.*\.make|.*\.mak|.*\.mk)' \
                -exec grep --color -n "$@" {} +
        }

        function treegrep()
        {
            find -E . -name .repo -prune -o -name .git -prune -o -type f -iregex '.*\.(c|h|cpp|S|java|xml)' \
                -exec grep --color -n -i "$@" {} +
        }

        function sgrep()
        {
            find -E . -name .repo -prune -o -name .git -prune -o  -type f -iregex '.*\.(c|h|cc|cpp|S|java|xml|sh|mk|aidl|vts)' \
                -exec grep --color -n "$@" {} +
        }

        ;;
    *)
        function mgrep()
        {
            find . -name .repo -prune -o -name .git -prune -o -path ./out -prune -o -regextype posix-egrep -iregex '(.*\/Makefile|.*\/Makefile\..*|.*\.make|.*\.mak|.*\.mk)' -type f \
                -exec grep --color -n "$@" {} +
        }

        function treegrep()
        {
            find . -name .repo -prune -o -name .git -prune -o -regextype posix-egrep -iregex '.*\.(c|h|cpp|S|java|xml)' -type f \
                -exec grep --color -n -i "$@" {} +
        }

        function sgrep()
        {
            find . -name .repo -prune -o -name .git -prune -o  -type f -iregex '.*\.\(c\|h\|cc\|cpp\|S\|java\|xml\|sh\|mk\|aidl\|vts\)' \
                -exec grep --color -n "$@" {} +
        }

        ;;
esac

function godir () {
    if [[ -z "$1" ]]; then
        echo "Usage: godir <regex>"
        return
    fi
    T=$(gettop)
    if [ ! "$OUT_DIR" = "" ]; then
        mkdir -p $OUT_DIR
        FILELIST=$OUT_DIR/filelist
    else
        FILELIST=$T/filelist
    fi
    if [[ ! -f $FILELIST ]]; then
        echo -n "Creating index..."
        (\cd $T; find . -wholename ./out -prune -o -wholename ./.repo -prune -o -type f > $FILELIST)
        echo " Done"
        echo ""
    fi
    local lines
    lines=($(\grep "$1" $FILELIST | sed -e 's/\/[^/]*$//' | sort | uniq))
    if [[ ${#lines[@]} = 0 ]]; then
        echo "Not found"
        return
    fi
    local pathname
    local choice
    if [[ ${#lines[@]} > 1 ]]; then
        while [[ -z "$pathname" ]]; do
            local index=1
            local line
            for line in ${lines[@]}; do
                printf "%6s %s\n" "[$index]" $line
                index=$(($index + 1))
            done
            echo
            echo -n "Select one: "
            unset choice
            read choice
            if [[ $choice -gt ${#lines[@]} || $choice -lt 1 ]]; then
                echo "Invalid choice"
                continue
            fi
            pathname=${lines[$(($choice-1))]}
        done
    else
        pathname=${lines[0]}
    fi
    \cd $T/$pathname
}

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

    if [ $selection = Auto ]
    then
	answer=$(echo -n $(uname) | sed -e "s/_.*//")
    else
	answer=$selection
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

    build_host_file $answer
    if [ "$LUNCH_BUILD_HOST" ]
    then
	echo "### DO NOT EDIT THIS FILE ###" > Makefile
        echo "include $LUNCH_BUILD_HOST" >> Makefile
        echo "include build/core/main.mk" >> Makefile
	echo "### DO NOT EDIT THIS FILE ###" >> Makefile
    fi
}

unset LUNCH_BUILD_HOST
function build_host_file()
{
    #echo $1
    if [ $1 = CYGWIN ]
    then
        LUNCH_BUILD_HOST=build/target/cygwin.mk
    elif [ $1 = Dawin ]
    then
        LUNCH_BUILD_HOST=build/target/macos.mk
    elif [ $1 = Linux ]
    then
        LUNCH_BUILD_HOST=build/target/linux.mk
    else
        echo unknown build host machine ...
    fi
}

add_lunch_combo Auto
add_lunch_combo CYGWIN
add_lunch_combo Dawin
add_lunch_combo Linux
