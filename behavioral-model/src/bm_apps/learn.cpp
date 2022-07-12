me modern shells, which will fall back to slower equivalents on
# less featureful shells.


# func_append VAR VALUE
# ---------------------
# Append VALUE onto the existing contents of VAR.

  # We should try to minimise forks, especially on Windows where they are
  # unreasonably slow, so skip the feature probes when bash or zsh are
  # being used:
  if test set = "${BASH_VERSION+set}${ZSH_VERSION+set}"; then
    : ${_G_HAVE_ARITH_OP="yes"}
    : ${_G_HAVE_XSI_OPS="yes"}
    # The += operator was introduced in bash 3.1
    case $BASH_VERSION in
      [12].* | 3.0 | 3.0*) ;;
      *)
        : ${_G_HAVE_PLUSEQ_OP="yes"}
        ;;
    esac
  fi

  # _G_HAVE_PLUSEQ_OP
  # Can be empty, in which case the shell is probed, "yes" if += is
  # useable or anything else if it does not work.
  test -z "$_G_HAVE_PLUSEQ_OP" \
    && (eval 'x=a; x+=" b"; test "a b" = "$x"') 2>/dev/null \
    && _G_HAVE_PLUSEQ_OP=yes

if test yes = "$_G_HAVE_PLUSEQ_OP"
then
  # This is an XSI compatible shell, allowing a faster implementation...
  eval 'func_append ()
  {
    $debug_cmd

    eval "$1+=\$2"
  }'
else
  # ...otherwise fall back to using expr, which is often a shell builtin.
  func_append ()
  {
    $debug_cmd

    eval "$1=\$$1\$2"
  }
fi


# func_append_quoted VAR VALUE
# ----------------------------
# Quote VALUE and append to the end of shell variable VAR, separated
# by a space.
if test yes = "$_G_HAVE_PLUSEQ_OP"; then
  eval 'func_append_quoted ()
  {
    $debug_cmd

    func_quote_for_eval "$2"
    eval "$1+=\\ \$func_quote_for_eval_result"
  }'
else
  func_append_quoted ()
  {
    $debug_cmd

    func_quote_for_eval "$2"
    eval "$1=\$$1\\ \$func_quote_for_eval_result"
  }
fi


# func_append_uniq VAR VALUE
# --------------------------
# Append unique VALUE onto the existing contents of VAR, assuming
# entries are delimited by the first character of VALUE.  For example:
#
#   func_append_uniq options " --another-option option-argument"
#
# will only append to $options if " --another-option option-argument "
# is not already present somewhere in $options already (note spaces at
# each end implied by leading space in second argument).
func_append_uniq ()
{
    $debug_cmd

    eval _G_current_value='`$ECHO $'$1'`'
    _G_delim=`expr "$2" : '\(.\)'`

    case $_G_delim$_G_current_value$_G_delim in
      *"$2$_G_delim"*) ;;
      *) func_append "$@" ;;
    esac
}


# func_arith TERM...
# ------------------
# Set func_arith_result to the result of evaluating TERMs.
  test -z "$_G_HAVE_ARITH_OP" \
    && (eval 'test 2 = $(( 1 + 1 ))') 2>/dev/null \
    && _G_HAVE_ARITH_OP=yes

if test yes = "$_G_HAVE_ARITH_OP"; then
  eval 'func_arith ()
  {
    $debug_cmd

    func_arith_result=$(( $* ))
  }'
else
  func_arith ()
  {
    $debug_cmd

    func_arith_result=`expr "$@"`
  }
fi


# func_basename FILE
# ------------------
# Set func_basename_result to FILE with everything up to and including
# the last / stripped.
if test yes = "$_G_HAVE_XSI_OPS"; then
  # If this shell supports suffix pattern removal, then use it to avoid
  # forking. Hide the definitions single quotes in case the shell chokes
  # on unsupported syntax...
  _b='func_basename_result=${1##*/}'
  _d='case $1 in
        */*) func_dirname_result=${1%/*}$2 ;;
        *  ) func_dirname_result=$3        ;;
      esac'

else
  # ...otherwise fall back to using sed.
  _b='func_basename_result=`$ECHO "$1" |$SED "$sed_basename"`'
  _d='func_dirname_result=`$ECHO "$1"  |$SED "$sed_dirname"`
      if test "X$func_dirname_result" = "X$1"; then
        func_dirname_result=$3
      else
        func_append func_dirname_result "$2"
      fi'
fi

eval 'func_basename ()
{
    $debug_cmd

    '"$_b"'
}'


# func_dirname FILE APPEND NONDIR_REPLACEMENT
# -------------------------------------------
# Compute the dirname of FILE.  If nonempty, add APPEND to the result,
# otherwise set result to NONDIR_REPLACEMENT.
eval 'func_dirname ()
{
    $debug_cmd

    '"$_d"'
}'


# func_dirname_and_basename FILE APPEND NONDIR_REPLACEMENT
# --------------------------------------------------------
# Perform func_basename and func_dirname in a single function
# call:
#   dirname:  Compute the dirname of FILE.  If nonempty,
#             add APPEND to the result, otherwise set result
#             to NONDIR_REPLACEMENT.
#             value returned in "$func_dirname_result"
#   basename: Compute filename of FILE.
#             value retuned in "$func_basename_result"
# For efficiency, we do not delegate to the functions above but instead
# duplicate the functionality here.
eval 'func_dirn