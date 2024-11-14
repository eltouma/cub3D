#! /bin/bash

cub3D=./cub3D
cub3D_exist=(1)
bad_maps=maps/bad/
good_maps=./maps/good/
green='\e[32m'
red='\e[31m'
blue='\e[34m'
reset='\e[0m'
valgrind=0
test_count=(1)
total_test=$((total_test+0))

# Echo an error if there is an argument 
# echo -e 	Prints the \n correctly
# set -e	Exit when any command fails
if [ $# -ne 0 ]; then
	printf "${red}Error${reset}:"; 
	trap 'echo -e "\nWrong number of argument"' EXIT
	set -e
fi

printf "Hello\n\nThis tester only tests ${red}bad maps${reset}.\n"
printf "If your program returns an error, the test is considered valid ✅\n"
printf "If your program launches a window, the test is considered unvalid ❌\n\n"
printf "⚠️  WARNING: If the test launches a window without closing it, click on 'esc'\n\n"

sleep 3

echo "Do you have a maps/bad/ folder? (y/n)"
read -r answer
if [ "$answer" = "n" ]; then
	mkdir maps/bad
	cp  maps/*.cub maps/bad/.
fi

if [ ! -f $cub3D ]; then
	cub3D_exist=0
	make fclean
	make
fi

# Check if ./cub3D have no argument
if [ $# -eq 0 ]; then
	for i in $cub3D;
		do ./$i > /dev/null 2>&1;
			if [ $? -ne 0 ]; then
				((total_test=total_test+1))
			fi
	done
fi

total_test=(1)

# Count number of bad_maps
if [ $# -eq 0 ]; then
	cd $bad_maps || exit 1
	#cd $good_maps || exit 1
	test_count=$(ls *.cub 2>/dev/null | wc -l)
	if [ $test_count -eq 0 ]; then
		printf "${red}Error${reset}:\n"; 
		echo -e "❌\tNo .cub files found."
		exit 1
    	fi
fi

test_count=$(($test_count))
cd ../../

while [ true ]; do
	echo -ne "\nDo you want to launch valgrind? (y/n)\n"
	read -r answer
	if [ "$answer" = "y" ]; then
		valgrind=1
		printf "➡️  Launch tester ${blue}with${reset} valgrind\n\n";
		#printf "${blue}Launch tester with valgrind${reset}\n";
#		echo -e "Launch tester with valgrind\n"
		break
	elif [ "$answer" = "n" ]; then
		valgrind=0
		printf "➡️  Launch tester ${blue}without${reset} valgrind\n\n";
		#echo -e "Launch tester without valgrind\n"
		break
	else
		echo -e "Sorry $answer is not valid"
	fi
done

# Check bad_maps
for i in $bad_maps*.*; do
	if [ "$valgrind" -eq 1 ]; then
        	 valgrind --leak-check=full --show-leak-kinds=all -s $cub3D "$i" & cub3d_pid="$!";
	else
        	$cub3D "$i" > /dev/null 2>&1 & cub3d_pid="$!"
	fi
                sleep 0.005 #  bad map
                # sleep 0.1 # good maps
                window_id=$(xdotool search --name "cub3D")
#                window_id=$(xdotool search --pid $cub3d_pid)
                if [ ! -z "$window_id" ]; then
                        echo "❌ Window found for $cub3D $i"
                        xdotool windowclose "$window_id"
                        kill $cubd3d_pid 2>/dev/null
                        echo -e "Window closed.\n"
                        continue;
                fi
                wait $cub3d_pid
                code_status="$?"
                count=0
                total=$test_count
                while [ $count -lt $total ]; do
                        sleep 0.01
                        #sleep 2
                        count=$(($count + 1))
                        pd=$(($count * 73 / $total))
                        printf "\r%d.%d%% complete ($total_test of $test_count)" $(($count*100/$total)) $((($count*1000/$total)%10))
                done
                if [ $code_status -eq 1 ]; then
                        ((total_test=total_test+1))
                        echo -e "\n✅\t./cub3D $i\n"
                elif [ $code_status -eq 0 ]; then
        #               wmctrl -c $cub3D
                        echo -e "\n❌\t./cub3D $i\n"
                else
                        echo -e '\n❌\tUnexpected return code\n'        
                fi
done

total_test=$(($total_test-1))

if [ $cub3D_exist -eq 0 ]; then
	make fclean
fi

if [ $# -eq 0 ]; then
	if [ $total_test -eq $test_count ]; then
		printf "${green}Passed: ${reset}"; echo $total_test'/'$test_count
	else
		printf "${red}Failed: ${reset}"; echo $total_test'/'$test_count
	fi
fi
