#!/bin/bash

# 获取脚本路径
shell_script=$0

# EOF预设回答交互，[y|NULL（可以理解为直接enter）|n]
function func_eof {
	bash $shell_script -a << EOF
y

n
EOF
}

# 命令行自定义回答交互
function func_ask {
	read -p "首先，A等不等于A [y/n]？" answer1
	read -p "其次，A等不等于a [y/n]？" answer2
	read -p "最后，A等不等于B [y/n]？" answer3

	echo -e "\n回答：$answer1 / $answer2 / $answer3"
}

# 帮助
function show_help {
	echo -e "[HELP] interactive_response.sh [选项]\n"
	echo "   -a         以命令行自定义回答，测试交互"
	echo "   -x         以代码预设回答，测试交互"
	echo "   -h         帮助信息"
	echo "   -v         版本信息"
}

# 版本信息
function show_info {
	echo -e "Interactive Response v1.0\n"
	echo "测试交互应答脚本"
}

# 参数/选项，$OPT为选项，$OPTARG为选项参数（该脚本无参数）
# x:带参，x不带参
while getopts "axhv" OPT;
do
	case $OPT in
		h)
			show_help
			break
			;;
		v)
			show_info
			break
			;;
		a)
			func_ask
			break
			;;
		x)
			func_eof
			break
			;;
		*)
			show_help
			break
			;;
	esac
done