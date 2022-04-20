#!/bin/bash

# 记录脚本的参数和参数数量
# $@：所有参数；$#：参数数量
# 提示：函数里使用$@是函数的所有参数，而非脚本参数
total_para=$@
total_para_num=$#

# 参数大于2时即认定为-x index，提取实际的参数
if [ $total_para_num -gt 2 ]; then
    actual_para=$(echo $total_para | awk '{for(i=3;i<=NF;i=i+1)printf $i" "}')
fi

#####################
# 多示例用法，持续更新 #
#####################

############################
# 一、替换=配置的键值对
# $1：键
# $2：欲修改的值
# $3：文件（sed修改文件-i）
############################
function key_value_sed {
    sed -r "s/($1=)[^\"]*/\1$2/"
    #sed -i -r "s/($1=)[^\"]*/\1$2/" $3
}

############################
# 二、秒转换为时分秒
# $1：秒
############################
function time_conversion {
    declare -i hour min sec
    hour=0
    min=0
    sec=$1

    if [ $sec -ge 3600 ]; then
        hour=$(($sec/3600))
        sec=$(($sec-$hour*3600))
    fi

    if [ $sec -ge 60 ]; then
        min=$(($sec/60))
        sec=$(($sec-$min*60))
    fi

    echo -e "转换后的时分秒为： [$hour:$min:$sec]"
}

# 检测参数，当前参数不能少于功能所需
function check_parameters {
    if [ $2 -gt $(($total_para_num - 2)) ]; then
        echo -e "错误：$1功能的参数不足"
        exit
    fi
}

# 根据index跳转对应的功能
function select_func {
	case $1 in
		1)
            check_parameters 'key_value_sed' 2
			key_value_sed $actual_para
			break
			;;
		2)
            check_parameters 'time_conversion' 1
			time_conversion $actual_para
			break
			;;
        *)
            echo "无index对应功能"
			break
			;;
    esac
}

# 帮助
function show_help {
	echo -e "[HELP] 用法：multi_usage.sh [选项] | [参数]\n"
	echo "   -x index   执行index对应功能，参数跟后面"
	echo "   -h         帮助信息"
	echo "   -v         版本信息"

    echo -e "\n功能列表："
    echo "    1         替换=配置的键值对：键，欲修改的值，文件（可选）"
    echo "    2         秒转换为时分秒：秒"
}

# 版本信息
function show_info {
	echo -e "Multi Usage v1.0\n"
	echo "集成了许多小功能"
}

# 参数/选项，$OPT为选项，$OPTARG为选项参数
# x:带参，x不带参
while getopts "x:hv" OPT;
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
        x)
            select_func $OPTARG
            break
            ;;
        *)
            show_help
            break
            ;;
    esac
done