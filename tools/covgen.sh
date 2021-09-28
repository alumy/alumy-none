dir=$1

lcov -c -d $dir -o $dir/app.info
genhtml $dir/app.info -o $dir/cc_result

