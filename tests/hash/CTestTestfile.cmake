# CMake generated Testfile for 
# Source directory: /home/rcarrasco/SevaBit/tests/hash
# Build directory: /home/rcarrasco/SevaBit/tests/hash
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(hash-fast "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "fast" "/home/rcarrasco/SevaBit/tests/hash/tests-fast.txt")
add_test(hash-slow "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "slow" "/home/rcarrasco/SevaBit/tests/hash/tests-slow.txt")
add_test(hash-slow-1 "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "slow-1" "/home/rcarrasco/SevaBit/tests/hash/tests-slow-1.txt")
add_test(hash-tree "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "tree" "/home/rcarrasco/SevaBit/tests/hash/tests-tree.txt")
add_test(hash-extra-blake "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "extra-blake" "/home/rcarrasco/SevaBit/tests/hash/tests-extra-blake.txt")
add_test(hash-extra-groestl "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "extra-groestl" "/home/rcarrasco/SevaBit/tests/hash/tests-extra-groestl.txt")
add_test(hash-extra-jh "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "extra-jh" "/home/rcarrasco/SevaBit/tests/hash/tests-extra-jh.txt")
add_test(hash-extra-skein "/home/rcarrasco/SevaBit/tests/hash/hash-tests" "extra-skein" "/home/rcarrasco/SevaBit/tests/hash/tests-extra-skein.txt")
