printf '\033[32mSetting CRY Environment\033[0m\n\n'

printf "Set cry test directory location : "
read DIR
export CRY_TEST_DIR=$DIR
printf '\033[32mOK!\033[0m'

sudo chmod 777 *.sh

cp ./testOut.cc $CRY_TEST_DIR
cd $CRY_TEST_DIR
make testOut
